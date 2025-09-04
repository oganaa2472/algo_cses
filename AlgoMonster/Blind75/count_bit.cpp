#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Method 1: Dynamic Programming - Most efficient O(n) solution
    // Uses the relationship: countBits[i] = countBits[i/2] + (i % 2)
    vector<int> countBits(int n) {
        vector<int> result(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            result[i] = result[i >> 1] + (i & 1);
        }
        return result;
    }
    
    // Method 2: Dynamic Programming with i & (i-1) trick
    // Uses the relationship: countBits[i] = countBits[i & (i-1)] + 1
    vector<int> countBits2(int n) {
        vector<int> result(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            result[i] = result[i & (i - 1)] + 1;
        }
        return result;
    }
    
    // Method 3: Manual bit counting - Good for understanding
    vector<int> countBits3(int n) {
        vector<int> result(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            int count = 0;
            int num = i;
            while (num > 0) {
                count += num & 1;
                num >>= 1;
            }
            result[i] = count;
        }
        return result;
    }
    
    // Method 4: Using built-in popcount (your original approach)
    vector<int> countBits4(int n) {
        vector<int> result(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            result[i] = __builtin_popcount(i);  // GCC/Clang
            // result[i] = __popcount(i);       // MSVC
        }
        return result;
    }
    
    // Method 5: Lookup table approach (for small numbers)
    vector<int> countBits5(int n) {
        vector<int> result(n + 1, 0);
        int lookup[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
        
        for (int i = 0; i <= n; i++) {
            int count = 0;
            int num = i;
            while (num > 0) {
                count += lookup[num & 15];  // Process 4 bits at a time
                num >>= 4;
            }
            result[i] = count;
        }
        return result;
    }
};

int main() {
    Solution solution;
    int n = 10;
    
    cout << "Counting Bits for numbers 0 to " << n << ":" << endl;
    cout << "=========================================" << endl;
    
    // Test all methods
    vector<int> result1 = solution.countBits(n);
    vector<int> result2 = solution.countBits2(n);
    vector<int> result3 = solution.countBits3(n);
    vector<int> result4 = solution.countBits4(n);
    vector<int> result5 = solution.countBits5(n);
    
    cout << "Number | Method1 | Method2 | Method3 | Method4 | Method5" << endl;
    cout << "-------|---------|---------|---------|---------|---------" << endl;
    
    for (int i = 0; i <= n; i++) {
        printf("%6d | %7d | %7d | %7d | %7d | %7d\n", 
               i, result1[i], result2[i], result3[i], result4[i], result5[i]);
    }
    
    cout << "\nMethod Explanations:" << endl;
    cout << "===================" << endl;
    cout << "Method 1 (DP with i/2): Uses the fact that i and i/2 differ by at most 1 bit" << endl;
    cout << "Method 2 (DP with i&(i-1)): Uses the fact that i&(i-1) removes the least significant 1" << endl;
    cout << "Method 3 (Manual): Counts bits manually by checking each bit" << endl;
    cout << "Method 4 (Built-in): Uses compiler's optimized popcount function" << endl;
    cout << "Method 5 (Lookup): Uses a lookup table for 4-bit chunks" << endl;
    
    cout << "\nTime Complexity Analysis:" << endl;
    cout << "=========================" << endl;
    cout << "Method 1: O(n) - Each number processed once" << endl;
    cout << "Method 2: O(n) - Each number processed once" << endl;
    cout << "Method 3: O(n log n) - Each number takes log n time" << endl;
    cout << "Method 4: O(n) - Built-in function is O(1)" << endl;
    cout << "Method 5: O(n) - Each number processed once" << endl;
    
    cout << "\nSpace Complexity: O(n) for all methods" << endl;
    
    cout << "\nKey Insights:" << endl;
    cout << "=============" << endl;
    cout << "1. countBits[i] = countBits[i/2] + (i % 2)" << endl;
    cout << "2. countBits[i] = countBits[i & (i-1)] + 1" << endl;
    cout << "3. i & (i-1) removes the least significant 1-bit" << endl;
    cout << "4. i >> 1 is equivalent to i/2 but faster" << endl;
    cout << "5. i & 1 is equivalent to i % 2 but faster" << endl;
    
    return 0;
}