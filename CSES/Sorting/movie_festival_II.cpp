#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Movie {
    int start, end;
    
    // Дуусах цагаар нь эрэмбэлнэ
    bool operator<(const Movie& other) const {
        return end < other.end;
    }
};

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<Movie> movies(n);
    for (int i = 0; i < n; i++) {
        cin >> movies[i].start >> movies[i].end;
    }

    // 1. Кинонуудаа дуусах цагаар эрэмбэлнэ
    sort(movies.begin(), movies.end());

    // 2. Гишүүдийн дуусах цагийг хадгалах multiset
    // Анх бүх гишүүн 0 цагт сул байна
    multiset<int> members;
    for (int i = 0; i < k; ++i) {
        members.insert(0);
    }

    int count = 0;

    for (const auto& m : movies) {
        // m.start-аас их буюу тэнцүү анхны элементийг хайна
        // upper_bound нь m.start-аас *эрс их* элементийг олдог
        auto it = members.upper_bound(m.start);

        // Хэрэв it нь begin() байвал бүх гишүүдийн дуусах цаг m.start-аас их байна
        // Өөрөөр хэлбэл хэн ч энэ киног үзэж амжихгүй.
        if (it != members.begin()) {
            // it-ийг нэг ухраавал m.start-аас бага буюу тэнцүү хамгийн их утга олдоно
            it--;
            
            // Хуучин дуусах цагийг хасаад, шинэ дуусах цагийг нэмнэ
            members.erase(it);
            members.insert(m.end);
            
            count++;
        }
    }

    cout << count << "\n";

    return 0;
}