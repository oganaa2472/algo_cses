#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[200005];
bool matched[200005]; // Хүн бүрийг хос болсон эсэхийг бүртгэнэ
int ans = 0; // Нийт хосын тоо

// u: одоогийн хүн, p: түүний дарга
void dfs(int u, int p) {
    // 1. Эхлээд бүх доод ажилтнууд руугаа орно (Post-order traversal)
    for (int v : adj[u]) {
        if (v == p) continue; // Буцаж дарга руугаа явахгүй
        dfs(v, u);
    }

    // 2. Доод хүмүүсээ шалгаж дууссаны дараа өөрийгөө шийднэ.
    // Хэрэв u дарга руугаа (p) очихдоо:
    // u өөрөө хосгүй байна, БАС p нь хосгүй байна гэвэл -> Хос болно!
    
    if (p != 0) { // p != 0 гэдэг нь u нь Ерөнхий захирал биш (даргатай) гэсэн үг
        if (!matched[u] && !matched[p]) {
            matched[u] = true;
            matched[p] = true;
            ans++; // Хосын тоог нэгээр нэмнэ
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 1-р хүнээс эхэлж, дарга нь 0 (байхгүй) гэж дуудна
    dfs(1, 0);

    cout << ans << endl;
    return 0;
}