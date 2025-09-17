#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long k;
    cin >> n >> m >> k;

    vector<vector<long long>> A(n, vector<long long>(n, INF));
    for(int i=0;i<m;i++){
        int u,v;
        long long w;
        cin >> u >> v >> w;
        u--; v--;
        A[u][v] = min(A[u][v], w); // if multiple edges, take minimum
    }

    auto minplus_multiply = [&](vector<vector<long long>> &X, vector<vector<long long>> &Y){
        vector<vector<long long>> Z(n, vector<long long>(n, INF));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int l=0;l<n;l++){
                    if(X[i][l]!=INF && Y[l][j]!=INF)
                        Z[i][j] = min(Z[i][j], X[i][l]+Y[l][j]);
                }
            }
        }
        return Z;
    };

    auto matrix_pow = [&](vector<vector<long long>> &X, long long p){
        vector<vector<long long>> res(n, vector<long long>(n, INF));
        for(int i=0;i<n;i++) res[i][i]=0; // identity in min-plus
        vector<vector<long long>> base = X;
        while(p){
            if(p&1) res = minplus_multiply(res, base);
            base = minplus_multiply(base, base);
            p >>=1;
        }
        return res;
    };

    vector<vector<long long>> Ak = matrix_pow(A, k);
    long long ans = Ak[0][n-1];
    if(ans >= INF) cout << 1000000000000000000  << "\n";
    else cout << ans << "\n";
}
