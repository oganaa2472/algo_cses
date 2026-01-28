#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// Ирмэгүүдийг тэмдэглэх массив.
// N <= 15 үед хамгийн ихдээ 2^15 = 32768 орой, 2^16 = 65536 ирмэг байна.
bool seen[1 << 16]; 
vector<int> path;
int n;
int mask; // n-1 битийг ялгаж авах маск

void dfs(int u) {
    for (int i = 0; i < 2; i++) {
        // Одоогийн u зангилаа дээр i (0 эсвэл 1) битийг залгаж шинэ ирмэг үүсгэнэ.
        // Энэ ирмэг нь N урттай дэд мөрийг төлөөлнө.
        int edge_val = (u << 1) | i;
        
        if (!seen[edge_val]) {
            seen[edge_val] = true;
            // Дараагийн зангилаа нь сүүлийн n-1 бит болно
            dfs(edge_val & mask);
            // DFS буцахдаа ирмэгийн утгыг нэмнэ (Hierholzer's algorithm)
            path.push_back(i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    if (n == 1) {
        cout << "01" << endl;
        return 0;
    }

    // Mask for n-1 bits: (1 << (n-1)) - 1
    // Жишээ нь: n=3 бол mask = 011 (binary) = 3
    mask = (1 << (n - 1)) - 1;

    // DFS-ийг 0 (буюу 00...0) зангилаанаас эхлүүлнэ
    dfs(0);

    // Хариуг байгуулах
    string res = "";


    // 1. Эхлэлийн n-1 ширхэг '0'-ийг нэмнэ
    for (int i = 0; i < n - 1; i++) {
        res += '0';
    }

    // 2. Олсон замын битүүдийг нэмнэ
    // АНХААР: path вектор дотор зам урвуу байгаа тул хойноос нь урагш гүйнэ
    for (int i = path.size() - 1; i >= 0; i--) {
        res += to_string(path[i]);
    }

    cout << res << endl;

    return 0;
}