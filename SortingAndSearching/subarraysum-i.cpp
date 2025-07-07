#include <bits/stdc++.h>
using namespace std;
long long subarraySum(vector<int>& nums, int k) {
        unordered_map<long long,long long> mp;
        mp[0] = 1;
        long long prefix = 0;
        long long res = 0;
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
