#include <bits/stdc++.h>
using namespace std;

typedef int item;

struct segtree {
    int size;
    vector<item> tree;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, 0);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] += v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
            add(i, v, 2 * x + 1, lx, m);
        else
            add(i, v, 2 * x + 2, m, rx);
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        return sum(l, r, 2 * x + 1, lx, m) + sum(l, r, 2 * x + 2, m, rx);
    }

    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    
    set<int> dist_sal;
    vector<int> emp(n);
    
    for (int i = 0; i < n; i++) {
        cin >> emp[i];
        dist_sal.insert(emp[i]);
    }

    vector<tuple<char, int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        char type;
        int a, b;
        cin >> type >> a >> b;
        queries[i] = {type, a, b};
        if (type == '!') dist_sal.insert(b);
        else {
            dist_sal.insert(a);
            dist_sal.insert(b);
        }
    }

    // Coordinate compression
    map<int, int> compress;
    vector<int> rev;
    int id = 0;
    for (int val : dist_sal) {
        compress[val] = id++;
        rev.push_back(val);
    }

    segtree seg;
    seg.init(id);

    vector<int> current(n); // store compressed salary index per employee

    for (int i = 0; i < n; i++) {
        current[i] = compress[emp[i]];
        seg.add(current[i], 1);
    }

    for (auto [type, a, b] : queries) {
        if (type == '!') {
            int emp_id = a - 1;
            int new_salary = compress[b];

            // remove old salary
            seg.add(current[emp_id], -1);

            // update and add new salary
            current[emp_id] = new_salary;
            seg.add(new_salary, 1);
        } else {
            auto it_l = compress.lower_bound(a);
            auto it_r = compress.upper_bound(b);

            if (it_l == compress.end()) {
                cout << "0\n";
                continue;
            }

            int l = it_l->second;
            int r = (it_r == compress.end()) ? id : it_r->second;
            cout << seg.sum(l, r) << '\n';
        }
    }

    return 0;
}
