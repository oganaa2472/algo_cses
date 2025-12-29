#include <iostream>

using namespace std;

/**
 * @param n     Зөөх дискний тоо
 * @param from  Эхлэх багана (1, 2, эсвэл 3)
 * @param to    Очих багана
 * @param aux   Туслах багана
 */
void solve_hanoi(int n, int from, int to, int aux) {
    if (n == 0) return;

    // 1. Дээд талын n-1 дискийг туслах багана руу зөөх
    solve_hanoi(n - 1, from, aux, to);

    // 2. Үлдсэн хамгийн том дискийг зорилтот багана руу зөөх
    cout << from << " " << to << "\n";

    // 3. Туслах багана дээр байгаа n-1 дискийг зорилтот багана руу зөөх
    solve_hanoi(n - 1, aux, to, from);
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    // Нийт нүүдлийн тоог (2^n - 1) хэвлэх
    // (1 << n) нь 2-ын n зэргийг маш хурдан тооцоолно
    cout << (1 << n) - 1 << "\n";

    // Бодлогыг 1-р баганаас 3-р багана руу 2-ыг ашиглан бодох
    solve_hanoi(n, 1, 3, 2);

    return 0;
}