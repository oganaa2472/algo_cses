#include <iostream>
#include <vector>

// PBDS (Policy Based Data Structure) сангуудыг дуудах
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// ordered_set гэсэн шинэ төрөл зарлаж байна
// Энэ нь set-тэй ижил боловч индексээр хандах боломжтой
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    // Хурдан оролт гаралт (IO Optimization)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    ordered_set children;

    // 1-ээс n хүртэлх хүүхдүүдийг жагсаалтад оруулна
    for (int i = 1; i <= n; i++) {
        children.insert(i);
    }

    int index = 0;

    while (!children.empty()) {
        // Одоогийн байгаа хүүхдийн тоонд хувааж үлдэгдэл авна
        // index = (index + k) % children.size()
        index = (index + k) % children.size();

        // find_by_order(index): index-р байрлалд байгаа элементийн заагчийг (iterator) буцаана
        auto it = children.find_by_order(index);

        // Олсон тоог хэвлэх
        cout << *it << " ";

        // Жагсаалтаас хасах
        children.erase(it);
        
        // Хасагдсаны дараа жагсаалт автоматаар шахагдах тул
        // index-ийг гараар өөрчлөх шаардлагагүй, 
        // дараагийн давталтад автоматаар зөв тооцогдоно.
    }

    return 0;
}