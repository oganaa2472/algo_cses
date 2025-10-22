#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
int main() {
    int n;
    cin>>n;
	// your code goes here
	int sum = 0;
	int S = 1LL * n * (n+1) / 2;
	if(S%2) {
	    cout<<0<<endl;
	    return 0;
	}
	int target = S/2;
	
	vector<int> dp(target+1,0);
	dp[0] = 1;
	for(int i = 1;i<=n;i++){
	    for(int j = target;j>=i;j--){
	        dp[j] = (dp[j-i]+dp[j])%MOD;
	    }
	}
	long long inv = (MOD+1)/2;
	cout<<dp[target]*inv%MOD<<endl;
}
