#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

#define ll long long
using namespace std;

// Салсан Олонлог (Disjoint Set Union - DSU) өгөгдлийн бүтэц
class DisjointSet {
public:
    // rank - рангаар нэгтгэхэд ашиглана (модны өндөртэй төстэй)
    // parent - зангилааны эцэг зангилааг хадгална
    // size - хэмжээгээр нэгтгэхэд ашиглана (модны хэмжээтэй төстэй)
    vector<ll> rank, parent, size;

    // Конструктор: n зангилаатай DSU үүсгэнэ.
    // Эхлээд зангилаа бүр өөрийн олонлогийн эцэг бөгөөд хэмжээ нь 1 байна.
    DisjointSet(ll n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (ll i = 0; i <= n; i++) {
            parent[i] = i; // Эхлээд i зангилааны эцэг нь өөрөө байна.
            size[i] = 1;   // Эхлээд олонлогийн хэмжээ 1 байна.
        }
    }

    // findUPar (Find Ultimate Parent): Зангилааны харьяалагдах олонлогийн үндсэн эцэг зангилааг олох.
    // Замын шахалтыг (path compression) ашиглан гүйцэтгэлийг сайжруулдаг.
    ll findUPar(ll node) {
        if (node == parent[node]) // Хэрэв зангилааны эцэг нь өөрөө байвал, энэ нь үндсэн эцэг мөн.
            return node;
        // Замын шахалт: Зангилаа болон түүний эцэг хоорондын зангилаануудыг үндсэн эцэг рүү шууд холбоно.
        return parent[node] = findUPar(parent[node]);
    }

    // unionByRank: Хоёр зангилаа харьяалагдах хоёр олонлогийг рангаар нь харьцуулж нэгтгэх.
    // Рангаар нэгтгэх нь модны өндөр хэт өсөхөөс сэргийлж, find үйлдлийн дундаж хугацааг сайжруулдаг.
    void unionByRank(ll u, ll v) {
        ll ulp_u = findUPar(u); // u зангилааны үндсэн эцэг.
        ll ulp_v = findUPar(v); // v зангилааны үндсэн эцэг.
        if (ulp_u == ulp_v) return; // Хэрэв аль хэдийн нэг олонлогт байвал юу ч хийхгүй.

        if (rank[ulp_u] < rank[ulp_v]) { // ulp_u-ийн ранг бага бол ulp_u-г ulp_v-д холбоно.
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) { // ulp_v-ийн ранг бага бол ulp_v-г ulp_u-д холбоно.
            parent[ulp_v] = ulp_u;
        } else { // Ранг нь тэнцүү бол аль нэгийг (жишээ нь ulp_v-г ulp_u-д) холбож, ulp_u-ийн рангыг нэгээр нэмнэ.
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    // unionBySize: Хоёр зангилаа харьяалагдах хоёр олонлогийг хэмжээгээр нь харьцуулж нэгтгэх.
    // Хэмжээгээр нэгтгэх нь модны гүн хэт өсөхөөс сэргийлж, find үйлдлийн дундаж хугацааг сайжруулдаг.
    void unionBySize(ll u, ll v) {
        ll ulp_u = findUPar(u); // u зангилааны үндсэн эцэг.
        ll ulp_v = findUPar(v); // v зангилааны үндсэн эцэг.
        if (ulp_u == ulp_v) return; // Хэрэв аль хэдийн нэг олонлогт байвал юу ч хийхгүй.

        if (size[ulp_u] < size[ulp_v]) { // ulp_u-ийн хэмжээ бага бол ulp_u-г ulp_v-д холбож, ulp_v-ийн хэмжээг нэмнэ.
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else { // ulp_v-ийн хэмжээ бага буюу тэнцүү бол ulp_v-г ulp_u-д холбож, ulp_u-ийн хэмжээг нэмнэ.
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    ll n, m; // n: зангилааны тоо, m: ирмэгийн тоо
    cin >> n >> m;

    // DSU өгөгдлийн бүтцийг n зангилаатай үүсгэнэ.
    DisjointSet ds(n);

    // max_component_size: Одоогоор график дахь хамгийн том холбоост хэсгийн хэмжээ.
    // Эхлээд зангилаа бүр тусдаа холбоост хэсэг тул хамгийн их хэмжээ 1 байна.
    int max_component_size = 1;
    int count = 0;
    // Ирмэг бүрийг авч үзэх давталт.
    for (int i = 0; i < m; i++) {
        ll a, b; // Ирмэгийн эхлэл, төгсгөл зангилаа
        cin >> a >> b;

        // a болон b зангилаануудын харьяалагдах олонлогийн үндсэн эцгийг олох.
        ll root_a = ds.findUPar(a);
        ll root_b = ds.findUPar(b);

        // Хэрэв a болон b өөр өөр олонлогт харьяалагддаг бол (өөр өөр холбоост хэсэгт байвал).
        if (root_a != root_b) {
            // Хоёр олонлогийг unionBySize аргаар нэгтгэнэ.
            // unionBySize нь хэмжээгээр харьцуулж нэгтгээд, шинэ олонлогийн үндсэн эцгийн хэмжээг шинэчилдэг.
            ds.unionBySize(a, b);

            // Нэгтгэсэн олонлогийн үндсэн эцгийг дахин олох.
            ll new_root = ds.findUPar(a); // a зангилаа харьяалагдах олонлогийн шинэ үндсэн эцгийг олох.
            count++;
            // Нэгтгэсний дараах хамгийн том холбоост хэсгийн хэмжээг шинэчлэх.
            // Шинэ холбоост хэсгийн хэмжээ нь ds.size[new_root]-д хадгалагдсан байна.
            max_component_size = max(max_component_size, (int)ds.size[new_root]);
        }

        // Ирмэг бүрийг боловсруулсны дараах хамгийн том холбоост хэсгийн хэмжээг хэвлэх.
        cout <<n-count<<" " << max_component_size << endl;
    }

    return 0;
}