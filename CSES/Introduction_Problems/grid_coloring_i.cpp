#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Оролт гаралтыг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    char chars[] = {'A', 'B', 'C', 'D'};

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            char original = grid[r][c];
            char up = (r > 0) ? grid[r-1][c] : ' ';
            char left = (c > 0) ? grid[r][c-1] : ' ';

            // 4 тэмдэгтийг нэг нэгээр нь шалгаж тохирохыг нь сонгоно
            for (char option : chars) {
                if (option != original && option != up && option != left) {
                    grid[r][c] = option;
                    break;
                }
            }
        }
    }

    // Үр дүнг хэвлэх
    for (int i = 0; i < n; i++) {
        cout << grid[i] << "\n";
    }

    return 0;
}