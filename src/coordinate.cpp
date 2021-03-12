#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

const int L = 128;

int main()
{
    int V = L * L;
    ofstream ofs("coordinate.dat");
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            ofs << i+j*L << endl;
        }
    }
}