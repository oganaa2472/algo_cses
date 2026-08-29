#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n, k;
multiset<int> left_set;  // Жижиг талын элементүүд (хамгийн том нь медиан)
multiset<int> right_set; // Том талын элементүүд

// Дүрэм дагуу олонлогуудын хэмжээг тохируулах
void balance() {
    int target_left = (k + 1) / 2;

    while (left_set.size() > target_left) {
        auto it = prev(left_set.end());
        right_set.insert(*it);
        left_set.erase(it);
    }

    while (left_set.size() < target_left && !right_set.empty()) {
        auto it = right_set.begin();
        left_set.insert(*it);
        right_set.erase(it);
    }
}

// Элемент нэмэх
void add(int x) {
    if (left_set.empty() || x <= *left_set.rbegin()) {
        left_set.insert(x);
    } else {
        right_set.insert(x);
    }
    balance();
}

// Элемент хасах
void remove(int x) {
    auto it = left_set.find(x);
    if (it != left_set.end()) {
        left_set.erase(it);
    } else {
        it = right_set.find(x);
        if (it != right_set.end()) {
            right_set.erase(it);
        }
    }
    balance();
}

int main() {
    // Хурдан I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> k)) return 0;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // 1. Эхний K урттай цонхыг байгуулах
    for (int i = 0; i < k; i++) {
        add(arr[i]);
    }

    // Эхний цонхны медиан (left_set-ийн хамгийн том элемент)
    cout << *left_set.rbegin();

    // 2. Цонхыг шилжүүлэн бодох
    for (int i = k; i < n; i++) {
        remove(arr[i - k]); // Зүүн талаас хасна
        add(arr[i]);        // Баруун талаас нэмнэ

        // Медианыг хэвлэх
        cout << " " << *left_set.rbegin();
    }

    cout << "\n";

    return 0;
}