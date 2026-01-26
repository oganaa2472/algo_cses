#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Үйлчлүүлэгчийн мэдээлэл
struct Customer {
    int arrival;
    int departure;
    int index; // Анхны оролтын дарааллын дугаар

    // Ирэх цагаар нь эрэмбэлэх operator
    bool operator<(const Customer& other) const {
        return arrival < other.arrival;
    }
};

int main() {
    // Хурдан I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Customer> customers(n);
    for (int i = 0; i < n; i++) {
        cin >> customers[i].arrival >> customers[i].departure;
        customers[i].index = i;
    }

    // 1. Ирэх цагаар нь эрэмбэлэх
    sort(customers.begin(), customers.end());

    // Min-Priority Queue: {departure_time, room_number}
    // Хамгийн эрт гарах хүн нь дарааллын эхэнд байна.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int room_count = 0; // Нийт нээгдсэн өрөөний тоо
    vector<int> ans(n); // Хариуг хадгалах (индексээр нь)

    for (int i = 0; i < n; i++) {
        // Хэрэв PQ хоосон биш БА хамгийн эрт сулрах өрөө нь 
        // энэ хүнийг ирэхээс өмнө сулрах бол:
        if (!pq.empty() && pq.top().first < customers[i].arrival) {
            // Тэр өрөөг дахин ашиглана
            pair<int, int> free_room = pq.top();
            pq.pop();

            int room_id = free_room.second;
            ans[customers[i].index] = room_id;
            
            // Шинэ гарах хугацаагаар нь буцааж хийнэ
            pq.push({customers[i].departure, room_id});
        } else {
            // Сул өрөө байхгүй тул шинэ өрөө нээнэ
            room_count++;
            ans[customers[i].index] = room_count;
            pq.push({customers[i].departure, room_count});
        }
    }

    // 1. Хамгийн ихдээ хэдэн өрөө хэрэг болсон
    cout << room_count << "\n";
    
    // 2. Хүн бүрт оноосон өрөөний дугаар (анхны дарааллаар)
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}