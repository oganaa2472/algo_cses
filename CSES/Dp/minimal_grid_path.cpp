#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Grid-ийг унших
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // Хариуг хадгалах string
    string ans = "";
    ans += grid[0][0]; // Эхлэх үсэг үргэлж орно

    // Одоо байгаа боломжит нүднүүд (candidates)
    // {row, col}
    vector<pair<int, int>> current_cells;
    current_cells.push_back({0, 0});

    // Нийт 2n - 2 алхам хийнэ (эхлэх цэгийг тооцсон тул)
    for (int step = 0; step < 2 * n - 2; step++) {
        vector<pair<int, int>> next_cells;
        char min_char = 'z' + 1; // Хамгийн ихээр эхлүүлнэ

        // 1. Одоогийн нүднүүдээс дараагийн боломжит хамгийн бага үсгийг олох
        for (auto p : current_cells) {
            int r = p.first;
            int c = p.second;

            // Доошоо явах
            if (r + 1 < n) {
                min_char = min(min_char, grid[r + 1][c]);
            }
            // Баруун тийш явах
            if (c + 1 < n) {
                min_char = min(min_char, grid[r][c + 1]);
            }
        }

        // Хамгийн бага үсгийг хариунд нэмэх
        ans += min_char;

        // 2. Зөвхөн min_char үсэгтэй нүднүүдийг дараагийн жагсаалтад оруулах
        for (auto p : current_cells) {
            int r = p.first;
            int c = p.second;

            // Доошоо
            if (r + 1 < n && grid[r + 1][c] == min_char) {
                next_cells.push_back({r + 1, c});
            }
            // Баруун тийш
            if (c + 1 < n && grid[r][c + 1] == min_char) {
                next_cells.push_back({r, c + 1});
            }
        }

        // 3. Давхардлыг арилгах (Sort + Unique)
        // Нэг нүд рүү олон газраас ирж болно
        sort(next_cells.begin(), next_cells.end());
        next_cells.erase(unique(next_cells.begin(), next_cells.end()), next_cells.end());

        // Дараагийн алхам руу шилжих
        current_cells = next_cells;
    }

    cout << ans << "\n";

    return 0;
}