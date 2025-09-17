#include <bits/stdc++.h>
using namespace std;

const int N_MAX = 1e7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute squares
    vector<int> squares;
    for(int i=0; i*i <= N_MAX; i++)
        squares.push_back(i*i);

    // Precompute all sums of two squares
    unordered_map<int, pair<int,int>> sum2;
    int sz = squares.size();
    for(int i=0; i<sz; i++){
        for(int j=i; j<sz; j++){
            int s = squares[i] + squares[j];
            if(s > N_MAX) break;
            if(!sum2.count(s)) sum2[s] = {i,j};
        }
    }

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int a=-1,b=-1,c=-1,d=-1;
        bool found=false;

        // Try 1-square
        int r = sqrt(n);
        if(r*r == n){
            a=r; b=c=d=0;
            found=true;
        }

        // Try 2-squares
        if(!found){
            for(int i=0;i<sz && squares[i]<=n && !found;i++){
                int rem = n - squares[i];
                int s = sqrt(rem);
                if(s*s == rem){
                    a=i; b=s; c=d=0;
                    found=true;
                }
            }
        }

        // Try 3-squares using precomputed sum-of-two-squares
        if(!found){
            for(int i=0;i<sz && squares[i]<=n && !found;i++){
                int rem = n - squares[i];
                if(sum2.count(rem)){
                    auto p = sum2[rem];
                    a=i; b=p.first; c=p.second; d=0;
                    found=true;
                }
            }
        }

        // Fallback to 4-squares (rare)
        if(!found){
            for(int i=0;i<sz && squares[i]<=n && !found;i++){
                for(int j=i;j<sz && squares[i]+squares[j]<=n && !found;j++){
                    for(int k=j;k<sz && squares[i]+squares[j]+squares[k]<=n && !found;k++){
                        int rem = n - squares[i] - squares[j] - squares[k];
                        int d_sqrt = sqrt(rem);
                        if(d_sqrt*d_sqrt == rem){
                            a=i; b=j; c=k; d=d_sqrt;
                            found=true;
                        }
                    }
                }
            }
        }

        cout << a << " " << b << " " << c << " " << d << "\n";
    }
}
