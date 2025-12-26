#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * PROBLEM: Range Counting Queries
 * Technique: Offline Sweep-line with Fenwick Tree
 * Time Complexity: O((N + Q) log N)
 * Space Complexity: O(N + Q)
 */

struct Query {
    int id, l, r, val, sign;
};

struct FenwickTree {
    int n;
    vector<int> bit;
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    void update(int i, int delta) {
        for (; i <= n; i += i & -i) bit[i] += delta;
    }

    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) sum += bit[i];
        return sum;
    }

    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i].first; // Утга
        nums[i].second = i + 1; // Индекс
    }
    // Тоонуудыг утгаар нь эрэмбэлэх
    sort(nums.begin(), nums.end());

    vector<Query> events;
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        // Асуулгыг хоёр хэсэгт хуваах: [1, d] - [1, c-1]
        events.push_back({i, a, b, d, 1});
        events.push_back({i, a, b, c - 1, -1});
    }
    // Асуулгуудыг утгаар нь эрэмбэлэх
    sort(events.begin(), events.end(), [](Query &a, Query &b) {
        return a.val < b.val;
    });

    FenwickTree ft(n);
    vector<int> results(q, 0);
    int numIdx = 0;

    for (auto &ev : events) {
        // Асуулгын утгаас (ev.val) бага буюу тэнцүү бүх тоог BIT-д нэмэх
        while (numIdx < n && nums[numIdx].first <= ev.val) {
            ft.update(nums[numIdx].second, 1);
            numIdx++;
        }
        // [a, b] муж дахь нийлбэрийг аваад тэмдгээр үржүүлж нэмэх
        results[ev.id] += ev.sign * ft.query(ev.l, ev.r);
    }

    for (int i = 0; i < q; i++) {
        cout << results[i] << "\n";
    }

    return 0;
}