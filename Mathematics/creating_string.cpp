#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const long long MOD = 1e9 + 7;
const int MAX = 1000005;  // Maximum size for the factorial array

vector<long long> fact(MAX), invFact(MAX);

// Fast exponentiation (a^b % MOD)
long long power(long long a, long long b) {
    long long result = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) result = (result * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return result;
}

// Precompute factorials and their modular inverses
void precomputeFactorials(int n) {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = power(fact[i], MOD - 2);  // Fermat's little theorem for modular inverse
    }
}

// C(a, b) % MOD
long long nCr(long long a, long long b) {
    if (b < 0 || b > a) return 0;
    return fact[a] * invFact[b] % MOD * invFact[a - b] % MOD;
}

int main() {
    string s;
    cin >> s;
    
    int n = s.length();
    
    // Precompute factorials and inverse factorials up to the length of the string
    precomputeFactorials(n);
    
    // Frequency map to count characters
    unordered_map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    
    // Calculate the total number of distinct permutations
    long long result = fact[n];
    for (auto& entry : freq) {
        result = (result * invFact[entry.second]) % MOD;
    }
    
    cout << result << endl;
    
    return 0;
}
