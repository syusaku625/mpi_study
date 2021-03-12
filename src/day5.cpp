#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

const int L = 128;
const int TOTAL_STEP = 20000;
const int INTERVAL = 200;
const double F = 0.04;
const int k = 0.06075;
const double dt = 0.2;
const double Du = 0.05;
const double Dv = 0.1;

void init(vector<double> &u, vector<double> &v){
    int d = 3;
    for (int i = L / 2 - d; i < L / 2 + d; i++){
        for (int j = L / 2 - d; j < L / 2 + d; j++){
            u[j + i * L] = 0.7;
        }
    }
    d = 6;
    for (int i = L / 2 - d; i < L / 2 + d; i++){
        for (int j = L / 2 - d; j < L / 2 + d; j++){
            v[j + i * L] = 0.9;
        }
    }
}

double calcU(double tu, double tv){
    return tu * tu * tv - (F + k) * tu;
}

double calcV(double tu, double tv){
    return -tu * tu * tv + F * (1.0 - tv);
}

double laplacian(int ix, int iy, vector<double> &s){
    double ts = 0.0;
    ts += s[ix - 1 + iy * L];
    ts += s[ix + 1 + iy * L];
    ts += s[ix + (iy + 1) * L];
    ts += s[ix + (iy - 1) * L];
    ts -= 4.0 * s[ix + iy * L];
    return ts;
}

void calc(vector<double> &u, vector<double> &v, vector<double> &u2, vector<double> &v2){
    for(int iy = 1; iy < L - 1; iy++){
        for(int ix = 1; ix < L - 1; ix++){
            double du = 0.0;
            double dv = 0.0;    
            const int i = ix + iy * L;
            du = Du * laplacian(ix, iy, u);
            dv = Dv * laplacian(ix, iy, v);
            du += calcU(u[i], v[i]);
            dv += calcV(u[i], v[i]);
            u2[i] = u[i] + du * dt;
            v2[i] = v[i] + dv * dt;
        }
    }
}

void save_as_dat(vector<double> &u) {
    static int index = 0;
    char filename[256];
    sprintf(filename, "result/conf%03d.dat", index);
    cout << filename << endl;
    ofstream ofs(filename);
    for(int i=0; i<u.size(); i++){
        ofs << fixed << setprecision(3) << u[i] << endl;
    }
    index++;
}

int main(){
    const int V = L * L;
    vector<double> u(V,0.0), v(V,0.0);
    vector<double> u2(V,0.0), v2(V,0.0);
    init(u, v);
    for(int i=0; i<TOTAL_STEP; i++){
        if(i & 1){
            calc(u2, v2, u, v);
        }
        else{
            calc(u, v, u2, v2);
        }
        if(i % INTERVAL == 0) save_as_dat(u);
    }
}