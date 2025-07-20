#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<long long> nums;

bool splitNum(long long mid) {
    int day = 1;
    long long c = 0;
    for (int i = 0; i < nums.size(); i++) {
        c = c + nums[i];
        if (c > mid) {
            day++;
            c = nums[i];
        }
    }
    return day <= k;
}

long long splitArray() {
    long long right = accumulate(nums.begin(), nums.end(), 0LL);
    long long left = *max_element(nums.begin(), nums.end());

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (splitNum(mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    cin >> n >> k;
    nums.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << splitArray() << endl;

    return 0;
}
