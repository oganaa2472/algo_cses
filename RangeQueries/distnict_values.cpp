#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int n, q;
int a[MAXN];
int compressed[MAXN];
int answer[MAXN];
int freq[MAXN];
int distinct = 0;
int block_size;

struct Query {
    int l, r, idx;
};

void add(int x) {
    freq[x]++;
    if (freq[x] == 1) distinct++;
}

void remove(int x) {
    freq[x]--;
    if (freq[x] == 0) distinct--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        values[i] = a[i];
    }

    // Coordinate compression
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    for (int i = 0; i < n; i++) {
        compressed[i] = lower_bound(values.begin(), values.end(), a[i]) - values.begin();
    }

    // Read queries
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--; // 0-based indexing
        queries[i] = {l, r, i};
    }

    block_size = sqrt(n);

    // Sort queries by Mo's ordering
    sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
        int block_a = a.l / block_size;
        int block_b = b.l / block_size;
        if (block_a != block_b) return block_a < block_b;
        return ((block_a & 1) ? (a.r > b.r) : (a.r < b.r));
    });

    int currL = 0, currR = -1;

    for (auto& q : queries) {
        while (currL > q.l) add(compressed[--currL]);
        while (currR < q.r) add(compressed[++currR]);
        while (currL < q.l) remove(compressed[currL++]);
        while (currR > q.r) remove(compressed[currR--]);

        answer[q.idx] = distinct;
    }

    for (int i = 0; i < q; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
