#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Range {
    int l, r, id;
    
    // operator< нь sort функцэд хэрхэн эрэмбэлэхийг заана
    bool operator<(const Range& other) const {
        if (l == other.l) {
            // Хэрэв эхлэл тэнцүү бол төгсгөлөөр БУУРАХААР
            return r > other.r;
        }
        // Эсвэл эхлэлээр ӨСӨХӨӨР
        return l < other.l;
    }
};

int main() {
    // Хурдан I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<Range> ranges(n);
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
        ranges[i].id = i; // Анхны байрлалыг хадгалах
    }

    // 1. Эрэмбэлэх
    sort(ranges.begin(), ranges.end());

    // Хариуг хадгалах массивууд (0 эсвэл 1)
    vector<int> contains(n, 0);
    vector<int> contained_by(n, 0);

    // 2. "Contains others" шалгах (Хойноос урагшаа)
    // min_r: Баруун талд тааралдсан хамгийн бага төгсгөлийн цэг
    int min_r = 2e9; // Маш том тоо
    for (int i = n - 1; i >= 0; i--) {
        if (ranges[i].r >= min_r) {
            contains[ranges[i].id] = 1;
        }
        min_r = min(min_r, ranges[i].r);
    }

    // 3. "Contained by others" шалгах (Урдаас хойшоо)
    // max_r: Зүүн талд тааралдсан хамгийн их төгсгөлийн цэг
    int max_r = 0; // Маш бага тоо
    for (int i = 0; i < n; i++) {
        if (ranges[i].r <= max_r) {
            contained_by[ranges[i].id] = 1;
        }
        max_r = max(max_r, ranges[i].r);
    }

    // 4. Хариуг хэвлэх
    for (int i = 0; i < n; i++) cout << contains[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << contained_by[i] << " ";
    cout << "\n";

    return 0;
}