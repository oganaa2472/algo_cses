#include <iostream>
#include <vector>

using namespace std;

// K <= 10^9 тул 2^30 > 10^9. Log утга нь 30 байхад хангалттай.
const int MAXN = 200005;
const int LOG = 30;

// up[i][j] -> i гарагаас 2^j алхам хийхэд очих газар
int up[MAXN][LOG];

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // 1. Initial State (1 алхам буюу 2^0)
    for (int i = 1; i <= n; i++) {
        cin >> up[i][0];
    }

    // 2. Binary Lifting Table байгуулах (Preprocessing)
    // j нь зэрэг (exponent), i нь гараг
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            // i-ээс 2^j нүүх = (i-ээс 2^(j-1) нүүгээд) + (тэндээсээ дахин 2^(j-1) нүүх)
            up[i][j] = up[ up[i][j-1] ][j-1];
        }
    }

    // 3. Query боловсруулах
    while (q--) {
        int x, k;
        cin >> x >> k;

        // k-г битүүдээр нь задалж үсрэх
        for (int j = 0; j < LOG; j++) {
            // Хэрэв k-гийн j-р бит нь 1 байвал (жишээ нь k=5 буюу 101 байвал 0 болон 2-р бит)
            if ((k >> j) & 1) {
                x = up[x][j]; // x-ийг 2^j алхамаар урагшлуулна
            }
        }

        cout << x << "\n";
    }

    return 0;
}