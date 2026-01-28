#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring> // memset

using namespace std;

const long long INF = 1e18;
const int MAXN = 505;

// capacity[u][v] нь u-ээс v рүү гүйх боломжтой үлдэгдэл урсгал
// long long ашиглана учир нь нийт урсгал int-ээс их гарч магадгүй
long long capacity[MAXN][MAXN];
int parent[MAXN]; // BFS зам мөшгөхөд хэрэгтэй
vector<int> adj[MAXN]; // Зөвхөн хөршүүдийг хадгалах (BFS хурдасгах)

// BFS ашиглан 1-ээс N хүртэл зам хайх
bool bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(s);
    parent[s] = -2; // Эхлэх цэгийг тэмдэглэх

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // Хэрэв v рүү очих урсгал үлдсэн бөгөөд хараахан очоогүй бол
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                // Төгсгөлд хүрвэл true буцаана
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Граф үүсгэх
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        
        // Хэрэв u, v хоёрын хооронд ирмэг байхгүй байсан бол adj-д нэмнэ
        // (Олон ирмэг байвал дахин нэмэхгүйн тулд шалгах, эсвэл зүгээр л давхардуулж болно,
        // гэхдээ Matrix ашиглаж байгаа тул adj vector зөвхөн BFS хурдасгахад л хэрэгтэй)
        // Энд энгийнээр шууд нэмж байна (давхардал BFS-д бага зэрэг нөлөөлөх ч хариунд нөлөөлөхгүй)
        adj[u].push_back(v);
        adj[v].push_back(u); // Урвуу урсгал (Residual edge) үүсгэхэд хэрэгтэй тул хоёр талд нь нэмнэ
        
        capacity[u][v] += c; // Parallel edges байвал хурдыг нэмнэ
    }

    long long max_flow = 0;

    // Зам олдсоор байвал урсгалыг нэмсээр байна
    while (bfs(1, n)) {
        long long flow = INF;
        
        // Олдсон замын дагуу хамгийн бага capacity (bottleneck)-ийг олно
        int curr = n;
        while (curr != 1) {
            int prev = parent[curr];
            flow = min(flow, capacity[prev][curr]);
            curr = prev;
        }

        // Урсгалыг нэмж, үлдэгдэл графыг шинэчилнэ
        curr = n;
        while (curr != 1) {
            int prev = parent[curr];
            capacity[prev][curr] -= flow; // Урагшаа урсгалыг багасгана
            capacity[curr][prev] += flow; // Буцах урсгалыг ихэсгэнэ
            curr = prev;
        }

        max_flow += flow;
    }

    cout << max_flow << endl;

    return 0;
}