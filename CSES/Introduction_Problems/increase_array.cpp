#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long moves = 0; // Нийт нүүдлийн тоо (их тоо гарах тул long long)
    long long prev_val;  // Өмнөх тоог хадгалах
    
    cin >> prev_val; // Эхний тоог унших

    for (int i = 1; i < n; i++) {
        long long current_val;
        cin >> current_val;

        if (current_val < prev_val) {
            // Хэрэв одоогийн тоо өмнөхөөсөө бага бол
            moves += (prev_val - current_val); // Зөрүүг нүүдэл болгож нэмнэ
        } else {
            // Хэрэв одоогийн тоо их буюу тэнцүү бол өмнөх тоог шинэчилнэ
            prev_val = current_val;
        }
        // prev_val-ийг өөрчлөхгүй хэвээр үлдээж байгаа нь
        // current_val-ийг prev_val-тай тэнцүү болгосонтой адил юм.
    }

    cout << moves << endl;

    return 0;
}