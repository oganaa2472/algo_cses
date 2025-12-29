#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long result = 1;
    long long mod = 1000000007;

    // 2-ыг n удаа үржүүлэхдээ алхам бүрт модуль авна
    for (int i = 0; i < n; i++) {
        result = (result * 2) % mod;
    }

    cout << result << endl;

    return 0;
}