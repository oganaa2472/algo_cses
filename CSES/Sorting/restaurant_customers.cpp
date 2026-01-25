#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    map<int,int> room_sizes;
    for (int i = 0; i < n; ++i) {
        int startTime, endTime;
        cin >> startTime >> endTime;
        room_sizes[startTime]++;
        room_sizes[endTime+1]--;
    }
    int current_rooms = 0;
    int max_rooms = 0;
    for (auto& entry : room_sizes) {
        current_rooms += entry.second;
        max_rooms = max(max_rooms, current_rooms);
    }

    cout << max_rooms << "\n";
    return 0;
}