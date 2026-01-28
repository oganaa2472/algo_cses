#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
int t[MAXN];
int ans[MAXN]; // Хариу хадгалах (0 бол бодогдоогүй)
bool visited[MAXN]; // Ерөнхий visited (Cycle detection-д хэрэгтэй)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;

        // Одоогийн замын дарааллыг хадгалах
        vector<int> path;
        int curr = i;

        // Visited биш цэг рүү явсаар байх
        while (!visited[curr]) {
            visited[curr] = true;
            path.push_back(curr);
            curr = t[curr];
        }

        // Одоо curr нь мөргөсөн цэг болно.
        
        // 1. Хэрэв мөргөсөн цэг аль хэдийн хариутай бол (Хуучин component руу нийлэх)
        if (ans[curr] != 0) {
            int current_len = ans[curr];
            // Замаа хойш нь мөшгиж хариуг бөглөх
            for (int j = path.size() - 1; j >= 0; j--) {
                current_len++;
                ans[path[j]] = current_len;
            }
        } 
        // 2. Хэрэв мөргөсөн цэг хариугүй бол (Шинэ цикл олдлоо)
        // Энэ тохиолдолд curr заавал path дотор байх ёстой
        else {
            int cycle_len = 0;
            int split_index = -1;

            // Path дотроос цикл эхэлсэн цэгийг (curr) олох
            // Бид саяхан энэ замаар явсан тул path-ийг хойш нь хайхад хурдан байна
            for (int j = path.size() - 1; j >= 0; j--) {
                if (path[j] == curr) {
                    split_index = j;
                    break;
                }
            }

            // Циклийн уртыг тооцох
            cycle_len = path.size() - split_index;

            // Цикл доторх цэгүүдэд хариу оноох
            for (int j = split_index; j < path.size(); j++) {
                ans[path[j]] = cycle_len;
            }

            // Циклийн гаднах (Мод) цэгүүдэд хариу оноох
            int current_val = cycle_len;
            for (int j = split_index - 1; j >= 0; j--) {
                current_val++;
                ans[path[j]] = current_val;
            }
        }
    }

    // Хариу хэвлэх
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}