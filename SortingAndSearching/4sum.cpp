#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<pair<int, int>> a(n); // (value, index)
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1; // Use 1-based indexing for output
    }

    // Sort for easier handling
    sort(a.begin(), a.end());

    // Map: sum -> vector of index pairs
    unordered_map<int, vector<pair<int, int>>> mp;

    // Try all pairs i, j
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int remaining = x - a[i].first - a[j].first;

            // Check if there's any pair that makes up the remaining
            if (mp.find(remaining) != mp.end()) {
                for (auto p : mp[remaining]) {
                    int x1 = p.first, x2 = p.second;
                    if (x1 != i && x1 != j && x2 != i && x2 != j) {
                        // All indices are distinct
                        cout << a[x1].second << " " << a[x2].second << " " << a[i].second << " " << a[j].second << "\n";
                        return 0;
                    }
                }
            }
        }

        // Add all previous pairs ending at i
        for (int j = 0; j < i; j++) {
            int sum = a[i].first + a[j].first;
            mp[sum].push_back({j, i});
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
