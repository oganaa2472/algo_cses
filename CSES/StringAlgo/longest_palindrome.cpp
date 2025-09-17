#include <bits/stdc++.h>
using namespace std;

string longestPalindrome(const string &s) {
    int n = s.size();
    if(n == 0) return "";

    // Transform s: add separators
    string t = "^";
    for(char c : s) t += "#" + string(1, c);
    t += "#$";

    int m = t.size();
    vector<int> P(m, 0);
    int C = 0, R = 0; // center, right boundary
    int maxLen = 0, centerIndex = 0;

    for(int i = 1; i < m-1; i++){
        int mirr = 2*C - i;
        if(i < R) P[i] = min(R-i, P[mirr]);

        // Expand around center i
        while(t[i + P[i] + 1] == t[i - P[i] - 1])
            P[i]++;

        // Update center and right boundary
        if(i + P[i] > R){
            C = i;
            R = i + P[i];
        }

        // Track max length
        if(P[i] > maxLen){
            maxLen = P[i];
            centerIndex = i;
        }
    }

    int start = (centerIndex - maxLen) / 2;
    return s.substr(start, maxLen);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    cout << longestPalindrome(s) << "\n";
}
