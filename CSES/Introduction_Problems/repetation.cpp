#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s; // Текстийг унших

    int max_len = 1;      // Хамгийн их уртыг хадгалах (хамгийн багадаа 1 байна)
    int current_len = 1;  // Одоогийн тоологдож буй урт

    // Текстийн 2 дахь тэмдэгтээс эхлэн төгсгөл хүртэл шалгана
    for (size_t i = 1; i < s.length(); i++) {
        if (s[i] == s[i - 1]) {
            // Хэрэв өмнөх тэмдэгттэй ижил байвал тоог нэмнэ
            current_len++;
        } else {
            // Хэрэв өөр тэмдэгт гарч ирвэл тоог 1-ээс дахин эхлүүлнэ
            current_len = 1;
        }

        // max_len-ийг шинэчлэх (current_len илүү том болсон бол)
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    cout << max_len << endl; // Хариуг хэвлэх

    return 0;
}