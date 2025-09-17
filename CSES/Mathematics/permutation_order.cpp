#include <bits/stdc++.h>
using namespace std;
vector<long long> fact;

vector<int> getPermutation(int n, long long k) {
    vector<int> nums(n);
    for (int i = 0; i < n; i++) nums[i] = i+1;
    k--; 
    vector<int> ans;
    for (int i = n; i >= 1; i--) {
        long long f = fact[i-1];
        int index = k / f;
        ans.push_back(nums[index]);
        nums.erase(nums.begin() + index);
        k %= f;
    }
    return ans;
}

long long getIndex(int n, vector<int>& perm) {
    vector<int> nums(n);
    for (int i = 0; i < n; i++) nums[i] = i+1;
    long long k = 1;
    for (int i = 0; i < n; i++) {
        int index = find(nums.begin(), nums.end(), perm[i]) - nums.begin();
        k += index * fact[n-1-i];
        nums.erase(nums.begin() + index);
    }
    return k;
}

int main() {
    int t;
    cin >> t;
    int maxN = 20; // safe limit for factorial (20! < 1e18)
    fact.resize(maxN+1);
    fact[0] = 1;
    for (int i = 1; i <= maxN; i++) fact[i] = fact[i-1] * i;

    while(t--) {
        int type, n;
        cin >> type >> n;
        if (type == 1) {
            long long k;
            cin >> k;
            vector<int> perm = getPermutation(n, k);
            for(int x: perm) cout << x << " ";
            cout << "\n";
        } else {
            vector<int> perm(n);
            for(int i=0;i<n;i++) cin >> perm[i];
            cout << getIndex(n, perm) << "\n";
        }
    }
    return 0;
}
