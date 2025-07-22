#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; i++) {
        cin >> movies[i].first >> movies[i].second;
    }

    // Sort movies by ending time
    sort(movies.begin(), movies.end(), [](auto &a, auto &b) {
        return a.second < b.second;
    });

    // multiset of available times (when each member is free)
    multiset<int> end_times;
    for (int i = 0; i < k; i++) {
        end_times.insert(0); // all members free at time 0
    }

    int count = 0;
    for (auto [start, end] : movies) {
        auto it = end_times.upper_bound(start);
        if (it == end_times.begin()) continue; // no one available
        --it; // member who is free at or before 'start'
        end_times.erase(it);
        end_times.insert(end);
        count++;
    }

    cout << count << "\n";
    return 0;
}
