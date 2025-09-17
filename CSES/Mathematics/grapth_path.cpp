#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long k;
    cin >> n >> m >> k;

    vector<vector<long long>> A(n, vector<long long>(n, 0));
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--; v--; // 0-index
        A[u][v] = (A[u][v]+1) % MOD;
    }

    auto multiply = [&](vector<vector<long long>> &X, vector<vector<long long>> &Y){
        vector<vector<long long>> Z(n, vector<long long>(n,0));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int l=0;l<n;l++)
                    Z[i][j] = (Z[i][j] + X[i][l]*Y[l][j]%MOD) % MOD;
        return Z;
    };

    auto matrix_pow = [&](vector<vector<long long>> &X, long long p){
        vector<vector<long long>> res(n, vector<long long>(n,0));
        for(int i=0;i<n;i++) res[i][i]=1; // identity
        vector<vector<long long>> base = X;
        while(p){
            if(p&1) res = multiply(res, base);
            base = multiply(base, base);
            p >>=1;
        }
        return res;
    };

    vector<vector<long long>> Ak = matrix_pow(A, k);
    cout << Ak[0][n-1] << "\n"; // paths from node 1 to n
}
