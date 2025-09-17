#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;

struct Matrix {
    long long a[2][2];
    Matrix(long long x=0, long long y=0, long long z=0, long long w=0) {
        a[0][0]=x; a[0][1]=y; a[1][0]=z; a[1][1]=w;
    }
};

Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    C.a[0][0] = (A.a[0][0]*B.a[0][0]%MOD + A.a[0][1]*B.a[1][0]%MOD) % MOD;
    C.a[0][1] = (A.a[0][0]*B.a[0][1]%MOD + A.a[0][1]*B.a[1][1]%MOD) % MOD;
    C.a[1][0] = (A.a[1][0]*B.a[0][0]%MOD + A.a[1][1]*B.a[1][0]%MOD) % MOD;
    C.a[1][1] = (A.a[1][0]*B.a[0][1]%MOD + A.a[1][1]*B.a[1][1]%MOD) % MOD;
    return C;
}

Matrix matrix_pow(Matrix A, long long n) {
    Matrix res(1,0,0,1); // Identity
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
    if(n==0) {cout << 0 << "\n"; return 0;}
    Matrix F(1,1,1,0);
    Matrix ans = matrix_pow(F, n-1);
    cout << ans.a[0][0] << "\n"; // F_n
}
