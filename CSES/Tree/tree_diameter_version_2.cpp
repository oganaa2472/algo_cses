#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
int diameter = 0; // Хамгийн урт замыг хадгалах хувьсагч

// Энэ функц нь 'u' оройноос доошоо навч руу явах хамгийн урт замыг буцаана.
int solveDP(int u, int parent) {
    int max1 = 0; // Хамгийн урт зам
    int max2 = 0; // Хоёр дахь хамгийн урт зам

    for (int v : adj[u]) {
        if (v == parent) continue; // Эцэг орой руугаа буцаж орохгүй

        // Хүүхэд орой 'v'-ээс доош явах хамгийн урт замыг олно (+1 нь u-гээс v рүү очих ирмэг)
        int child_path = solveDP(v, u) + 1;

        // Хамгийн урт 2 замыг шинэчлэх хэсэг
        if (child_path > max1) {
            max2 = max1;
            max1 = child_path;
        } else if (child_path > max2) {
            max2 = child_path;
        }
    }

    // Одоогийн u оройг оройн цэгээ болгосон замын урт: max1 + max2
    // Энэ нь өмнөх олсон диаметрээс их байвал шинэчилнэ.
    diameter = max(diameter, max1 + max2);

    // Дээд талын эцэг орой руу нь зөвхөн хамгийн урт ганц замыг нь буцаана
    return max1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    adj.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 1-р оройг үндэс болгон DP-г ажиллуулна
    solveDP(1, 0);

    // Ганцхан удаагийн хайлтаар диаметр бодогдсон байна
    cout << diameter << "\n";

    return 0;
}