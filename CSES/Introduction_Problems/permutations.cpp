#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Тусгай тохиолдол: n = 1
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    // Боломжгүй тохиолдол: n = 2 эсвэл 3
    if (n == 2 || n == 3) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    // Эхлээд бүх тэгш тоонуудыг хэвлэнэ
    for (int i = 2; i <= n; i += 2) {
        cout << i << " ";
    }

    // Дараа нь бүх сондгой тоонуудыг хэвлэнэ
    for (int i = 1; i <= n; i += 2) {
        cout << i << (i + 2 <= n ? " " : "");
    }

    cout << endl;

    return 0;
}