#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 100005;

vector<int> adj[MAXN];
int in_degree[MAXN];
int dp[MAXN];

int main() {
    // Input хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++; // Орсон ирмэгийн тоог тоолно
    }

    // Topological Sort хийх Queue
    queue<int> q;
    
    // In-degree нь 0 байгаа бүх цэгийг Queue-д хийнэ
    // Анхаар: Зөвхөн 1 биш, бүх 0 degree-тэйг хийх хэрэгтэй (Графын бүтцийг эвдэхгүйн тулд)
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    // DP эхлүүлэх
    dp[1] = 1; 

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // Шилжилт: u-ээс v рүү очиж байгаа тул u-ийн замын тоог v дээр нэмнэ
            dp[v] = (dp[v] + dp[u]) % MOD;

            // Kahn's Algorithm: In-degree хасна
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Хариу: n-р үед очих замын тоо
    cout << dp[n] << endl;

    return 0;
}