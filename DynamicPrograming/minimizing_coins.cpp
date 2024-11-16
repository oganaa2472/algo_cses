#include <iostream>
#include <vector>
#include <climits>
using namespace std;

long long MOD = 1e9 + 7;

int main() {
    long long n,x;
    cin >> n>>x;
    vector<long long> dp(x+1,INT_MAX);
    vector<long long> coins(n);
    for(int i =0;i<n;i++) cin>>coins[i];
	dp[0] = 0;
    for(int i = 1;i<=x;i++){
        for(auto coin:coins){
            if(i-coin>=0){
                dp[i] = min(dp[i], dp[i-coin]+1);
            }
        }
    }
   if(dp[x]==INT_MAX) cout<<-1<<endl;
   else cout<<dp[x]<<endl;
    return 0;
}
