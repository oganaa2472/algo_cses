#include <iostream>  // Стандарт оролт гаралтын сан
#include <vector>    // Динамик массив ашиглах сан
#include <stack>     // Стек ашиглах сан
#include <algorithm> // std::fill, std::sort, std::unique зэрэг функцүүдэд
#include <queue>     // Топологийн эрэмбэлэлтийн Kahn-ийн алгоритмд зориулсан дугаар (queue)

// --- 1-р үе шат: Анхны граф дээрх DFS - Оройнуудыг дуусгах дарааллаар стект оруулах ---
// u: одоогийн орой
// adj: графын хөршийн жагсаалт (чиглэлтэй ирмэг)
// visited: орой тус бүрийг эргэж очсон эсэхийг тэмдэглэх массив
// st: DFS-ийн дуусгах дарааллаар оройнуудыг хадгалах стек
void dfs1(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::stack<int>& st) {
    visited[u] = true; // Оройг эргэж очсоноор тэмдэглэх
    for (int v : adj[u]) { // Одоогийн оройн бүх хөршөөр дамжих
        if (!visited[v]) { // Хэрэв хөрш нь эргэж очоогүй бол
            dfs1(v, adj, visited, st); // Рекурсивээр дараагийн DFS-ийг хийх
        }
    }
    st.push(u); // Бүх хөрш болон тэдгээрийн хөврөлүүд эргэж дууссаны дараа оройг стект оруулах
}

// --- 2-р үе шат: Урвуу граф дээрх DFS - SCC-уудыг тодорхойлж, ID оноох ---
// u: одоогийн орой
// rev_adj: урвуу графын хөршийн жагсаалт
// visited: орой тус бүрийг эргэж очсон эсэхийг тэмдэглэх массив
// scc_id: орой тус бүр аль SCC-д хамаарахыг хадгалах массив
// current_scc_id: одоо тодорхойлж буй SCC-ийн ID
void dfs2(int u, const std::vector<std::vector<int>>& rev_adj, std::vector<bool>& visited, std::vector<int>& scc_id, int current_scc_id) {
    visited[u] = true;         // Оройг эргэж очсоноор тэмдэглэх
    scc_id[u] = current_scc_id; // Оройг одоогийн SCC-ийн ID-д оноох
    for (int v : rev_adj[u]) { // Одоогийн оройн урвуу граф дахь хөршөөр дамжих
        if (!visited[v]) { // Хэрэв хөрш нь эргэж очоогүй бол
            dfs2(v, rev_adj, visited, scc_id, current_scc_id); // Рекурсивээр DFS хийх
        }
    }
}

int main() {
    // Оролт/гаралтын хурдыг нэмэгдүүлэх
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m; // Өрөөний тоо (n) ба туннелын тоо (m)
    std::cin >> n >> m;

    // Өрөө тус бүрийн зоосны тоог хадгалах массив (0-ээс n-1 хүртэлх индекс)
    std::vector<long long> coins(n); 
    for (int i = 0; i < n; ++i) {
        std::cin >> coins[i];
    }

    // Анхны граф болон урвуу графын хөршийн жагсаалт (0-ээс n-1 хүртэлх индекс)
    std::vector<std::vector<int>> adj(n);     
    std::vector<std::vector<int>> rev_adj(n); 

    // Туннелуудыг уншиж, граф байгуулах (1-ээс n хүртэлх индексийг 0-ээс n-1 рүү хөрвүүлэх)
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u; --v; // 0-based индекс рүү хөрвүүлэх
        adj[u].push_back(v);     // u-ээс v руу ирмэг нэмэх
        rev_adj[v].push_back(u); // v-ээс u руу урвуу ирмэг нэмэх
    }

    // --- Косаражугийн Алгоритмын 1-р үе шат ---
    std::vector<bool> visited(n, false); // Эргэж очсон оройнуудыг тэмдэглэх
    std::stack<int> st; // DFS-ийн дуусгах дарааллаар оройнуудыг хадгалах стек
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) { // Хэрэв орой эргэж очоогүй бол
            dfs1(i, adj, visited, st); // DFS хийх
        }
    }

    // --- Косаражугийн Алгоритмын 2-р үе шат ---
    std::fill(visited.begin(), visited.end(), false); // visited массивыг дахин эхлүүлэх
    std::vector<int> scc_id(n, -1); // Орой тус бүр аль SCC-д хамаарахыг хадгалах
    int scc_count = 0; // Олдсон SCC-ийн нийт тоо

    while (!st.empty()) { // Стек хоосон биш байвал
        int u = st.top(); // Стекээс хамгийн сүүлд орсон оройг авах
        st.pop();         // Стекээс хасах
        if (!visited[u]) { // Хэрэв орой эргэж очоогүй бол (шинэ SCC-ийн эхлэл)
            dfs2(u, rev_adj, visited, scc_id, scc_count); // Урвуу граф дээр DFS хийж, SCC-ийг тодорхойлох
            scc_count++; // Шинэ SCC олдсон тул тоог нэмэгдүүлэх
        }
    }

    // Хоосон графын (n=0) тохиолдлыг зохицуулах
    if (n == 0) {
        std::cout << 0 << "\n";
        return 0;
    }

    // --- SCC бүрийн зоосны нийлбэрийг тооцоолж, Нягтруулсан Граф байгуулах ---
    std::vector<long long> scc_coins_sum(scc_count, 0); // SCC бүрийн нийт зоос
    for (int i = 0; i < n; ++i) {
        scc_coins_sum[scc_id[i]] += coins[i]; // Оройн зоосыг хамаарах SCC-ийн нийлбэрт нэмэх
    }

    std::vector<std::vector<int>> condensed_adj(scc_count); // Нягтруулсан графын хөршийн жагсаалт
    std::vector<int> indegree(scc_count, 0); // Нягтруулсан графын орой тус бүрийн орох ирмэгийн тоо

    // Нягтруулсан графын ирмэгүүдийг нэмж, орох ирмэгийн тоог тооцоолох
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            if (scc_id[u] != scc_id[v]) { // Хэрэв ирмэг өөр SCC хооронд бол
                condensed_adj[scc_id[u]].push_back(scc_id[v]); // Нягтруулсан графд ирмэг нэмэх
            }
        }
    }
    
    // Нягтруулсан графын ирмэгүүдийг давхардлаас цэвэрлэж, орох ирмэгийн тоог зөв тооцоолох
    for (int i = 0; i < scc_count; ++i) {
        std::sort(condensed_adj[i].begin(), condensed_adj[i].end()); // Ирмэгүүдийг эрэмбэлэх
        condensed_adj[i].erase(std::unique(condensed_adj[i].begin(), condensed_adj[i].end()), condensed_adj[i].end()); // Давхардлыг арилгах
        for (int neighbor_scc : condensed_adj[i]) {
            indegree[neighbor_scc]++; // Хөрш SCC-ийн орох ирмэгийн тоог нэмэгдүүлэх
        }
    }

    // --- Нягтруулсан DAG дээрх Динамик Програмчлал (Хамгийн урт зам) ---
    std::vector<long long> dp(scc_count); // DP массив: тухайн SCC-д төгссөн замын хамгийн их зоосны нийлбэр
    std::queue<int> q; // Топологийн эрэмбэлэлтэд зориулсан дугаар

    // DP утгуудыг эхлүүлэх ба 0 орох ирмэгтэй SCC-уудыг дугаарт хийх
    for (int i = 0; i < scc_count; ++i) {
        dp[i] = scc_coins_sum[i]; // Хамгийн багадаа тухайн SCC-ийн зоос
        if (indegree[i] == 0) {
            q.push(i); // Орох ирмэггүй SCC-г дугаарт нэмэх (эдгээр нь замын эхлэл болж чадна)
        }
    }

    long long max_total_coins = 0; // Цуглуулж болох хамгийн их зоосны нийлбэр

    // Эхлэлийн цэгүүдээс хамгийн их зоосыг авна (нэг оройтой граф эсвэл ирмэггүй)
    if (scc_count > 0) {
        max_total_coins = *std::max_element(dp.begin(), dp.end());
    }
    
    // Kahn-ийн алгоритмаар топологийн эрэмбээр давтаж, DP-г тооцоолох
    while (!q.empty()) {
        int u_scc = q.front();
        q.pop();

        // Одоогийн SCC хүртэлх замаар цуглуулсан зоосны хамгийн ихийг шинэчлэх
        max_total_coins = std::max(max_total_coins, dp[u_scc]);

        // Хөрш SCC-ээр дамжих
        for (int v_scc : condensed_adj[u_scc]) {
            // v_scc-д хүрэх замын зоосны нийлбэрийг шинэчлэх
            dp[v_scc] = std::max(dp[v_scc], dp[u_scc] + scc_coins_sum[v_scc]);
            
            // v_scc-ийн орох ирмэгийн тоог хасах
            indegree[v_scc]--;
            // Хэрэв орох ирмэг нь 0 болсон бол дугаарт нэмэх
            if (indegree[v_scc] == 0) {
                q.push(v_scc);
            }
        }
    }
    
    // Хамгийн их цуглуулсан зоосны нийлбэрийг хэвлэх
    std::cout << max_total_coins << "\n";

    return 0;
}