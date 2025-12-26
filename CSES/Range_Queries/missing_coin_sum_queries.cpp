#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

/**
 * PROBLEM: Range Missing Coin Sum
 * TECHNIQUE: Offline Queries + Fenwick Tree (BIT)
 * COMPLEXITY: O(Q * log(sum) * log N)
 */

const int MAXN = 200005;
ll bit[MAXN];
int n, q;

void update(int i, int val) {
    for (; i <= n; i += i & -i) bit[i] += val;
}

ll query(int i) {
    ll s = 0;
    for (; i > 0; i -= i & -i) s += bit[i];
    return s;
}

struct Coin {
    int val, id;
};

struct Query {
    int a, b, id;
    ll current_res;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    if (!(cin >> n >> q)) return 0;

    vector<Coin> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i].val;
        coins[i].id = i + 1;
    }
    // Зооснуудыг утгаар нь эрэмбэлэх
    sort(coins.begin(), coins.end(), [](Coin x, Coin y) {
        return x.val < y.val;
    });

    vector<Query> active_queries(q);
    vector<ll> final_ans(q);
    for (int i = 0; i < q; i++) {
        cin >> active_queries[i].a >> active_queries[i].b;
        active_queries[i].id = i;
        active_queries[i].current_res = 0;
    }

    // Хамгийн ихдээ 40-50 удаагийн шүүрдэлт хийнэ
    bool changed = true;
    while (changed) {
        changed = false;
        
        // Асуулгуудыг одоогийн res-ээр нь эрэмбэлэх (Шүүрдэхэд хялбар болгох)
        sort(active_queries.begin(), active_queries.end(), [](const Query& x, const Query& y) {
            return x.current_res < y.current_res;
        });

        for (int i = 1; i <= n; i++) bit[i] = 0; // BIT-ийг цэвэрлэх
        int coin_ptr = 0;

        for (int i = 0; i < q; i++) {
            // Асуулгын res + 1-ээс бага утгатай бүх зоосыг BIT-д нэмнэ
            while (coin_ptr < n && coins[coin_ptr].val <= active_queries[i].current_res + 1) {
                update(coins[coin_ptr].id, coins[coin_ptr].val);
                coin_ptr++;
            }
            
            // [a, b] муж дахь нийлбэрийг олох
            ll new_sum = query(active_queries[i].b) - query(active_queries[i].a - 1);
            if (new_sum > active_queries[i].current_res) {
                active_queries[i].current_res = new_sum;
                changed = true;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        final_ans[active_queries[i].id] = active_queries[i].current_res + 1;
    }

    for (int i = 0; i < q; i++) {
        cout << final_ans[i] << "\n";
    }

    return 0;
}