#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i = 0;i<n;i++) cin>>nums[i];
    vector<int> ans;
    for(int i = 0 ;i<n;i++){
        auto lower = lower_bound(ans.begin(),ans.end(),nums[i]);
        if(lower==ans.end()){
            ans.push_back(nums[i]);
        }else{
            ans[lower-ans.begin()] = nums[i];
        }
    }
    cout<<ans.size()<<endl;
    // o(n*log(n))
}
