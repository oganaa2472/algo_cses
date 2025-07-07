#include <bits/stdc++.h>
using namespace std;
int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> mp;
        mp[0] = 1;
        int prefix = 0;
        int res = 0;
        for(int num:nums){
            prefix+=num;
            res=res+mp[prefix-k];
            mp[prefix]++;
        }
        return res;
    }

int main() {
    int n,k;
    cin >> n>>k;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin>>nums[i];
    }
    cout<<subarraySum(nums,k);

    
    return 0;
}
