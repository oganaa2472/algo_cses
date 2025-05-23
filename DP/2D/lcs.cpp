#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> t1(n), t2(m);
    for (int i = 0; i < n; i++) cin >> t1[i];
    for (int i = 0; i < m; i++) cin >> t2[i];

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Bottom-up DP for LCS
    for (int ind1 = 1; ind1 <= n; ind1++) {
        for (int ind2 = 1; ind2 <= m; ind2++) {
            if (t1[ind1 - 1] == t2[ind2 - 1])
                dp[ind1][ind2] = 1 + dp[ind1 - 1][ind2 - 1];
            else
                dp[ind1][ind2] = max(dp[ind1 - 1][ind2], dp[ind1][ind2 - 1]);
        }
    }

    int i = n, j = m;
    vector<int> result;

    // Backtrack to find LCS
    while (i > 0 && j > 0) {
        if (t1[i - 1] == t2[j - 1]) {
            result.push_back(t1[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(result.begin(), result.end());

    cout << dp[n][m] << endl;
    for (auto it : result) cout << it << " ";
    cout << endl;

    return 0;
}
