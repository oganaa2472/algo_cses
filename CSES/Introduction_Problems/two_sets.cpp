#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long n;
    cin >> n;

    // Нийт нийлбэрийг олох
    long long sum = n * (n + 1) / 2;

    // Нийлбэр сондгой бол тэнцүү хуваах боломжгүй
    if (sum % 2 != 0) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    vector<long long> set1, set2;
    long long target = sum / 2;

    // Том тооноос нь эхлэн "Greedy" аргаар багцлах
    for (int i = n; i >= 1; i--) {
        if (target >= i) {
            set1.push_back(i);
            target -= i;
        } else {
            set2.push_back(i);
        }
    }

    // Set 1-ийг хэвлэх
    cout << set1.size() << endl;
    for (size_t i = 0; i < set1.size(); i++) {
        cout << set1[i] << (i == set1.size() - 1 ? "" : " ");
    }
    cout << endl;

    // Set 2-ийг хэвлэх
    cout << set2.size() << endl;
    for (size_t i = 0; i < set2.size(); i++) {
        cout << set2[i] << (i == set2.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}