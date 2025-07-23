#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int n;
vector<string> grid;
vector<vector<int>> dp;

int countPaths(int i, int j) {
    // Out of bounds
    if (i < 0 || j < 0) return 0;

    // Trap cell
    if (grid[i][j] == '*') return 0;

    // Base case: start point
    if (i == 0 && j == 0) return 1;

    // Already computed
    if (dp[i][j] != -1) return dp[i][j];

    int up = countPaths(i - 1, j);
    int left = countPaths(i, j - 1);

    return dp[i][j] = (up + left) % MOD;
}
int main() {
    cin >> n;
    grid.resize(n);
    dp.assign(n, vector<int>(n, -1));

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    cout << countPaths(n - 1, n - 1) << endl;
    return 0;
}