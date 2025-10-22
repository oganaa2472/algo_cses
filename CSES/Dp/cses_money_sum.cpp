#include <bits/stdc++.h>
using namespace std;
// it is similar to subset sum problem
int main() {
    int n;
    cin>>n;
	// your code goes here
	vector<int> values(n);
	int sum = 0;
	
	for(int i = 0;i<n;i++){
	    cin>>values[i];
	    sum+=values[i];
	}
	vector<int> dp(sum+1,0);
	
    dp[0] = 1;
    for(int i = 0;i<n;i++){
        for(int value = sum;value>=values[i];value--){
            dp[value] |= dp[value-values[i]];
        }
    }
    int count=0;
    for(int i = 1;i<=sum;i++){
        if(dp[i]) count++;
    }
    cout<<count<<endl;
    for(int i = 1;i<=sum;i++){
        if(dp[i]) cout<<i<<" ";
    }
}
