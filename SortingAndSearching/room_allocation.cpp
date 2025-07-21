#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<tuple<int, int, int>> customers(n); // (arrival, departure, index)
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        customers[i] = {a, b, i};
    }

    sort(customers.begin(), customers.end());

    // min-heap: (end time, room number)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    int room_count = 0;
    vector<int> answer(n);

    for (auto [start, end, idx] : customers) {
        if (!pq.empty() && pq.top().first < start) {
            // reuse the room
            auto [old_end, room] = pq.top(); pq.pop();
            pq.push({end, room});
            answer[idx] = room;
        } else {
            // need new room
            room_count++;
            pq.push({end, room_count});
            answer[idx] = room_count;
        }
    }

    cout << room_count << '\n';
    for (int x : answer) cout << x << ' ';
    cout << '\n';

    return 0;
}
