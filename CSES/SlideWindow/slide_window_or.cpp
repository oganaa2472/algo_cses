#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 1. Стандарт Input/Output-ийг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    if (!(cin >> n >> k)) return 0;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    // 2. Генератораар дарааллын элементүүдийг үүсгэн хадгалах
    vector<int> arr(n);
    arr[0] = x;
    for (int i = 1; i < n; i++) {
        // 1LL ашиглаж (a * arr[i-1]) үржвэр 32-bit int-ээс давахаас сэргийлнэ
        arr[i] = (a * 1LL * arr[i - 1] + b) % c;
    }

    vector<int> pref(n), suf(n);

    // 3. Prefix OR байгуулах (Блок бүрийн хувьд зүүнээс баруун тийш)
    for (int i = 0; i < n; i++) {
        if (i % k == 0) { // Шинэ блок эхэлж байвал тухайн элементийг шууд авна
            pref[i] = arr[i];
        } else { // Блок дотроо бол өмнөх бичсэн OR дээр нэмж OR хийнэ
            pref[i] = pref[i - 1] | arr[i];
        }
    }

    // 4. Suffix OR байгуулах (Блок бүрийн хувьд баруунаас зүүн тийш)
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1 || (i + 1) % k == 0) { // Блокын төгсгөл эсвэл массив төгсөж байвал
            suf[i] = arr[i];
        } else { // Блок дотроо араас нь урагшаа цуглуулна
            suf[i] = suf[i + 1] | arr[i];
        }
    }

    // 5. Цонх (Window) бүрийн OR-ийг O(1)-д авч, XOR нэгтгэл хийх
    int ans = 0;
    for (int i = 0; i <= n - k; i++) {
        int r = i + k - 1; // Цонхны баруун төгсгөлийн индекс
        
        // Зүүн блокын арын хэсэг (suf[i]) болон баруун блокын урд хэсгийг (pref[r]) нийлүүлнэ
        int window_or = suf[i] | pref[r];
        
        ans ^= window_or;
    }

    // 6. Эцсийн хариуг хэвлэх
    cout << ans << "\n";

    return 0;
}