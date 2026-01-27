#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MOD = 1e9 + 7;

// Fenwick Tree (Binary Indexed Tree) бүтэц
vector<int> bit;
int n;

// Утга нэмэх функц (Point Update)
void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] = (bit[idx] + val) % MOD;
    }
}

// Нийлбэр олох функц (Prefix Sum Query)
int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum = (sum + bit[idx]) % MOD;
    }
    return sum;
}

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num_inputs;
    if (!(cin >> num_inputs)) return 0;

    vector<int> a(num_inputs);
    vector<int> sorted_a; // Шахахад (compression) ашиглана

    for (int i = 0; i < num_inputs; i++) {
        cin >> a[i];
        sorted_a.push_back(a[i]);
    }

    // 1. Coordinate Compression (Координат шахах)
    // Тоонуудыг эрэмбэлж, давхардлыг арилгана
    sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());

    // Map ашиглан жинхэнэ утгыг шахсан утгатай холбоно
    // Жишээ нь: 10 -> 1, 50 -> 2, 100 -> 3 гэх мэт
    auto get_compressed_index = [&](int val) {
        // lower_bound нь тухайн тоо sorted жагсаалтын хэдэд байгааг олно (1-ээс эхлүүлнэ)
        return lower_bound(sorted_a.begin(), sorted_a.end(), val) - sorted_a.begin() + 1;
    };

    // Fenwick tree-г n хэмжээтэй үүсгэнэ (n нь ялгаатай тоонуудын тоо болно)
    n = sorted_a.size() + 1; // n-ийг BIT-ийн хэмжээгээр шинэчлэв
    bit.assign(n + 1, 0);

    // 2. Үндсэн тооцоолол
    for (int x : a) {
        int idx = get_compressed_index(x);
        
        // idx-ээс бага утгатай (idx-1) бүх дарааллын тоог олно
        int count = query(idx - 1);
        
        // Одоогийн тоог өөрийг нь нэмнэ (+1)
        int current_ways = (count + 1) % MOD;
        
        // Fenwick tree-г шинэчилнэ
        update(idx, current_ways);
    }

    // 3. Нийт хариу: Бүх боломжийн нийлбэр
    // query(n) нь мод дахь бүх утгын нийлбэрийг өгнө
    cout << query(n) << "\n";

    return 0;
}