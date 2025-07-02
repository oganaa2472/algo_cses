#include <vector>
#include <map>
#include <algorithm> // for sort, unique, lower_bound, upper_bound
#include <iostream>
#include <tuple>     // for std::tuple in queries_data

// Сегмент модны массивын дээд хэмжээ
// Ажилчдын тоо N + 2 * Query-н тоо Q. Жишээ нь N=2e5, Q=2e5 -> 2e5 + 4e5 = 6e5
// Сегмент модны хувьд 4 * M хэмжээтэй байх нь аюулгүй байдаг.
const int MAX_COMPRESSED_SIZE = 600005; // ~N + 2Q, 4*N_Q_MAX

// Сегмент модны массив (1-ээс эхэлдэг индекс ашиглана)
int tree[4 * MAX_COMPRESSED_SIZE];

// Ажилчдын одоогийн цалинг хадгалах массив (1-ээс N хүртэлх ID-тай)
int employee_salaries[200005]; // MAXN

// Координатын шахалтад ашиглах өвөрмөц цалингийн утгууд
std::vector<int> distinct_salaries;

// Цалингийн утгаас шахагдсан индекс рүү хөрвүүлэх map
std::map<int, int> salary_to_compressed_idx;

// Сегмент модны update функц: idx дээрх тооллыг val-аар өөрчлөх
void update(int node, int start, int end, int idx, int val) {
    if (start == end) { // Хамгийн доод зангилаа (leaf node)
        tree[node] += val;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) { // Зүүн хүүхдийн мужид байвал
            update(2 * node, start, mid, idx, val);
        } else { // Баруун хүүхдийн мужид байвал
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        // Эцэг зангилааг хүүхдүүдийнх нь нийлбэрээр шинэчлэх
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}

// Сегмент модны query функц: [L, R] мужид хамаарах тооллын нийлбэрийг олох
int query(int node, int start, int end, int L, int R) {
    // 1. Хүсэлтийн муж (L, R) нь одоогийн зангилааны муж (start, end) -тай давхцахгүй бол
    if (R < start || end < L) {
        return 0; // Нийлбэр 0
    }
    // 2. Одоогийн зангилааны муж (start, end) нь хүсэлтийн муж (L, R) -д бүрэн багтсан бол
    if (L <= start && end <= R) {
        return tree[node]; // Энэ зангилааны утгыг буцаана
    }
    // 3. Хэсэгчилсэн давхцалтай бол, хүүхдүүдээс хүсэлт хийнэ
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, L, R); // Зүүн хүүхдээс
    int p2 = query(2 * node + 1, mid + 1, end, L, R); // Баруун хүүхдээс
    return p1 + p2; // Хоёрынх нь нийлбэрийг буцаана
}

int main() {
    // Хурдан оруулах/гаргахын тулд
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    // Эхний цалингуудыг уншиж, distinct_salaries болон employee_salaries-д нэмэх
    for (int i = 0; i < n; ++i) {
        int salary;
        std::cin >> salary;
        distinct_salaries.push_back(salary);
        employee_salaries[i + 1] = salary; // Ажилчдын ID нь 1-ээс эхэлдэг
    }

    // Бүх хүсэлтүүдийг уншиж, тэдгээрийн утгуудыг distinct_salaries-д нэмэх
    std::vector<std::tuple<char, int, int>> queries_data(q);
    for (int i = 0; i < q; ++i) {
        char type;
        int val1, val2;
        std::cin >> type >> val1 >> val2;
        queries_data[i] = std::make_tuple(type, val1, val2);

        if (type == '!') {
            distinct_salaries.push_back(val2); // Шинэ цалин
        } else { // type == '?'
            distinct_salaries.push_back(val1); // Мужийн доод хязгаар
            distinct_salaries.push_back(val2); // Мужийн дээд хязгаар
        }
    }

    // Координатын шахалт хийх: Эрэмбэлэх ба давхцлыг арилгах
    std::sort(distinct_salaries.begin(), distinct_salaries.end());
    distinct_salaries.erase(std::unique(distinct_salaries.begin(), distinct_salaries.end()), distinct_salaries.end());

    // Цалингийн утгаас шахагдсан индекс рүү хөрвүүлэх map-ийг дүүргэх
    for (int i = 0; i < distinct_salaries.size(); ++i) {
        salary_to_compressed_idx[distinct_salaries[i]] = i;
    }

    int M = distinct_salaries.size(); // Шахагдсан цалингийн утгуудын тоо

    // Сегмент модыг эхний цалингуудаар үүсгэх
    for (int i = 0; i < n; ++i) {
        int current_salary = employee_salaries[i + 1]; // employee_salaries нь 1-ээс эхэлдэг
        int compressed_idx = salary_to_compressed_idx[current_salary];
        update(1, 0, M - 1, compressed_idx, 1); // Энэ цалингийн тооллыг 1-ээр нэмэгдүүлэх
    }

    // Хүсэлтүүдийг боловсруулах
    for (const auto& q_tuple : queries_data) {
        char type = std::get<0>(q_tuple);
        int val1 = std::get<1>(q_tuple);
        int val2 = std::get<2>(q_tuple);

        if (type == '!') {
            int emp_id = val1;
            int new_salary = val2;

            int old_salary = employee_salaries[emp_id];
            
            // Хуучин цалингийн тооллыг хасах
            int old_compressed_idx = salary_to_compressed_idx[old_salary];
            update(1, 0, M - 1, old_compressed_idx, -1);

            // Ажилчны цалингийн бүртгэлийг шинэчлэх
            employee_salaries[emp_id] = new_salary;

            // Шинэ цалингийн тооллыг нэмэх
            int new_compressed_idx = salary_to_compressed_idx[new_salary];
            update(1, 0, M - 1, new_compressed_idx, 1);

        } else { // type == '?'
            int a = val1;
            int b = val2;

            // [a, b] мужид хамаарах шахагдсан индексийг олох
            // lower_bound нь a-аас багагүй эхний элементийн итераторыг буцаана.
            auto it_a = std::lower_bound(distinct_salaries.begin(), distinct_salaries.end(), a);
            // upper_bound нь b-ээс их эхний элементийн итераторыг буцаана. Бидэнд b-ээс ихгүй хамгийн сүүлийн элемент хэрэгтэй тул 1-ээр хасна.
            auto it_b = std::upper_bound(distinct_salaries.begin(), distinct_salaries.end(), b);

            int compressed_a_idx = (it_a == distinct_salaries.end()) ? M : (it_a - distinct_salaries.begin());
            int compressed_b_idx = (it_b == distinct_salaries.begin()) ? -1 : (it_b - distinct_salaries.begin() - 1);
            
            // Хэрэв шахагдсан индекстэй муж хүчингүй бол (жишээ нь a > b эсвэл муж хоосон бол)
            if (compressed_a_idx > compressed_b_idx || compressed_a_idx >= M || compressed_b_idx < 0) {
                std::cout << 0 << "\n";
            } else {
                // Сегмент модноос тооллыг авах
                std::cout << query(1, 0, M - 1, compressed_a_idx, compressed_b_idx) << "\n";
            }
        }
    }

    return 0;
}