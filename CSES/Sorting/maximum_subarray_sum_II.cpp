#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long a, b; // Урт нь int багтах ч аюулгүй байдлын үүднээс
    if (!(cin >> n >> a >> b)) return 0;

    // Угтвар нийлбэр хадгалах массив (1-based index)
    vector<long long> p(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        p[i] = p[i - 1] + x;
    }

    multiset<long long> s;
    // Хариу хамгийн багадаа сөрөг тоо байж болох тул маш бага тооноос эхэлнэ
    long long max_sum = -4e18; 

    // i нь дэд массивын ТӨГСГӨЛИЙН цэг
    // Дэд массив дор хаяж 'a' урттай байх ёстой тул i нь a-аас эхэлнэ
    for (int i = a; i <= n; i++) {
        // 1. Шинээр хүчинтэй болсон эхлэх цэгийг нэмэх
        // Энэ нь одоогийн i-ээс яг 'a' зайд байгаа цэг юм
        s.insert(p[i - a]);

        // 2. Хүчинтэй хугацаа нь дууссан эхлэх цэгийг хасах
        // Энэ нь одоогийн i-ээс 'b + 1' зайд байгаа цэг юм (урт нь b-ээс их болсон)
        if (i > b) {
            // multiset.erase(val) нь бүх val утгыг устгадаг тул
            // iterator ашиглан зөвхөн нэгийг нь устгана.
            s.erase(s.find(p[i - b - 1]));
        }

        // 3. Одоогийн цонхон дахь хамгийн бага P[k]-г авч хариуг шинэчлэх
        // s.begin() нь multiset-ийн хамгийн бага утгыг заана
        long long current_max = p[i] - *s.begin();
        max_sum = max(max_sum, current_max);
    }

    cout << max_sum << "\n";

    return 0;
}