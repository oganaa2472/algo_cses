#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
int n; // Ялгаатай тоонуудын тоо (Модны хэмжээ)
vector<int> tree;

// Segment Tree Update: pos байрлалд val утгыг нэмнэ
// node: одоогийн модны зангилаа
// start, end: одоогийн зангилааны хариуцаж буй завсар
void update(int node, int start, int end, int pos, int val) {
    if (start == end) {
        // Навчин (leaf) зангилаа дээр ирлээ
        tree[node] = (tree[node] + val) % MOD;
        return;
    }
    
    int mid = (start + end) / 2;
    // Зүүн хүү рүү явах
    if (pos <= mid) update(2 * node, start, mid, pos, val);
    // Баруун хүү рүү явах
    else update(2 * node + 1, mid + 1, end, pos, val);
    
    // Эцэг зангилааг шинэчлэх (Зүүн + Баруун)
    tree[node] = (tree[2 * node] + tree[2 * node + 1]) % MOD;
}

// Segment Tree Query: [l, r] завсрын нийлбэрийг олно
int query(int node, int start, int end, int l, int r) {
    // Хэрэв хайж буй завсар одоогийн завсартай огт огтлолцохгүй бол
    if (r < start || end < l) return 0;
    
    // Хэрэв одоогийн завсар хайж буй завсар дотор бүрэн багтаж байвал
    if (l <= start && end <= r) return tree[node];
    
    int mid = (start + end) / 2;
    // Зүүн, баруун хүүхдүүдээс нийлбэрийг асууна
    long long p1 = query(2 * node, start, mid, l, r);
    long long p2 = query(2 * node + 1, mid + 1, end, l, r);
    
    return (p1 + p2) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num_inputs;
    if (!(cin >> num_inputs)) return 0;

    vector<int> a(num_inputs);
    vector<int> sorted_a;

    for (int i = 0; i < num_inputs; i++) {
        cin >> a[i];
        sorted_a.push_back(a[i]);
    }

    // --- Coordinate Compression (Утга шахах) ---
    sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());

    auto get_compressed_index = [&](int val) {
        return lower_bound(sorted_a.begin(), sorted_a.end(), val) - sorted_a.begin() + 1;
    };
    
    // Segment Tree-ийн хэмжээ
    n = sorted_a.size();
    tree.resize(4 * n + 1, 0); // Модны хэмжээг 4*N гэж авдаг

    // --- Үндсэн Логик ---
    for (int x : a) {
        int idx = get_compressed_index(x);
        
        // 1. Query: [1, idx-1] завсрын нийлбэрийг олно
        // Энэ нь x-ээс бага тоогоор төгссөн дарааллын тоо
        int count = 0;
        if (idx > 1) {
            count = query(1, 1, n, 1, idx - 1);
        }
        
        // 2. Одоогийн тоог нэмэх (+1)
        int current_ways = (count + 1) % MOD;
        
        // 3. Update: Segment Tree-ийн idx байрлалд current_ways-ийг нэмнэ
        update(1, 1, n, idx, current_ways);
    }

    // Бүх боломжийн нийлбэр нь модны орой (root) дээр байгаа
    cout << tree[1] << "\n";

    return 0;
}