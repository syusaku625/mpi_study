#include<cstdlib>
#include<mpi.h>
#include<vector>
#include<iostream>
using namespace std;

const int L=8;
int main(int argc ,char **argv){
    MPI_Init(&argc, &argv);
    int rank, procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    const int mysize = L/procs;
    vector<int> local(mysize, rank);
    vector<int> global(L);
    MPI_Gather(local.data(), mysize, MPI_INT, global.data(), mysize, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0){
        for(int i=0; i<L; i++){
            cout << global[i];
        }
        cout << endl;
    }
    MPI_Finalize();
}
