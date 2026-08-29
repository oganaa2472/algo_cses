#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    // Хурдан I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // k-аас их тоонууд MEX болж чадахгүй тул freq массивын хэмжээ k + 2 байна.
    vector<int> freq(k + 2, 0);
    set<int> missing;

    // Эхэндээ [0, k] хүртэлх бүх тоо цонхонд байхгүй гэж үзээд set-д оруулна
    for (int i = 0; i <= k; i++) {
        missing.insert(i);
    }

    // Элемент нэмэх функц
    auto add = [&](int x) {
        if (x <= k) {
            freq[x]++;
            if (freq[x] == 1) { // Анх удаа орж ирж байгаа бол
                missing.erase(x);
            }
        }
    };

    // Элемент хасах функц
    auto remove = [&](int x) {
        if (x <= k) {
            freq[x]--;
            if (freq[x] == 0) { // Цонхноос бүрэн гарсан бол
                missing.insert(x);
            }
        }
    };

    // 1. Эхний K урттай цонхыг үүсгэх
    for (int i = 0; i < k; i++) {
        add(arr[i]);
    }

    // Эхний цонхны MEX-ийг хэвлэх
    cout << *missing.begin();

    // 2. Цонхыг баруун тийш шилжүүлэх
    for (int i = k; i < n; i++) {
        remove(arr[i - k]); // Зүүн талаас хасна
        add(arr[i]);        // Баруун талаас нэмнэ

        // Шинэ MEX-ийг зайгаар заглан хэвлэнэ
        cout << " " << *missing.begin();
    }

    cout << "\n";

    return 0;
}