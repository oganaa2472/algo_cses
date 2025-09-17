#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> P(k);
    for(int i = 0; i < k; i++) cin >> P[i];

    vector<bool> dp(n+1, false);
    dp[0] = false; // 0 sticks is losing

    for(int i = 1; i <= n; i++){
        for(int p : P){
            if(i >= p && !dp[i-p]){
                dp[i] = true;
                break;
            }
        }
    }

    for(int i = 1; i <= n; i++){
        cout << (dp[i] ? 'W' : 'L');
    }
    cout << "\n";
}
