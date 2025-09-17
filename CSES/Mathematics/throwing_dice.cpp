#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;

struct Matrix {
    long long a[6][6];
    Matrix(long long val=0) {
        memset(a,0,sizeof(a));
        for(int i=0;i<6;i++) a[i][i] = val;
    }
};

Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
            for(int k=0;k<6;k++)
                C.a[i][j] = (C.a[i][j] + A.a[i][k]*B.a[k][j]%MOD)%MOD;
    return C;
}

Matrix matrix_pow(Matrix A, long long n) {
    Matrix res(1);
    while(n) {
        if(n&1) res = multiply(res, A);
        A = multiply(A, A);
        n >>= 1;
    }
    return res;
}

int main() {
    long long n;
    cin >> n;
    if(n==0) {cout << 1 << "\n"; return 0;}
    vector<long long> base = {1,1,2,4,8,16}; // f(0..5)
    if(n<=5) {cout << base[n] << "\n"; return 0;}

    Matrix M;
    for(int i=0;i<6;i++) M.a[0][i]=1;
    for(int i=1;i<6;i++) M.a[i][i-1]=1;

    Matrix P = matrix_pow(M, n-5);

    long long ans=0;
    for(int i=0;i<6;i++)
        ans = (ans + P.a[0][i]*base[5-i]%MOD)%MOD;

    cout << ans << "\n";
}
