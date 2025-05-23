#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& dp) {
    if (n == 0) return 0;
    if (dp[n] != -1) return dp[n];

    int a = n;
    int res = INT_MAX;

    while (a > 0) {
        int m = a % 10;
        if (m != 0) {
            res = min(res, 1 + solve(n - m, dp));
        }
        a /= 10;
    }

    return dp[n] = res;
}

int main() {
    int n;
    cin >> n;
    vector<int> dp(n + 1, -1);
    cout << solve(n, dp) << endl;
    return 0;
}
