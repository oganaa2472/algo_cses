#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main() {
    // Input/Output хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    // Adjacency List: {neighbor, weight}
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // Орой бүр дээр K ширхэг хамгийн бага замыг хадгалах Max-Heap
    // dist[u] нь u хот руу ирэх хамгийн бага K замыг агуулна.
    // Хамгийн ихийг нь орой дээрээ барих тул priority_queue<long long> (default Max-Heap)
    vector<priority_queue<long long>> dist(n + 1);

    // Глобал хайлтад зориулсан Min-Heap (Dijkstra)
    // {cost, u}
    priority_queue<pair<long long, int>, 
                   vector<pair<long long, int>>, 
                   greater<pair<long long, int>>> pq;

    // Эхлэл
    dist[1].push(0);
    pq.push({0, 1});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Хэрэв u орой дээрх зам маань K ширхэгт хүрээгүй эсвэл
        // одоогийн зам (d) нь u дээр бүртгэгдсэн хамгийн муу замаас (dist[u].top()) их байвал
        // энэ замаар цааш хайх шаардлагагүй (Pruning).
        // Гэхдээ энд бидний логик доорх if нөхцлөөр хянагдах тул 
        // d > dist[u].top() шалгалтыг хийхдээ болгоомжтой байх хэрэгтэй. 
        // Хамгийн найдвартай нь шууд relaxation хийх.
        if (dist[u].size() == k && d > dist[u].top()) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            long long new_cost = d + w;

            // Хэрэв K зам бүрдээгүй бол нэмнэ
            if (dist[v].size() < k) {
                dist[v].push(new_cost);
                pq.push({new_cost, v});
            }
            // Хэрэв K зам бүрдсэн ч, шинэ зам маань одоогийн хамгийн муугаас сайн бол сайжруулна
            else if (new_cost < dist[v].top()) {
                dist[v].pop(); // Мууг нь хаяна
                dist[v].push(new_cost); // Сайнаа хийнэ
                pq.push({new_cost, v});
            }
        }
    }

    // dist[n] дотор хамгийн бага K зам байгаа боловч Max-Heap дотор байгаа тул
    // тэдгээр нь Их -> Бага дараалалтай гарч ирнэ.
    // Бид Бага -> Их болгож хэвлэх ёстой.
    vector<long long> result;
    while (!dist[n].empty()) {
        result.push_back(dist[n].top());
        dist[n].pop();
    }
    
    // Эрэмбэлэх (Багаас их рүү)
    sort(result.begin(), result.end());

    for (long long cost : result) {
        cout << cost << " ";
    }
    cout << endl;

    return 0;
}