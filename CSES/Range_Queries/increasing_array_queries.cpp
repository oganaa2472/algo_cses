#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * PROBLEM: Increasing Subarray Sum Queries
 * Technique: Segment Tree with recursive sum calculation
 * Time Complexity: O(Q log^2 N)
 */

typedef long long ll;

const int MAXN = 200005;
ll tree[4 * MAXN], sum[4 * MAXN];
int n, q;
ll x[MAXN], pref[MAXN];

// Энэ функц нь node-ийн мужид байгаа тоонуудыг V утгаар хязгаарлавал 
// үүсэх нийлбэрийг олдог
ll get_sum(int node, int start, int end, ll V) {
    if (tree[node] <= V) {
        return (ll)(end - start + 1) * V;
    }
    if (start == end) {
        return max(V, tree[node]);
    }
    int mid = (start + end) / 2;
    // Хэрэв зүүн хүүгийн хамгийн их утга V-ээс бага бол зүүн тал бүхэлдээ V болно
    if (tree[2 * node] <= V) {
        return (ll)(mid - start + 1) * V + get_sum(2 * node + 1, mid + 1, end, V);
    } else {
        // Үгүй бол баруун талын нийлбэрийг (sum[node] - sum[2*node]) ашиглана
        return get_sum(2 * node, start, mid, V) + (sum[node] - sum[2 * node]);
    }
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = sum[node] = x[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    // sum[node] нь тухайн мужийг өсдөг болгосны дараах нийлбэрийг хадгална
    sum[node] = sum[2 * node] + get_sum(2 * node + 1, mid + 1, end, tree[2 * node]);
}

// Асуулгад хариулахдаа бид зүүн талаас ирсэн хамгийн их утгыг (V) дамжуулна
pair<ll, ll> query(int node, int start, int end, int l, int r, ll V) {
    if (l <= start && end <= r) {
        ll res_sum = get_sum(node, start, end, V);
        return {res_sum, max(V, tree[node])};
    }
    int mid = (start + end) / 2;
    if (r <= mid) return query(2 * node, start, mid, l, r, V);
    if (l > mid) return query(2 * node + 1, mid + 1, end, l, r, V);

    pair<ll, ll> left_res = query(2 * node, start, mid, l, r, V);
    pair<ll, ll> right_res = query(2 * node + 1, mid + 1, end, l, r, left_res.second);
    
    return {left_res.first + right_res.first, right_res.second};
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        pref[i] = pref[i - 1] + x[i];
    }

    build(1, 1, n);

    while (q--) {
        int a, b;
        cin >> a >> b;
        pair<ll, ll> res = query(1, 1, n, a, b, 0);
        // Нийт нийлбэрээс анхны массивын нийлбэрийг хасна
        ll actual_sum = pref[b] - pref[a - 1];
        cout << res.first - actual_sum << "\n";
    }

    return 0;
}