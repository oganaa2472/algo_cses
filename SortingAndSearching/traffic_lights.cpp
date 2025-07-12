#include <iostream>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n;
    cin >> x >> n;

    set<int> lights;        // positions of the traffic lights
    multiset<int> gaps;     // lengths of segments between lights

    // Initial state: lights at 0 and x, one big gap
    lights.insert(0);
    lights.insert(x);
    gaps.insert(x);

    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;

        // Find where this light goes
        auto right = lights.upper_bound(p);   // first light > p
        auto left = prev(right);              // light just before p

        // Remove old gap between left and right
        gaps.erase(gaps.find(*right - *left));

        // Insert new gaps created by new light
        gaps.insert(p - *left);
        gaps.insert(*right - p);

        // Add the new light
        lights.insert(p);

        // Output the current max segment (rbegin = last = max)
        cout << *gaps.rbegin() << " ";
    }

    cout << "\n";
    return 0;
}
