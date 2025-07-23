// #include <bits/stdc++.h>
// using namespace std;

// const int MAXN = 1005;
// const int MAXX = 1e5 + 5;
// const int MOD = 1e9 + 7;
// int n, x;
// vector<int> h, s;
// vector<vector<int>> dp;

// int solve(int i, int money_left) {
//     // Out of bounds
//     if (i == n) return 0;
//     if (dp[i][money_left] != -1) return dp[i][money_left];

//     int res = solve(i + 1, money_left);
//     if(money_left>=h[i]){
//         res = max(res,s[i]+solve(i+1,money_left-h[i]));
//     }


//     return dp[i][money_left] = res;
// }
// int main(){
//     cin >> n >> x;
//     h.resize(n);
//     s.resize(n);
//     dp.assign(n + 1, vector<int>(x + 1, -1));

//     for (int i = 0; i < n; i++) cin >> h[i];
//     for (int i = 0; i < n; i++) cin >> s[i];

//     cout << solve(0, x) << endl;
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n); // h: prices, s: pages

    for (int i = 0; i < n; i++) cin >> h[i];
    for (int i = 0; i < n; i++) cin >> s[i];

    vector<int> dp(x + 1, 0); // dp[j] = max pages with total cost j

    for (int i = 0; i < n; i++) {
        for (int j = x; j >= h[i]; j--) {
            dp[j] = max(dp[j], dp[j - h[i]] + s[i]);
        }
    }

    cout << dp[x] << "\n";
    return 0;
}
