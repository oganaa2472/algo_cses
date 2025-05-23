#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// n-row, m-column grid
int n, m;
int dp[1001][1 << 11]; // m хүртэл багана, 2^n боломжит маск

// dfs(col, mask): col дахь баганад ямар ч хандсан байсан, mask бол тухайн баганын төлөв (бит маск)
int dfs(int col, int mask) {
    if (col == m) {
        // хэрвээ бүх багана бөглөгдсөн байвал зөв тохиолдол
        return mask == 0 ? 1 : 0;
    }

    if (dp[col][mask] != -1)
        return dp[col][mask];

    // Дараагийн баганын хувилбаруудыг үүсгэнэ
    int res = 0;

    function<void(int, int)> generate = [&](int pos, int currMask) {
        if (pos == n) {
            // mask -> дараагийн column-д дамжих маск
            res = (res + dfs(col + 1, currMask)) % MOD;
            return;
        }

        if ((mask & (1 << pos)) != 0) {
            // Хэрвээ энэ байр бөглөгдсөн байвал алгас
            generate(pos + 1, currMask);
        } else {
            // 1x2 хэвтээ тавих
            if (pos + 1 < n && (mask & (1 << (pos + 1))) == 0) {
                generate(pos + 2, currMask);
            }
            // 2x1 босоо тавих
            generate(pos + 1, currMask | (1 << pos));
        }
    };

    generate(0, 0);

    return dp[col][mask] = res;
}

int main() {
    cin >> n >> m;

    memset(dp, -1, sizeof(dp));
    cout << dfs(0, 0) << endl;
    return 0;
}
