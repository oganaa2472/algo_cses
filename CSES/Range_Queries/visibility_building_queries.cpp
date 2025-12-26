#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 200005;
const int LOG = 19; // 2^19 нь 200,000-аас их
int up[MAXN][LOG];
int h[MAXN];

int main() {
    // Оролт гаралтыг хурдасгах
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> h[i];

    // Monotonic Stack: Дараагийн өндөр барилгыг олох
    stack<int> s;
    for (int i = n; i >= 1; i--) {
        while (!s.empty() && h[s.top()] <= h[i]) s.pop();
        if (s.empty()) up[i][0] = n + 1; // Өндөр барилга байхгүй бол
        else up[i][0] = s.top();
        s.push(i);
    }
    up[n + 1][0] = n + 1;

    // Binary Lifting хүснэгт бөглөх
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n + 1; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    // Асуулга бүрт хариулах
    while (q--) {
        int a, b;
        cin >> a >> b;
        
        int curr = a;
        int count = 1; // Эхний барилга үргэлж харагдана
        
        for (int j = LOG - 1; j >= 0; j--) {
            // Хэрэв үсрэх индекс b-ээс бага буюу тэнцүү бол үсэрнэ
            if (up[curr][j] <= b) {
                count += (1 << j);
                curr = up[curr][j];
            }
        }
        cout << count << "\n";
    }

    return 0;
}