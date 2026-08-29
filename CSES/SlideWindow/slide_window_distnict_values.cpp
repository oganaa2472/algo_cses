#include <iostream>
#include <vector>
#include <map>

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

    map<int, int> freq;
    int distinct_count = 0;

    // 1. Эхний K урттай цонхны элементүүдийг тоолох
    for (int i = 0; i < k; i++) {
        if (freq[arr[i]] == 0) {
            distinct_count++;
        }
        freq[arr[i]]++;
    }

    // Эхний цонхны хариуг хэвлэх
    cout << distinct_count;

    // 2. Цонхыг баруун тийш шилжүүлэн бодох
    for (int i = k; i < n; i++) {
        // Зүүн талын элементийг хасах
        int left_elem = arr[i - k];
        freq[left_elem]--;
        if (freq[left_elem] == 0) {
            distinct_count--; // Баганад тоо үлдээгүй бол ялгаатай тоо нэгээр цөөрнө
        }

        // Баруун талын элементийг нэмэх
        int right_elem = arr[i];
        if (freq[right_elem] == 0) {
            distinct_count++; // Анх удаа орж ирж байгаа тоо бол +1
        }
        freq[right_elem]++;

        // Хариуг зайгаар заглан хэвлэх
        cout << " " << distinct_count;
    }

    cout << "\n";

    return 0;
}