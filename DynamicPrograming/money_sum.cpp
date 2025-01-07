#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n ;
    cin>>n;
    vector<int> moneys(n+1,0);
    int moneysum = 0;
    for(int i = 1 ;i<=n;i++){
        cin>>moneys[i];
        moneysum+=moneys[i];
        
    }
    vector<vector<int>> dp(moneysum+1,vector<int>(n+1,0));
    dp[0][0] = true;
    int count = 0;
    for (int k = 1; k<=n; k++) {
        for (int x = 0; x <= moneysum; x++) {
            if (x-moneys[k] >= 0) dp[x][k] |= dp[x-moneys[k]][k-1];
            dp[x][k] |= dp[x][k-1];
            if(k==n&&dp[x][k]==1) count++; 
        }
       
    }

    cout<<count-1;
    cout<<endl;
    for(int i = 1;i<=moneysum;i++){
        if(dp[i][n]==1) cout<<i<<" ";
        
    }
}
