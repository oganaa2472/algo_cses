#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];

// 3 төрлийн массив хэрэгтэй болно
int distA[MAXN]; // A цэгээс бүх орой хүртэлх зай
int distB[MAXN]; // B цэгээс бүх орой хүртэлх зай

// Хамгийн хол цэгийг олоход туслах хувьсагчид
int maxDist = -1;
int farthestNode = -1;

// 1. Хамгийн хол цэг хайх DFS (Өмнөх бодлогын функц)
void findFarthest(int u, int p, int d) {
    if (d > maxDist) {
        maxDist = d;
        farthestNode = u;
    }
    for (int v : adj[u]) {
        if (v != p) findFarthest(v, u, d + 1);
    }
}

// 2. Зайг массивд хадгалах DFS
// u: одоогийн, p: эцэг, d: зай, dists: утга хадгалах массив
void calcDist(int u, int p, int d, int dists[]) {
    dists[u] = d; // Зайг массивд бичнэ
    for (int v : adj[u]) {
        if (v != p) {
            calcDist(v, u, d + 1, dists);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // АЛХАМ 1: Диаметрийн нэг үзүүр A-г олох
    maxDist = -1;
    findFarthest(1, 0, 0);
    int nodeA = farthestNode;

    // АЛХАМ 2: Диаметрийн нөгөө үзүүр B-г олох
    maxDist = -1;
    findFarthest(nodeA, 0, 0);
    int nodeB = farthestNode;

    // АЛХАМ 3: A цэгээс бүх зайг тооцож distA-д хадгалах
    calcDist(nodeA, 0, 0, distA);

    // АЛХАМ 4: B цэгээс бүх зайг тооцож distB-д хадгалах
    calcDist(nodeB, 0, 0, distB);

    // АЛХАМ 5: Хариуг хэвлэх
    for (int i = 1; i <= n; i++) {
        cout << max(distA[i], distB[i]) << " ";
    }
    cout << endl;

    return 0;
}