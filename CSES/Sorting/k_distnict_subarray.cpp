#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    // map: {тоо : тоолуур}
    map<int, int> counts;
    int left = 0;
    long long ans = 0;

    for (int right = 0; right < n; right++) {
        // Баруун талын тоог цонхонд нэмэх
        counts[x[right]]++;

        // Хэрэв ялгаатай тооны тоо k-аас их болвол зүүн талаас агшаах
        while (counts.size() > k) {
            counts[x[left]]--;
            // Хэрэв тухайн тооны тоолуур 0 болвол map-аас устгана
            if (counts[x[left]] == 0) {
                counts.erase(x[left]);
            }
            left++;
        }

        // Одоогийн [left, right] цонхон доторх хүчинтэй дэд массивуудын тоо
        ans += (right - left + 1);
    }

    cout << ans << "\n";

    return 0;
}