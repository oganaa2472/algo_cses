#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
int main() {
	// your code goes here
	
	int n;
	cin>>n;
	vector<int> dp(n+1,INF);
	dp[0] = 0;
	for(int i = 1;i<=n;i++){
	    int currentNumber = i;
	    while(currentNumber>0){
	        dp[i] = min(dp[i],dp[i-currentNumber%10]+1);
	        currentNumber = currentNumber/10;
	    }
	}
	cout<<dp[n];

}
