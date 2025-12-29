#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    for (long long k = 1; k <= n; k++) {
        // Нийт боломж: (k^2 * (k^2 - 1)) / 2
        long long total_positions = (k * k) * (k * k - 1) / 2;
        
        // Бие бие рүүгээ довтлох боломж: 4 * (k - 1) * (k - 2)
        // k < 3 үед энэ утга 0 эсвэл хасах гарах тул k-г шалгах хэрэгтэй
        long long attacking_positions = 4 * (k - 1) * (k - 2);
        
        if (k < 3) {
            cout << total_positions << "\n";
        } else {
            cout << total_positions - attacking_positions << "\n";
        }
    }

    return 0;
}