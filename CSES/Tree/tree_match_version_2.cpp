#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Модны оройнуудын холбоосыг хадгалах хөршүүдийн жагсаалт
vector<vector<int>> adj;

// dp[u][0] - u оройг хүүхэдтэй нь хослоогүй үеийн хамгийн их хосолт
// dp[u][1] - u оройг аль нэг хүүхэдтэй нь хосолсон үеийн хамгийн их хосолт
vector<vector<int>> dp;

void dfs(int u, int p) {
    dp[u][0] = 0;
    dp[u][1] = 0;
    
    int sum_children = 0;
    
    // Эхлээд бүх хүүхдүүдийн хувьд DFS дуудаж, DP утгуудыг нь бодож олно
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            // Хүүхдүүдээс авч болох хамгийн их хосолтуудын нийлбэр
            sum_children += max(dp[v][0], dp[v][1]);
        }
    }
    
    // u-г доош нь ямар нэгэн хүүхэдтэй нь хослуулахгүй үеийн утга
    dp[u][0] = sum_children;
    
    // u-г аль нэг хүүхэд v-тэй нь сонгож хослох үеийн утга
    for (int v : adj[u]) {
        if (v != p) {
            // v-г сонгож хосолбол үүсэх боломжит хосолтын тоо
            int current_matching = sum_children - max(dp[v][0], dp[v][1]) + dp[v][0] + 1;
            dp[u][1] = max(dp[u][1], current_matching);
        }
    }
}

int main() {
    // Хурдан оролт/гаралт хийх тохиргоо
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    // Оройн тоог автоматаар унших
    if (!(cin >> n)) return 0;
    
    adj.assign(n + 1, vector<int>());
    dp.assign(n + 1, vector<int>(2, 0));
    
    // Мод нь n оройтой бол n-1 ширхэг ирмэгтэй байна
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v; // Ирмэгээр холбогдсон хоёр оройг унших
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 1-р оройг үндэс (root) болгон DFS ажиллуулна. Эцэг оройг нь 0 гэж өгнө.
    dfs(1, 0);
    
    // Хамгийн их хосолтын тоо нь үндэс оройн хувьд авч болох хамгийн их утга байна
    int max_matching = max(dp[1][0], dp[1][1]);
    
    cout << max_matching << "\n";
    
    return 0;
}