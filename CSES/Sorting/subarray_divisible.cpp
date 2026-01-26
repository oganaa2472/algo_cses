#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Үлдэгдлүүдийг тоолох массив (map ашиглахаас хурдан)
    // count[x] = x үлдэгдэл хэдэн удаа гарсныг хадгална
    vector<long long> mod_counts(n, 0);
    
    // Анхны нөхцөл: Нийлбэр 0 байх (үлдэгдэл 0) нэг тохиолдол байна гэж үздэг
    mod_counts[0] = 1;

    long long current_sum = 0;
    long long ans = 0;

    for (int x : a) {
        current_sum += x;
        
        // C++ -д сөрөг тооны modulo сөрөг гардаг тул эерэг болгох трик
        long long remainder = (current_sum % n + n) % n;
        
        // Хэрэв энэ үлдэгдэл өмнө нь гарч байсан бол
        // тэр тоогоор дэд массив үүсгэх боломжтой
        ans += mod_counts[remainder];
        
        // Одоогийн үлдэгдлийг бүртгэнэ
        mod_counts[remainder]++;
    }

    cout << ans << "\n";

    return 0;
}