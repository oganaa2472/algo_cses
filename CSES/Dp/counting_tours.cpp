#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1000005;

// dp[i][0] -> Салсан (хоёр жижиг блоктой)
// dp[i][1] -> Нэгдсэн (нэг том блоктой)
long long dp[MAXN][2];

void precompute() {
    // Суурь нөхцөл (Өндөр = 1)
    dp[1][0] = 1; 
    dp[1][1] = 1;

    for (int i = 1; i < MAXN - 1; i++) {
        // Төлөв 0 (Салсан):
        // Өмнөх Салсанаас (0) -> 4 аргаар (2 сунгах + 2 шинэ)
        // Өмнөх Нэгдсэнээс (1) -> 1 аргаар (хоёр жижиг болж салах)
        dp[i+1][0] = (dp[i][0] * 4 + dp[i][1]) % MOD;

        // Төлөв 1 (Нэгдсэн):
        // Өмнөх Салсанаас (0) -> 1 аргаар (нэгдэх)
        // Өмнөх Нэгдсэнээс (1) -> 2 аргаар (сунгах + шинэ том)
        dp[i+1][1] = (dp[i][0] + dp[i][1] * 2) % MOD;
    }
}

void solve() {
    int n;
    cin >> n;
    // Хариу: Салсан + Нэгдсэн боломжуудын нийлбэр
    cout << (dp[n][0] + dp[n][1]) % MOD << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Програм эхлэхэд бүх хариуг нэг удаа тооцоолно
    precompute();

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}