#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // Оролт, гаралыг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n)) return 0;

    // Дунд талын элементийн байрлал (1-ээс эхэлсэн индекс)
    long long target_rank = (n * n + 1) / 2;

    long long low = 1;
    long long high = n * n;
    long long ans = high;

    // Хариун дээр Binary Search хийх
    while (low <= high) {
        long long mid = low + (high - low) / 2;

        // mid-ээс бага буюу тэнцүү хэдэн тоо байгааг тоолох
        long long count = 0;
        for (long long i = 1; i <= n; ++i) {
            count += min(n, mid / i);
        }

        // Хэрэв олдон элементүүд хангалттай олон байвал хариуг шинэчлээд бага утга руу хайна
        if (count >= target_rank) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}