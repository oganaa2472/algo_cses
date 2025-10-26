#include <bits/stdc++.h>
using namespace std;

string s;
long long dp[20][11][2][2]; // pos, prev_digit (-1..9 mapped to 0..10), tight, leading_zero

long long solve(int pos, int prev_digit, int tight, int leading_zero) {
    if (pos == s.size()) return 1LL; // reached the end, valid number

    if (dp[pos][prev_digit + 1][tight][leading_zero] != -1)
        return dp[pos][prev_digit + 1][tight][leading_zero];

    long long res = 0LL;
    int limit = tight ? (s[pos] - '0') : 9;

    for (int d = 0; d <= limit; d++) {
        if (!leading_zero && d == prev_digit) continue; // cannot repeat adjacent digits
        int new_tight = tight && (d == limit);
        int new_leading_zero = leading_zero && (d == 0);
        res += solve(pos + 1, new_leading_zero ? -1 : d, new_tight, new_leading_zero);
    }

    return dp[pos][prev_digit + 1][tight][leading_zero] = res;
}

long long count_no_adj_same(long long x) {
    if (x < 0) return 0LL;
    s = to_string(x);
    memset(dp, -1, sizeof(dp));
    return solve(0, -1, 1, 1);
}

int main() {
    long long a, b;
    cin >> a >> b;
    cout << count_no_adj_same(b) - count_no_adj_same(a - 1) << endl;
    return 0;
}
