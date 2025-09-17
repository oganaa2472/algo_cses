#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // Values are in [1..n]. We'll use 0 as a sentinel ("-infinity") for empty pile.
        // dp[x][y]: number of subsequences processed so far that end with last values x <= y
        // in the two nondecreasing piles when using the greedy leftmost-pile rule.
        int maxValue = n;
        vector<vector<int>> dp(maxValue + 1, vector<int>(maxValue + 1, 0));
        dp[0][0] = 1; // empty subsequence

        for (int v : a) {
            vector<vector<int>> next(maxValue + 1, vector<int>(maxValue + 1, 0));

            for (int x = 0; x <= maxValue; ++x) {
                for (int y = x; y <= maxValue; ++y) {
                    int ways = dp[x][y];
                    if (!ways) continue;

                    // Option 1: skip v
                    next[x][y] += ways;
                    if (next[x][y] >= MOD) next[x][y] -= MOD;

                    // Option 2: include v using deterministic greedy placement
                    // Prefer pile A (x) if x <= v; else try pile B (y) if y <= v; otherwise cannot include.
                    if (x <= v) {
                        int aLast = v, bLast = y;
                        if (aLast <= bLast) {
                            next[aLast][bLast] += ways;
                            if (next[aLast][bLast] >= MOD) next[aLast][bLast] -= MOD;
                        } else {
                            next[bLast][aLast] += ways;
                            if (next[bLast][aLast] >= MOD) next[bLast][aLast] -= MOD;
                        }
                    } else if (y <= v) {
                        int aLast = x, bLast = v;
                        if (aLast <= bLast) {
                            next[aLast][bLast] += ways;
                            if (next[aLast][bLast] >= MOD) next[aLast][bLast] -= MOD;
                        } else {
                            next[bLast][aLast] += ways;
                            if (next[bLast][aLast] >= MOD) next[bLast][aLast] -= MOD;
                        }
                    }
                }
            }

            dp.swap(next);
        }

        long long ans = 0;
        for (int x = 0; x <= maxValue; ++x) {
            for (int y = x; y <= maxValue; ++y) {
                ans += dp[x][y];
                if (ans >= MOD) ans -= MOD;
            }
        }

        cout << ans % MOD << '\n';
    }
    return 0;
}


