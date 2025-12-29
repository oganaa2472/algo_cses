#include <iostream>

using namespace std;

int main() {
    // Оролт гаралтыг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            // Мөрийн индекс ба баганын индексийн XOR-ыг хэвлэх
            cout << (r ^ c) << (c == n - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}