#include <iostream>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

// Өмнөх бодлогын логик: Гурван цэгийн байршлыг тодорхойлох
// 0: Collinear (Нэг шулуун дээр)
// 1: Clockwise (Баруун)
// 2: Counter-Clockwise (Зүүн)
int orientation(Point p, Point q, Point r) {
    long long val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// "q" цэг нь "pr" хэрчим дээр байгаа эсэхийг шалгах функц
// Зөвхөн p, q, r нь нэг шулуун дээр байх үед (collinear) ашиглана
bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

void solve() {
    Point p1, p2, p3, p4;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> p4.x >> p4.y;

    int o1 = orientation(p1, p2, p3);
    int o2 = orientation(p1, p2, p4);
    int o3 = orientation(p3, p4, p1);
    int o4 = orientation(p3, p4, p2);

    // General Case: Ерөнхий тохиолдол
    if (o1 != o2 && o3 != o4) {
        cout << "YES" << endl;
        return;
    }

    // Special Cases: Нэг шулуун дээрх тохиолдлууд
    // p3 нь p1p2 дээр байгаа эсэх
    if (o1 == 0 && onSegment(p1, p3, p2)) {
        cout << "YES" << endl;
        return;
    }
    // p4 нь p1p2 дээр байгаа эсэх
    if (o2 == 0 && onSegment(p1, p4, p2)) {
        cout << "YES" << endl;
        return;
    }
    // p1 нь p3p4 дээр байгаа эсэх
    if (o3 == 0 && onSegment(p3, p1, p4)) {
        cout << "YES" << endl;
        return;
    }
    // p2 нь p3p4 дээр байгаа эсэх
    if (o4 == 0 && onSegment(p3, p2, p4)) {
        cout << "YES" << endl;
        return;
    }

    cout << "NO" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}