#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 20;

// dp[mask][city]: mask доторх хотуудаар дамжаад city дээр ирэх замын тоо
// 1 << 20 нь ойролцоогоор 1 сая. 20 * 1 сая = 20 сая төлөв. (Санах ойд багтана)
long long dp[1 << MAXN][MAXN];
vector<int> adj[MAXN]; // Reverse adjacency list: v -> u гэж хадгална (u руу v-ээс ирсэн)

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // 0-based index руу шилжүүлэх
        u--; v--;
        // Бид u руу хаанаас ирснийг хайх тул 'v' рүү 'u' орж ирнэ гэж хадгална
        // Энэ нь DP шилжилт хийхэд хялбар болгоно
        adj[v].push_back(u);
    }

    // Base Case: Эхний хотод (index 0) байна, mask нь зөвхөн 0-р битийг агуулна
    dp[1][0] = 1;

    // Бүх mask-аар гүйнэ
    for (int mask = 2; mask < (1 << n); mask++) {
        // Хэрэв mask нь эхний хотыг агуулаагүй бол энэ нь хүчингүй зам (учир нь заавал 1-ээс эхлэх ёстой)
        if (!(mask & 1)) continue;

        // ЧУХАЛ НӨХЦӨЛ:
        // Хэрэв mask нь N-р хотыг (index n-1) агуулсан мөртлөө
        // Бүх хотыг агуулаагүй (mask != (1<<n)-1) байвал энэ замыг тооцохгүй.
        // Учир нь Lehmälä дээр очсон л бол аялал дуусах ёстой.
        if ((mask & (1 << (n - 1))) && mask != ((1 << n) - 1)) continue;

        // Одоогийн mask-д байгаа 'u' хот бүрийн хувьд
        for (int u = 0; u < n; u++) {
            if (mask & (1 << u)) {
                // Өмнөх mask-ийг гаргаж авах (u-г хасна)
                int prev_mask = mask ^ (1 << u);
                if (prev_mask == 0) continue;

                // u руу ирж болох v хотуудыг шалгах
                for (int v : adj[u]) {
                    if (prev_mask & (1 << v)) {
                        dp[mask][u] = (dp[mask][u] + dp[prev_mask][v]) % MOD;
                    }
                }
            }
        }
    }

    // Хариу: Бүх хотыг дайрсан (FULL MASK) бөгөөд N-1 дээр төгссөн зам
    cout << dp[(1 << n) - 1][n - 1] << endl;

    return 0;
}