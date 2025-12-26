#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * PROBLEM: Distinct Values Queries
 * Technique: Offline Sweep-line with Fenwick Tree
 * Time Complexity: O((N + Q) log N)
 */

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
};

struct Query {
    int l, r, id;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) cin >> x[i];

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    // Асуулгуудыг баруун хязгаараар (r) эрэмбэлэх
    sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        return a.r < b.r;
    });

    FenwickTree ft(n);
    map<int, int> last_occurrence;
    vector<int> results(q);
    int current_r = 0;

    for (int i = 0; i < q; i++) {
        // Асуулгын r хүртэлх тоонуудыг BIT-д нэмэх
        while (current_r < queries[i].r) {
            current_r++;
            int val = x[current_r];
            // Хэрэв энэ тоо өмнө нь гарч байсан бол хуучин байршлыг нь идэвхгүй болгоно
            if (last_occurrence.count(val)) {
                ft.update(last_occurrence[val], -1);
            }
            // Шинэ байршлыг идэвхжүүлж, бүртгэнэ
            ft.update(current_r, 1);
            last_occurrence[val] = current_r;
        }
        // [l, r] муж дахь идэвхтэй тоонуудыг тоолно
        results[queries[i].id] = ft.query(queries[i].r) - ft.query(queries[i].l - 1);
    }

    for (int res : results) cout << res << "\n";

    return 0;
}