#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n;
    cin >> x >> n;

    set<int> lights;
    multiset<int> segments;

    // Initial state
    lights.insert(0);
    lights.insert(x);
    segments.insert(x);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;

        // Find neighbors
        auto it = lights.lower_bound(p);
        int right = *it;
        int left = *prev(it);

        // Update segments
        segments.erase(segments.find(right - left));
        segments.insert(p - left);
        segments.insert(right - p);

        // Insert new light
        lights.insert(p);

        // Print maximum segment
        cout << *segments.rbegin() << " ";
    }

    return 0;
}
