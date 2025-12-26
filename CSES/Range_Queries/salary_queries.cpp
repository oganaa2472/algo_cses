#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_VAL = 600005; // n + 2q max unique values
int tree[4 * MAX_VAL];
int n, q;

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] += val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0;
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
}

struct Query {
    char type;
    int a, b;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> q;
    vector<int> salaries(n + 1);
    vector<int> coords;
    for (int i = 1; i <= n; i++) {
        cin >> salaries[i];
        coords.push_back(salaries[i]);
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].type >> queries[i].a >> queries[i].b;
        coords.push_back(queries[i].a);
        coords.push_back(queries[i].b);
    }

    // Coordinate Compression
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    auto get_rank = [&](int val) {
        return lower_bound(coords.begin(), coords.end(), val) - coords.begin() + 1;
    };

    int m = coords.size();
    for (int i = 1; i <= n; i++) {
        update(1, 1, m, get_rank(salaries[i]), 1);
    }

    for (int i = 0; i < q; i++) {
        if (queries[i].type == '!') {
            int k = queries[i].a;
            int x = queries[i].b;
            // Remove old salary, add new one
            update(1, 1, m, get_rank(salaries[k]), -1);
            salaries[k] = x;
            update(1, 1, m, get_rank(salaries[k]), 1);
        } else {
            cout << query(1, 1, m, get_rank(queries[i].a), get_rank(queries[i].b)) << "\n";
        }
    }

    return 0;
}