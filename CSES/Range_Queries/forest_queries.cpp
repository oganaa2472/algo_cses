#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Fast I/O is very important for 200,000 queries
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    // 2D prefix sum array (using 1-based indexing for convenience)
    vector<vector<int>> pref(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            int val = (c == '*' ? 1 : 0);
            
            // Build the prefix sum using values from top, left, and diagonal
            pref[i][j] = val + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
        }
    }

    while (q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;

        // Apply the Inclusion-Exclusion formula
        int result = pref[y2][x2] 
                   - pref[y1-1][x2] 
                   - pref[y2][x1-1] 
                   + pref[y1-1][x1-1];
        
        cout << result << "\n";
    }

    return 0;
}