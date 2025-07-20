#include <bits/stdc++.h>
using namespace std;

vector<int> threeSum(vector<pair<int,int>>& nums, int k) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    
    for (int i = 0; i < n; i++) {
        if (i > 0 && nums[i].first == nums[i - 1].first) continue;  // skip duplicates
        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = nums[i].first + nums[l].first + nums[r].first;
            if (sum > k) r--;
            else if (sum < k) l++;
            else {
                vector<int> res = {nums[i].second + 1, nums[l].second + 1, nums[r].second + 1};
                sort(res.begin(), res.end());  // optional: sort indices for cleaner output
                return res;
            }
        }
    }
    return {};
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    vector<int> answer = threeSum(v, k);
    if (answer.empty()) cout << "IMPOSSIBLE\n";
    else for (auto it : answer) cout << it << " ";
}
