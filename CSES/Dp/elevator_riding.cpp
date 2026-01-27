#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    if (!(cin >> n >> x)) return 0;

    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    // dp[mask] нь {лифтний тоо, сүүлийн лифтний ачаалал} гэсэн хос утга хадгална
    // Хэмжээ нь 2^n (бүх боломжит дэд олонлог)
    vector<pair<int, int>> best(1 << n);

    // Суурь нөхцөл: 0 хүн байхад 1 лифт (хоосон), 0 жинтэй гэж эхлүүлэх нь хялбар.
    // (Бодлогын хариунд хоосон лифтийг тооцохгүй байх тал дээр анхаарна)
    best[0] = {1, 0};

    // Бүх mask-аар гүйнэ (1-ээс 2^n - 1 хүртэл)
    for (int mask = 1; mask < (1 << n); mask++) {
        // Анхны утгыг муугаар (хамгийн ихээр) өгнө
        best[mask] = {n + 1, 0};

        // Тухайн mask-д байгаа хүн бүрийг шалгана
        for (int p = 0; p < n; p++) {
            // Хэрэв p-р хүн mask дотор байгаа бол (бит нь 1 бол)
            if ((mask >> p) & 1) {
                // p-р хүн нэмэгдэхээс өмнөх төлөвийг авна (XOR ашиглаж p-г хасна)
                auto prev = best[mask ^ (1 << p)];
                
                int rides = prev.first;
                int weight = prev.second;

                // p-р хүнийг одоогийн лифтэнд багтаах гээд үздэг
                if (weight + w[p] <= x) {
                    // Багтаж байна -> жин нэмэгдэнэ
                    weight += w[p];
                } else {
                    // Багтахгүй байна -> шинэ лифт эхлүүлнэ
                    rides++;
                    weight = w[p]; // Шинэ лифтний жин нь энэ хүний жин
                }

                // pair-ийн min функц нь эхлээд rides-ийг, дараа нь weight-ийг харьцуулдаг
                // Тиймээс бид хамгийн оновчтойг автоматаар хадгална
                best[mask] = min(best[mask], {rides, weight});
            }
        }
    }

    // Бүх хүн багтсан (бүх бит нь 1) үеийн лифтний тоог хэвлэнэ
    cout << best[(1 << n) - 1].first << "\n";

    return 0;
}