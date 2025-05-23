#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int mod = 1e9+7;
    int n,m;
    cin>>n>>m;

    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n+1,0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        in_degree[v]++; 
    }
   
   
    queue<int> q;
    for(int i = 1;i<=n;i++) {
        if(in_degree[i]==0) q.push(i);
    }
    vector<int> dp(n+1,0);
    // vector<int> pred(n+1,-1);
    dp[1] = 1;
    
    // Топологийн эрэмбэлэлтийн дагуу хотуудыг боловсруулж, DP утгуудыг тооцоолно.
    while (!q.empty()) {
        int u = q.front(); // Queue-ээс эхний хотыг (зангилааг) гаргаж авна.
        q.pop();

        // Хэрэв u хот нь 1-р хотоос хүрч болох зам дээр байгаа бол (dp[u] нь 0-ээс их бол)
        if (dp[u] > 0) {
            // u хотоос шууд нисдэг бүх хотуудыг (хөрш зангилаануудыг) v гэж авч үзнэ.
            for (int v : adj[u]) {
                // Хэрэв u-р хот хүртэлх хамгийн олон хот дамжсан зам дээр v-г нэмэх нь
                // v-р хот хүртэлх одоогийн хамгийн их дамжсан хотын тооноос их бол:
                
               dp[v] = (dp[v] + dp[u]) % mod;
                // v-р хот хүртэлх хамгийн их дамжсан хотын тоог шинэчилнэ.
                  
                in_degree[v]--;
                // Хэрэв v хотын орох ирмэгийн тоо 0 болвол, Queue-д хийнэ.
                if (in_degree[v] == 0) {
                    q.push(v);
                }
            }
        } else { // Хэрэв u хот нь 1-р хотоос хүрч болох зам дээр байхгүй бол (dp[u] == 0)
            // Энэ хотоос гарч буй ирмэгүүдийг топологийн эрэмбэлэлтийн хувьд боловсруулах хэрэгтэй ч,
            // 1-ээс эхэлсэн замын DP утгыг эндээс шинэчлэхгүй.
            for (int v : adj[u]) {
                 in_degree[v]--;
                 if (in_degree[v] == 0) {
                     q.push(v);
                 }
             }
        }
    }
    if (dp[n] == 0 && n > 1) {
        std::cout << "0" << std::endl;
    } else {
        // Хамгийн олон хот дамжсан замын уртыг хэвлэнэ (хотын тоо).
        std::cout << dp[n] << std::endl;

    }



    return 0;
}