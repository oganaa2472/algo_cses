#include <bits/stdc++.h>
using namespace std;

// dp[mask] = pair(minRides, weightInLastRide)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;
    vector<long long> w(n);
    for (int i = 0; i < n; ++i) cin >> w[i];

    const int N = 1 << n;
    // initialize with large values
    const long long INF_R = 1e9;
    // dp[mask] = {minRides, weightInLastRide}
    vector<pair<int,long long>> dp(N, {INT_MAX, (long long)1e18});
    dp[0] = {1, 0}; // base case: no items require one ride with 0 weight
    for (int mask = 0; mask < N; ++mask) {
        for (int j = 0; j < n; ++j) {
            if (mask & (1 << j)) continue; // item j already included
            int nextMask = mask | (1 << j);
            long long itemWeight = w[j];
            auto [rides, lastWeight] = dp[mask];
            if (lastWeight + itemWeight <= x) {
                // can fit in the current ride
                pair<int,long long> candidate = {rides, lastWeight + itemWeight};
                dp[nextMask] = min(dp[nextMask], candidate);
            } else {
                // need a new ride
                pair<int,long long> candidate = {rides + 1, itemWeight};
                dp[nextMask] = min(dp[nextMask], candidate);
            }
        }
    }
    cout << dp[N - 1].first << "\n";
}