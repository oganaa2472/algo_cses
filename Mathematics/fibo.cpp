#include <iostream>
#include <cmath>

using namespace std;

int fb(int num) {
    long long f = 0, f1 = 1, result = 0;
    const long long MOD = static_cast<long long>(exp(9)) + 7;

    for (int i = 1; i <= num; i++) {
        result = f + f1;
        f = f1;
        f1 = result;
    }

    return f % MOD;
}

int main() {
    int num;
   
    cin >> num;
    cout << fb(num) << endl;
    return 0;
}
