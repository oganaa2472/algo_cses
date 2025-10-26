#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int n, m;
vector<vector<long long>> memo;

long long dfs(int col, int mask) {
    if (col == m) {
        // If last column is fully filled
        return mask == 0 ? 1 : 0;
    }
    if (memo[col][mask] != -1) return memo[col][mask];

    long long res = 0;

    function<void(int, int)> fill = [&](int pos, int next_mask) {
        if (pos == n) {
            res = (res + dfs(col + 1, next_mask)) % MOD;
            return;
        }
        if (mask & (1 << pos)) {
            // current cell already filled
            fill(pos + 1, next_mask);
        } else {
            // place vertical domino
            if (pos + 1 < n && !(mask & (1 << (pos + 1)))) {
                fill(pos + 2, next_mask);
            }
            // place horizontal domino
            fill(pos + 1, next_mask | (1 << pos));
        }
    };

    fill(0, 0);
    return memo[col][mask] = res;
}

int main() {
    cin >> n >> m;
    int max_mask = 1 << n;
    memo.assign(m, vector<long long>(max_mask, -1));
    cout << dfs(0, 0) << endl;
    return 0;
}
