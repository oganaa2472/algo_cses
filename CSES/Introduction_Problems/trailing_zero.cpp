#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    long long count = 0;
    
    // n-ийг 5-ын зэрэгтүүдэд хуваан нийлбэрийг олно
    // Жишээ нь: n/5 + n/25 + n/125 + ...
    for (long long i = 5; n / i >= 1; i *= 5) {
        count += n / i;
    }

    cout << count << endl;

    return 0;
}