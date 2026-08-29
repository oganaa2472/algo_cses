#include <iostream>
using namespace std;

long long solve(long long n, long long k) {
    // 1. Суурь нөхцөл: Ганцхан хүүхэд үлдсэн бол тэр нь 1 дэх хүүхэд байна
    if (n == 1) return 1;

    // 2. Эхний тойрогт хасагдах боломжтой хүүхдийн тоо
    long long removed_in_first_round = (n + 1) / 2;

    // Хэрэв k нь эхний тойрогт хасагдах хүүхдүүдийн дотор байвал:
    if (k <= n / 2) {
        return 2 * k; // 2, 4, 6, 8... гэж хасагдана
    }

    // 3. Дараагийн тойрог руу шилжих (Дэд бодлого)
    long long res = solve(n - n / 2, k - n / 2);

    // 4. Буцааж анхны дугаар руу шилжүүлэх
    if (n % 2 == 0) {
        return 2 * res - 1;
    } else {
        if (res == 1) return n; // Сондгой үед сүүлийн элемент хасагдах тусгай тохиолдол
        return 2 * res - 3;
    }
}

int main() {
    // Хурдан оролт, гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--) {
        long long n, k;
        cin >> n >> k;
        cout << solve(n, k) << "\n";
    }
    return 0;
}