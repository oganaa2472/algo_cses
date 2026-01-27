#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
int n, m;

// row: Одоогийн баганын хэддүгээр мөрийг шалгаж байгаа
// current_mask: Өмнөх баганаас энэ багана руу орж ирсэн илүүдэл хэсгүүд
// next_mask: Энэ баганаас дараагийн багана руу гарах илүүдэл хэсгүүд
// count: current_mask төлөвт хүрсэн боломжийн тоо
// next_dp: Дараагийн баганын DP хүснэгт
void generate_next_masks(int row, int current_mask, int next_mask, long long count, vector<long long>& next_dp) {
    // Хэрэв баганын бүх мөрийг шалгаж дууссан бол
    if (row == n) {
        next_dp[next_mask] = (next_dp[next_mask] + count) % MOD;
        return;
    }

    // Тохиолдол 1: Өмнөх баганаас домино орж ирсэн (Энэ нүд дүүрсэн)
    if ((current_mask >> row) & 1) {
        // Энд шинэ домино тавих боломжгүй, дараагийн мөр рүү шилжинэ.
        // next_mask-ийн 'row' бит 0 хэвээр үлдэнэ.
        generate_next_masks(row + 1, current_mask, next_mask, count, next_dp);
    } 
    else {
        // Тохиолдол 2: Энэ нүд хоосон байна, заавал дүүргэх ёстой.

        // Сонголт А: Хэвтээ домино тавих (Horizontal)
        // Энэ баганаас дараагийн багана руу цухуйна -> next_mask-д 1 нэмнэ
        generate_next_masks(row + 1, current_mask, next_mask | (1 << row), count, next_dp);

        // Сонголт Б: Босоо домино тавих (Vertical)
        // Доод талын нүд (row+1) хоосон байх ёстой
        if (row + 1 < n && !((current_mask >> (row + 1)) & 1)) {
            // Энэ болон дараагийн мөрийг таглана. next_mask-д нөлөөлөхгүй.
            generate_next_masks(row + 2, current_mask, next_mask, count, next_dp);
        }
    }
}

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    // dp[mask] = Одоогийн баганад mask төлөвтэй ирэх боломжийн тоо
    vector<long long> dp(1 << n, 0);
    
    // Суурь нөхцөл: 0-р баганад өмнөхөөс орж ирсэн зүйл байхгүй (mask = 0)
    dp[0] = 1;

    // Багана бүрээр гүйнэ
    for (int j = 0; j < m; j++) {
        vector<long long> next_dp(1 << n, 0);
        
        // Өмнөх баганын бүх боломжит mask-аар гүйнэ
        for (int mask = 0; mask < (1 << n); mask++) {
            // Хэрэв энэ mask-д хүрэх боломж байгаа бол (dp[mask] > 0)
            // Дараагийн баганын mask-уудыг үүсгэнэ
            if (dp[mask] > 0) {
                generate_next_masks(0, mask, 0, dp[mask], next_dp);
            }
        }
        // DP шинэчлэх
        dp = next_dp;
    }

    // Хариу: Сүүлийн багана дуусахад дараагийн багана руу юу ч илүү гараагүй байх ёстой (mask = 0)
    cout << dp[0] << "\n";

    return 0;
}