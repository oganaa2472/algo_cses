#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Нийт 2^n ширхэг дараалал байна
    int total_strings = 1 << n;

    for (int i = 0; i < total_strings; i++) {
        // i-р тоог Грей код руу хөрвүүлэх томьёо
        int gray_val = i ^ (i >> 1);
        
        // n урттай бит болгон хөрвүүлж хэвлэх
        string s = "";
        for (int j = n - 1; j >= 0; j--) {
            if ((gray_val >> j) & 1) {
                s += '1';
            } else {
                s += '0';
            }
        }
        cout << s << "\n";
    }

    return 0;
}