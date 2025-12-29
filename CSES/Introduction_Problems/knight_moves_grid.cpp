#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Морь нүүж болох 8 чиглэл
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

int main() {
    int n;
    cin >> n;

    // Зайг хадгалах хүснэгт, -1-ээр дүүргэсэн нь очиж амжаагүйг илтгэнэ
    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int, int>> q;

    // Зүүн дээд булангаас эхэлнэ
    dist[0][0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();

        int x = curr.first;
        int y = curr.second;

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Хөлгөөс гадагшаа гараагүй ба өмнө нь очоогүй нүдийг шалгах
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // Үр дүнг хэвлэх
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dist[i][j] << (j == n - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}