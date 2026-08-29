#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

// Өгөгдлийн бүтцүүд
map<int, int> freq;
set<pair<int, int>> st; // {-count, val}

// Элемент нэмэх хэсэг
void add(int x) {
    if (freq[x] > 0) {
        st.erase({-freq[x], x});
    }
    freq[x]++;
    st.insert({-freq[x], x});
}

// Элемент хасах хэсэг
void remove(int x) {
    st.erase({-freq[x], x});
    freq[x]--;
    if (freq[x] > 0) {
        st.insert({-freq[x], x});
    } else {
        freq.erase(x);
    }
}

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

    // 1. Эхний K урттай цонхны элементүүдийг оруулах
    for (int i = 0; i < k; i++) {
        add(arr[i]);
    }

    // Эхний цонхны Mode-ийг хэвлэх
    cout << st.begin()->second;

    // 2. Цонхыг баруун тийш шилжүүлэх
    for (int i = k; i < n; i++) {
        remove(arr[i - k]); // Зүүн талаас хасна
        add(arr[i]);        // Баруун талаас нэмнэ

        // Шинэ цонхны Mode-ийг зайгаар заглан хэвлэнэ
        cout << " " << st.begin()->second;
    }

    cout << "\n";

    return 0;
}