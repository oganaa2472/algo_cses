#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];

// maxDist: одоогийн олсон хамгийн хол зай
// farthestNode: тэр хамгийн хол байгаа цэг
int maxDist = -1;
int farthestNode = -1;

// u: одоогийн цэг, p: эцэг цэг, d: эхлэлээс ирсэн зай
void dfs(int u, int p, int d) {
    // Хэрэв одоогийн зай (d) нь бидний бүртгэсэн max-аас их байвал шинэчилнэ
    if (d > maxDist) {
        maxDist = d;
        farthestNode = u;
    }
    
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1); // Цаашаа 1 алхам явах тул зайг (d+1) болгоно
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // Ирмэгүүдийг унших
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // АЛХАМ 1: 1-р цэгээс хамгийн хол цэгийг олох (A цэг)
    maxDist = -1;
    dfs(1, 0, 0); 
    int nodeA = farthestNode;

    // АЛХАМ 2: Олсон A цэгээсээ хамгийн хол цэгийг олох (B цэг)
    maxDist = -1;
    dfs(nodeA, 0, 0);
    // Одоо maxDist дотор A-аас B хүртэлх зай буюу Диаметр хадгалагдаж байна

    cout << maxDist << endl;

    return 0;
}