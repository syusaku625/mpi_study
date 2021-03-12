import glob
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import pylab

#x = np.arange(0, 127, 1)
#y = np.arange(127,0, -1)
#X, Y = np.meshgrid(x, y)
test = glob.glob('./result/*')
count=0
for file in test:
    a = np.arange(0)
    for l in open(file).readlines():
        data = l[:-1].split(' ')
        a=np.append(a, [float(data[0])])
    b=a.reshape(128, 128)
    fig = plt.figure(figsize=(8,6))
    plt.imshow(b)
    plt.title("Plot 2D array")
    filename="test"+str(count)
    plt.savefig(filename)
    count+=1