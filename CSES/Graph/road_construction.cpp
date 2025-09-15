
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, size;
    int components;
    int largest;

    DSU(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
        components = n;
        largest = 1;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // path compression
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return; // already in same set

        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        largest = max(largest, size[a]);
        components--;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dsu.unite(a, b);
        cout << dsu.components << " " << dsu.largest << "\n";
    }
}
