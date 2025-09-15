#include <bits/stdc++.h>
using namespace std;

string s1, s2;
vector<vector<int>> dp;

int solve(int i, int j) {
    // i = эхний string-ийн үлдсэн урт
    // j = хоёр дахь string-ийн үлдсэн урт
    
    // base cases
    if (i == 0) return j; // хоосон → j тэмдэгт нэмэх
    if (j == 0) return i; // i тэмдэгт устгах
    
    // memoization
    if (dp[i][j] != -1) return dp[i][j];
    
    if (s1[i-1] == s2[j-1]) {
        // тэмдэгтүүд адилхан → үйлдэл хэрэггүй
        return dp[i][j] = solve(i-1, j-1);
    } else {
        int insertOp  = solve(i, j-1);
        int deleteOp  = solve(i-1, j);
        int replaceOp = solve(i-1, j-1);
        return dp[i][j] = 1 + min({insertOp, deleteOp, replaceOp});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();
    dp.assign(n+1, vector<int>(m+1, -1));

    cout << solve(n, m) << "\n";
    return 0;
}
