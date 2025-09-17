#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;

long long modinv(long long a){
    long long res = 1, b = MOD-2;
    while(b){
        if(b&1) res = res*a % MOD;
        a = a*a % MOD;
        b >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin >> n >> m;
    vector<vector<long long>> mat(n, vector<long long>(m+1));
    for(int i=0;i<n;i++)
        for(int j=0;j<=m;j++)
            cin >> mat[i][j];

    vector<long long> x(m,0);
    int row = 0;
    for(int col=0;col<m && row<n;col++){
        int pivot = row;
        while(pivot<n && mat[pivot][col]==0) pivot++;
        if(pivot==n) continue; // free variable
        swap(mat[row], mat[pivot]);
        long long inv = modinv(mat[row][col]);
        for(int j=col;j<=m;j++) mat[row][j] = mat[row][j]*inv % MOD;

        for(int i=0;i<n;i++){
            if(i==row) continue;
            long long factor = mat[i][col];
            for(int j=col;j<=m;j++){
                mat[i][j] = (mat[i][j] - factor*mat[row][j]%MOD + MOD)%MOD;
            }
        }
        row++;
    }

    // Check consistency
    for(int i=row;i<n;i++){
        if(mat[i][m]!=0){
            cout << -1 << "\n";
            return 0;
        }
    }

    // Extract solution
    for(int i=0;i<row;i++){
        int first=0;
        while(first<m && mat[i][first]==0) first++;
        if(first<m) x[first] = mat[i][m];
    }

    for(int i=0;i<m;i++) cout << x[i] << " ";
    cout << "\n";
}
