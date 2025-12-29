#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;

    // Тэмдэгт бүрийн давтамжийг тоолох (A-Z: 26 тэмдэгт)
    vector<int> count(26, 0);
    for (char c : s) {
        count[c - 'A']++;
    }

    int odd_count = 0;
    int odd_index = -1;
    for (int i = 0; i < 26; i++) {
        if (count[i] % 2 != 0) {
            odd_count++;
            odd_index = i;
        }
    }

    // Хэрэв сондгой тэмдэгт 1-ээс олон бол боломжгүй
    if (odd_count > 1) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    string first_half = "", middle = "", second_half = "";

    for (int i = 0; i < 26; i++) {
        string temp(count[i] / 2, (char)(i + 'A'));
        if (i == odd_index) {
            // Сондгой тэмдэгтийн нэгийг нь голд үлдээж, бусдыг нь хоёр талд хуваана
            middle = (char)(i + 'A');
        }
        first_half += temp;
    }

    second_half = first_half;
    reverse(second_half.begin(), second_half.end());

    // Хэрэв сондгой тэмдэгт байсан бол дунд нь бүгдийг нь байрлуулна
    if (odd_index != -1) {
        string mid_str(count[odd_index], (char)(odd_index + 'A'));
        // Сондгой тэмдэгтийг хувааж байрлуулсан логикийг засаж, 
        // бүх сондгой тэмдэгтийг дунд нь тавих нь илүү хялбар.
        first_half = "";
        for (int i = 0; i < 26; i++) {
            if (i != odd_index) {
                string temp(count[i] / 2, (char)(i + 'A'));
                first_half += temp;
            }
        }
        second_half = first_half;
        reverse(second_half.begin(), second_half.end());
        cout << first_half << mid_str << second_half << endl;
    } else {
        cout << first_half << second_half << endl;
    }

    return 0;
}