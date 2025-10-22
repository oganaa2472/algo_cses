#include <bits/stdc++.h>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
    vector<int> cur;
    // let's think about binary search solution 
    // 10 9
    int n = nums.size();
    for(int i = 0;i<n;i++){
        auto it = lower_bound(cur.begin(),cur.end(),nums[i]);
        if(it==cur.end()){
            cur.push_back(nums[i]);
        }else{
            *it = nums[i];
        }
    }
    return (int)cur.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int lis_length = lengthOfLIS(nums);
    cout << lis_length << "\n";

    return 0;
}