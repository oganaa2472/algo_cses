#include <iostream>
#include <vector>
#include <algorithm> // lower_bound функцэд хэрэгтэй

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> tails;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        // lower_bound нь эрэмбэлэгдсэн дарааллаас x-тэй тэнцүү эсвэл түүнээс их
        // хамгийн эхний элементийн заагчийг (iterator) буцаана.
        auto it = lower_bound(tails.begin(), tails.end(), x);

        if (it == tails.end()) {
            // Хэрэв x нь tails-ийн бүх элементээс их байвал
            // бид хамгийн урт дарааллаа сунгаж чадна гэсэн үг.
            tails.push_back(x);
        } else {
            // Хэрэв тийм биш бол, олсон байрлал дахь тоог x-ээр солино.
            // Энэ нь дарааллын уртыг ихэсгэхгүй ч, төгсгөлийн элементийг багасгаж
            // ирээдүйд дараалал үргэлжлэх магадлалыг нэмэгдүүлнэ.
            *it = x;
        }
    }

    // tails массивын хэмжээ нь LIS-ийн урттай тэнцүү байна
    cout << tails.size() << "\n";

    return 0;
}