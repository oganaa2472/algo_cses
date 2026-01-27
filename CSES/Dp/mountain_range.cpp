#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> h(n);
    // pair ашиглан {өндөр, индекс} хадгална (эрэмбэлэхэд хэрэгтэй)
    vector<pair<int, int>> sorted_indices(n);

    for (int i = 0; i < n; i++) {
        cin >> h[i];
        sorted_indices[i] = {h[i], i};
    }

    // 1. Зүүн талын хамгийн ойрын өндөр уулыг олох (L)
    vector<int> L(n, -1);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        // Одоогийн уулнаас намхан уулсыг стекээс гаргана
        while (!s.empty() && h[s.top()] <= h[i]) {
            s.pop();
        }
        if (!s.empty()) {
            L[i] = s.top();
        }
        s.push(i);
    }

    // 2. Баруун талын хамгийн ойрын өндөр уулыг олох (R)
    vector<int> R(n, -1);
    while (!s.empty()) s.pop(); // Стекийг цэвэрлэх
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && h[s.top()] <= h[i]) {
            s.pop();
        }
        if (!s.empty()) {
            R[i] = s.top();
        }
        s.push(i);
    }

    // 3. Өндрөөр нь буурахаар эрэмбэлэх
    // greater<pair> ашиглан буурахаар эрэмбэлнэ
    sort(sorted_indices.begin(), sorted_indices.end(), greater<pair<int, int>>());

    // 4. DP тооцоолол
    vector<int> dp(n, 0);
    int max_mountains = 0;

    for (auto p : sorted_indices) {
        int u = p.second; // Уулын индекс
        
        // Одоогийн уул дээр ирэх хамгийн урт замыг олно
        int from_left = (L[u] != -1) ? dp[L[u]] : 0;
        int from_right = (R[u] != -1) ? dp[R[u]] : 0;
        
        dp[u] = 1 + max(from_left, from_right);
        
        max_mountains = max(max_mountains, dp[u]);
    }

    cout << max_mountains << "\n";

    return 0;
}