COMPILER=mpic++
#local environment
DEST = ~/bin
LIBDIR = /home/syusaku/lib
TARDIR = ./bin
OBJDIR = ./obj
SRCDIR = ./src
MPI_DIR = /usr/local/openmpi-4.1.0/include
MPI_LIB_DIR = -L/usr/local/openmpi-4.1.0/lib

CPPFLAGS = -Wall -O0 -g -std=c++0x -lstdc++fs
INCLUDE = -I./include

#GLOG
#GLOG      = $(LIBDIR)/glog
#LDFLAGS += -L$(GLOG)/lib -lglog -lpthread
#INCLUDE += -I$(GLOG)/include

#boost
#BOOST     = $(LIBDIR)/boost
#LDFLAGS += -L$(BOOST)/lib -lboost_graph 
#INCLUDE += -I$(BOOST)/include

#EIGEN      = $(LIBDIR)/eigen
#INCLUDE += -I$(EIGEN)/include/eigen3

#MPI
INCLUDE += -I$(MPI_DIR)
MPI_LIB_DIR += -lmpi
MPI_LIB_DIR += -lmpi_cxx


TARGET = $(TARDIR)/run

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS = $(OBJECTS:.o=d)

$(TARGET): $(OBJECTS) $(LIBS)
		@[ -d $(TARDIR) ] || mkdir -p $(TARDIR)
		$(COMPILER) -o $@ $^ $(LDFLAGS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
		@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
		$(COMPILER) $(CPPFLAGS) $(INCLUDE) $(MPI_LIB_DIR) -o $@ -c $<

all: clean $(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

install:$(TARGET)
	install -s $(TARGET) $(DEST)

-include $(DEPENDS)