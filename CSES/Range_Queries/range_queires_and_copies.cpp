#include <iostream>
#include <vector>

using namespace std;

/**
 * PROBLEM: Range Queries and Copies (CSES)
 * Technique: Persistent Segment Tree
 * Time Complexity: O((N + Q) log N)
 * Space Complexity: O((N + Q) log N)
 */

typedef long long ll;

struct Node {
    ll sum;
    Node *l, *r;

    Node(ll v) : sum(v), l(nullptr), r(nullptr) {}
    Node(Node *l, Node *r) : l(l), r(r) {
        sum = 0;
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

const int MAXN = 200005;
Node* roots[MAXN]; // Массивын хувилбар бүрийн язгуур зангилаа
int n, q;

// Анхны модыг байгуулах
Node* build(const vector<int>& a, int start, int end) {
    if (start == end) return new Node(a[start]);
    int mid = (start + end) / 2;
    return new Node(build(a, start, mid), build(a, mid + 1, end));
}

// Утга өөрчлөх (Шинэ зангилаанууд үүсгэнэ)
Node* update(Node* node, int start, int end, int idx, int val) {
    if (start == end) return new Node(val);
    int mid = (start + end) / 2;
    if (idx <= mid) {
        return new Node(update(node->l, start, mid, idx, val), node->r);
    } else {
        return new Node(node->l, update(node->r, mid + 1, end, idx, val));
    }
}

// Нийлбэр олох
ll query(Node* node, int start, int end, int l, int r) {
    if (start > r || end < l) return 0;
    if (l <= start && end <= r) return node->sum;
    int mid = (start + end) / 2;
    return query(node->l, start, mid, l, r) + query(node->r, mid + 1, end, l, r);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    int versions = 1;
    roots[1] = build(a, 1, n);

    while (q--) {
        int t; cin >> t;
        if (t == 1) { // Set value
            int k, a, x;
            cin >> k >> a >> x;
            roots[k] = update(roots[k], 1, n, a, x);
        } else if (t == 2) { // Get sum
            int k, a, b;
            cin >> k >> a >> b;
            cout << query(roots[k], 1, n, a, b) << "\n";
        } else { // Copy array
            int k; cin >> k;
            roots[++versions] = roots[k];
        }
    }

    return 0;
}