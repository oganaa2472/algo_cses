#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Энэ мөр нь кодыг илүү хурдан ажиллахад тусалдаг (Compiler optimization)
#pragma GCC optimize("O3")

using namespace std;

int main() {
    // Оролт гаралтыг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> nums(n);
    
    // Оролтын мөрүүдийг уншиж, тоо (integer) болгож хувиргах
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        // Binary string-ийг integer рүү хөрвүүлэх (base 2)
        nums[i] = stoi(s, nullptr, 2);
    }

    int min_dist = k + 1; // Хамгийн ихдээ k байна, тиймээс k+1-ээр эхлүүлнэ

    // Бүх хосыг шалгах
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // XOR хийхэд ялгаатай битүүд нь 1 болно
            int val = nums[i] ^ nums[j];
            
            // 1 болсон битүүдийг тоолох (Hamming distance)
            int dist = __builtin_popcount(val);
            
            if (dist < min_dist) {
                min_dist = dist;
            }
            
            // Хэрэв зай 0 бол үүнээс бага байх боломжгүй тул шууд зогсооно
            if (min_dist == 0) {
                cout << 0 << endl;
                return 0;
            }
        }
    }

    cout << min_dist << endl;

    return 0;
}