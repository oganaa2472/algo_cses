#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n,price;
    cin>>n>>price;
    
    vector<int> pages(n),prices(n);
    
    for(int i = 0;i<n;i++) cin>>prices[i];
    for(int i = 0;i<n;i++) cin>>pages[i];
    
    
    vector<vector<int>> dp(n+1,vector<int>(price+1,0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= price; j++) {
            dp[i][j] = dp[i-1][j];
            int left = j-prices[i-1];
            if (left >= 0) {
        	    dp[i][j] = max(dp[i][j], dp[i-1][left]+pages[i-1]);
            }
          
        }
      
    }
    cout << dp[n][price] << endl;
  }
