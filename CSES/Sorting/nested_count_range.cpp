#include <iostream>
#include <vector>
#include <algorithm>

// PBDS сангууд
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// ordered_set-д pair хадгална: {y_coordinate, unique_index}
// Энэ нь давхардсан y утгуудыг алдаагүй хадгалах боломжийг олгоно.
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct Range {
    int l, r, id;
    
    // Эрэмбэлэх дүрэм
    bool operator<(const Range& other) const {
        if (l == other.l) {
            return r > other.r; // x тэнцүү бол y буурахаар
        }
        return l < other.l; // x өсөхөөр
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<Range> ranges(n);
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].l >> ranges[i].r;
        ranges[i].id = i;
    }

    // 1. Эрэмбэлэх
    sort(ranges.begin(), ranges.end());

    vector<int> count_contains(n, 0);
    vector<int> count_contained_by(n, 0);
    ordered_set os;

    // 2. Contains (Бусдыг агуулж буйг тоолох) - Хойноос урагш
    for (int i = n - 1; i >= 0; i--) {
        // Одоогийн ranges[i].r-ээс бага буюу тэнцүү y-тэй хэдэн интервал орсон бэ?
        // {ranges[i].r, 2e9} гэж хайх нь r-тэй тэнцүү бүх элементийг оруулаад тоолно.
        int count = os.order_of_key({ranges[i].r, 2000000000});
        count_contains[ranges[i].id] = count;
        
        // PBDS-д нэмэх ({y, index} хослол)
        os.insert({ranges[i].r, i});
    }

    // PBDS-ээ цэвэрлэнэ (дараагийн үйлдэлд бэлдэх)
    os.clear();

    // 3. Contained By (Бусдад агуулагдаж буйг тоолох) - Урдаас хойш
    for (int i = 0; i < n; i++) {
        // Одоогийн ranges[i].r-ээс их буюу тэнцүү y-тэй хэдэн интервал өмнө нь байсан бэ?
        // Нийт тооноос (os.size()) эрс багуудыг хасна.
        int strictly_smaller = os.order_of_key({ranges[i].r, -1});
        count_contained_by[ranges[i].id] = os.size() - strictly_smaller;
        
        os.insert({ranges[i].r, i});
    }

    // 4. Хариу хэвлэх
    for (int i = 0; i < n; i++) cout << count_contains[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << count_contained_by[i] << " ";
    cout << "\n";

    return 0;
}