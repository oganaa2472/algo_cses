#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
unordered_map<string,long long> memo;
long long solve(int l, int r, vector<long long>& nums, vector<vector<long long>>& dp) {
    if (l == r) return nums[l];
    if (l > r) return 0;
    if (dp[l][r] != LLONG_MIN) return dp[l][r];

    long long takeLeft = nums[l] - solve(l+1, r, nums, dp);
    long long takeRight = nums[r] - solve(l, r-1, nums, dp);
    return dp[l][r] = max(takeLeft, takeRight);
}
int main() {
    int n;
    cin>>n;
	// your code goes here
	long long sum = 0;
	vector<long long> nums(n);
	

	vector<vector<long long>> dp(n, vector<long long>(n));
    for(int i =0;i<n;i++){
	    cin>>nums[i];
        dp[i][i] = nums[i];
	    sum += nums[i];
	}
    for(int left = n-1;left>=0;left--){
        for(int right = left+1;right<n;right++){
            long long takeLeft = nums[left] - dp[left+1][right];
            long long takeRight = nums[right] - dp[left][right-1];
            dp[left][right] = max(takeLeft, takeRight);
        }
    }
    cout<< (dp[0][n-1] + sum)/2 <<endl;
	// long long ans = (solve(0,n-1,nums,dp) + sum) / 2;
	// cout<<ans<<endl;
}
