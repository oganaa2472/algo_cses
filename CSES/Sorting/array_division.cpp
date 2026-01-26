#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Шалгах функц:
// limit гэсэн дээд хязгаартайгаар массивыг k-аас олон биш хэсэгт хувааж болох уу?
bool check(long long limit, int k, const vector<int>& x) {
    int partitions = 1; // Анхны дэд массив
    long long current_sum = 0;

    for (int val : x) {
        // Хэрэв ганц элемент нь л limit-ээс их байвал шууд боломжгүй
        if (val > limit) return false;

        if (current_sum + val > limit) {
            // Одоогийн дэд массив дүүрсэн, шинийг эхлүүлнэ
            partitions++;
            current_sum = val;
        } else {
            // Одоогийн дэд массивт багтаж байна
            current_sum += val;
        }
    }

    // Хэрэв үүссэн хэсгүүдийн тоо k-аас ихгүй байвал боломжтой
    return partitions <= k;
}

int main() {
    // Хурдан I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> x(n);
    long long max_val = 0;
    long long sum_val = 0;

    for (int i = 0; i < n; i++) {
        cin >> x[i];
        max_val = max(max_val, (long long)x[i]);
        sum_val += x[i];
    }

    // Binary Search
    long long low = max_val;
    long long high = sum_val;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (check(mid, k, x)) {
            // Боломжтой бол илүү багыг хайж үзнэ
            ans = mid;
            high = mid - 1;
        } else {
            // Боломжгүй (capacity багадаад байна), ихэсгэх хэрэгтэй
            low = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}