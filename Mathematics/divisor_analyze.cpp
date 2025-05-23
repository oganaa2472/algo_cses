#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

using namespace std;

// Хурдавчилсан зэрэг олох функц (base^exp mod mod).
long long power_mod(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod; // Суурийг модулоор авна.
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % mod; // Хэрэв зэрэг сондгой бол хариутай үржүүлнэ.
        base = (__int128)base * base % mod; // Суурийг квадратлана.
        exp /= 2; // Зэргийг хоёр дахин багасгана.
    }
    return res;
}

// Модуло урвуу олох функц (n^-1 mod mod).
// Фермагийн Бага Теорем ашигласан (mod нь анхны тоо байх ёстой).
long long modInverse(long long n, long long mod) {
    return power_mod(n, mod - 2, mod);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; // Анхны үржигдэхүүнд задалалтын хэсгийн тоо
    cin >> n;

    long long MOD = 1e9 + 7; // Модулын утга (10^9 + 7)
    long long MOD_EXP = 1e9 + 6; // Зэрэг олоход ашиглах модул (MOD - 1)
    long long BIG_MOD = 2 * MOD_EXP; // Бүтээгдэхүүний зэрэг тооцоолоход ашиглах том модул (2 * (MOD - 1))

    // Анхны үржигдэхүүн (p) болон түүний зэрэг (a) хослолуудыг хадгалах вектор.
    vector<pair<long long, long long>> prime_factors(n);

    // Үр дүнгийн хувьсагчид
    long long num_divisors = 1;      // 1. Хуваагчдын тоо mod MOD
    long long sum_divisors = 1;        // 2. Хуваагчдын нийлбэр mod MOD
    // 3. Хуваагчдын үржвэр тооцоолоход хэрэг болох tau(N) mod BIG_MOD
    long long product_exponent_tau_big_mod = 1;

    // Оролтоос n ширхэг анхны үржигдэхүүн p болон зэрэг a-г уншиж, тооцоо хийх.
    for (int i = 0; i < n; ++i) {
        long long p, a; // Анхны тоо (x), зэрэг (k)
        cin >> p >> a;
        prime_factors[i] = {p, a}; // Хослолыг хадгална (сүүлд хэрэг болно).

        // 1. Хуваагчдын Тоог Тооцоолох (хэсэгчилсэн)
        // Томьёо: tau(N) = Product (ai + 1)
        num_divisors = (num_divisors * (a + 1)) % MOD;

        // 2. Хуваагчдын Нийлбэрийг Тооцоолох (хэсэгчилсэн)
        // Геометрийн цувааны нийлбэр: S_i = 1 + p^1 + ... + p^a mod MOD
        // p % MOD == 1 үед тусгай тохиолдол (нийлбэр нь a+1 болох)-г шалгана.
        if (p % MOD == 1) {
            sum_divisors = (sum_divisors * (a % MOD + 1) % MOD) % MOD; // (a+1) % MOD
        } else {
            // Ерөнхий тохиолдол: S_i = (p^(a+1) - 1) * (p - 1)^-1 mod MOD
            long long numerator = (power_mod(p, a + 1, MOD) - 1 + MOD) % MOD; // p^(a+1) - 1 mod MOD
            long long denominator_inverse = modInverse(p - 1, MOD); // (p - 1)^-1 mod MOD
            long long geometric_sum = (numerator * denominator_inverse) % MOD; // S_i mod MOD
            sum_divisors = (sum_divisors * geometric_sum) % MOD; // Нийт нийлбэрт үржүүлнэ.
        }

        // 3. Хуваагчдын Үржвэрийн зэрэг тооцоолоход хэрэг болох хэсэг (tau(N) mod BIG_MOD)
        // product_exponent_tau_big_mod = Product (ai + 1) mod BIG_MOD
        // a+1 их байж болох тул (a+1) % BIG_MOD авна.
        product_exponent_tau_big_mod = (__int128)product_exponent_tau_big_mod * ((a + 1) % BIG_MOD) % BIG_MOD;
    }

    // 3. Хуваагчдын Үржвэрийг Эцсийн Байдлаар Тооцоолох
    // Томьёо: P(N) = Product (p_i ^ (a_i * tau(N) / 2)) mod MOD
    // Үүний тулд a_i * tau(N) / 2 зэргийг MOD_EXP (10^9 + 6) модулоор тооцоолох хэрэгтэй.
    long long product_divisors = 1; // 3. Хуваагчдын үржвэр mod MOD

    // Өмнө хадгалсан (p_i, a_i) хослолуудыг дахин ашиглана.
    for (int i = 0; i < n; ++i) {
        long long p = prime_factors[i].first;
        long long a = prime_factors[i].second;

        // p_i-ийн зэрэг: E_i = a * tau(N) / 2.
        // E_i-г MOD_EXP (10^9 + 6) модулоор тооцоолно.
        // E_i mod (10^9 + 6) = ((a * tau(N)) mod (2 * (10^9 + 6))) / 2
        
        // (a * tau(N)) mod BIG_MOD (2 * (10^9 + 6))
        // a их байж болох тул a % BIG_MOD авна.
        long long a_big_mod = a % BIG_MOD;
        // a * tau(N) mod BIG_MOD = (a mod BIG_MOD) * (tau(N) mod BIG_MOD) mod BIG_MOD
        long long X_big_mod = (__int128)a_big_mod * product_exponent_tau_big_mod % BIG_MOD;

        // Зэрэг MOD_EXP модулоор: X_big_mod / 2 (бүхэл тоон хуваах).
        // a * tau(N) үргэлж тэгш байдаг тул X_big_mod ч тэгш байна.
        long long exponent_mod_exp = X_big_mod / 2;

        // p_i ^ (exponent_mod_exp) mod MOD
        long long p_power_mod = power_mod(p, exponent_mod_exp, MOD);

        // Нийт үржвэрт p_power_mod-г үржүүлнэ.
        product_divisors = (product_divisors * p_power_mod) % MOD;
    }

    // Үр дүн гурвыг 10^9 + 7 модулоор хэвлэх.
    cout << num_divisors << " " << sum_divisors << " " << product_divisors << endl;

    return 0;
}