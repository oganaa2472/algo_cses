#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /*
     * Single Number III - Find two numbers that appear only once
     * 
     * Problem: Given an integer array nums, in which exactly two elements appear only once 
     * and all the other elements appear exactly twice. Find the two elements that appear only once.
     * 
     * Approach: Use XOR properties and bit manipulation
     * 
     * Key Insights:
     * 1. XOR of a number with itself = 0
     * 2. XOR of a number with 0 = the number itself
     * 3. XOR is associative and commutative
     * 4. If we XOR all numbers, pairs cancel out, leaving xor_sum of the two single numbers
     * 5. The two single numbers must differ in at least one bit position
     * 6. We can use this differing bit to separate the numbers into two groups
     */
    vector<int> singleNumberIII(vector<int>& nums) {
        int n = nums.size();
        int xor_sum = 0;
        
        // Step 1: XOR all numbers to get xor_sum of the two single numbers
        // All pairs will cancel out (a ^ a = 0), leaving only the two single numbers
        for(int i = 0; i < n; i++) {
            xor_sum ^= nums[i];
        }
        
        // Step 2: Find the rightmost set bit in xor_sum
        // This bit must be different between the two single numbers
        // We use x & -x to isolate the rightmost set bit
        int rightmost_set_bit = xor_sum & -xor_sum;
        
        // Step 3: Separate numbers into two groups based on this bit
        // Group 1: Numbers that have this bit set
        // Group 2: Numbers that don't have this bit set
        // The two single numbers will be in different groups
        int num1 = 0, num2 = 0;
        for(int i = 0; i < n; i++) {
            if(nums[i] & rightmost_set_bit) {
                // This number has the rightmost set bit
                num1 ^= nums[i];
            } else {
                // This number doesn't have the rightmost set bit
                num2 ^= nums[i];
            }
        }
        
        return {num1, num2};
    }
    
    /*
     * Alternative approach with more detailed explanation
     */
    vector<int> singleNumberIII_Detailed(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Calculate XOR of all numbers
        int xor_sum = 0;
        for(int i = 0; i < n; i++) {
            xor_sum ^= nums[i];
        }
        
        // At this point, xor_sum = single1 ^ single2
        // All other numbers (which appear twice) have cancelled out
        
        // Step 2: Find a bit that differs between single1 and single2
        // Since xor_sum is not zero, there must be at least one set bit
        // We find the rightmost set bit using x & -x
        int diff_bit = xor_sum & -xor_sum;
        
        // Step 3: Partition the array based on this bit
        int single1 = 0, single2 = 0;
        
        for(int num : nums) {
            if(num & diff_bit) {
                // Numbers with this bit set go to group 1
                single1 ^= num;
            } else {
                // Numbers without this bit set go to group 2
                single2 ^= num;
            }
        }
        
        return {single1, single2};
    }
};

// Comprehensive explanation of rightmost set bit
class RightmostSetBitExplainer {
public:
    // Method 1: Using xor_sum & -xor_sum (most efficient)
    int findRightmostSetBit1(int num) {
        return num & -num;
    }
    
    // Method 2: Manual approach - find first 1 from right
    int findRightmostSetBit2(int num) {
        if (num == 0) return 0;
        
        int position = 0;
        while ((num & 1) == 0) {
            num >>= 1;
            position++;
        }
        return 1 << position;
    }
    
    // Method 3: Using log2 and power of 2
    int findRightmostSetBit3(int num) {
        if (num == 0) return 0;
        return num & (num - 1) ^ num;
    }
    
    // Method 4: Using built-in functions
    int findRightmostSetBit4(int num) {
        if (num == 0) return 0;
        return 1 << __builtin_ctz(num);  // GCC/Clang
        // return 1 << _tzcnt_u32(num);  // MSVC
    }
    
    // Visualize the process
    void visualizeRightmostSetBit(int num) {
        cout << "Number: " << num << " (Binary: ";
        printBinary(num);
        cout << ")" << endl;
        
        int rightmost = findRightmostSetBit1(num);
        cout << "Rightmost set bit: " << rightmost << " (Binary: ";
        printBinary(rightmost);
        cout << ")" << endl;
        
        cout << "Position: " << __builtin_ctz(num) << endl;
        cout << "----------------------------------------" << endl;
    }
    
    void printBinary(int num) {
        for (int i = 31; i >= 0; i--) {
            cout << ((num >> i) & 1);
            if (i % 8 == 0) cout << " ";
        }
    }
    
    // Explain why xor_sum & -xor_sum works
    void explainXorAndNegative(int xor_sum) {
        cout << "XOR Sum: " << xor_sum << " (Binary: ";
        printBinary(xor_sum);
        cout << ")" << endl;
        
        cout << "Negative: " << -xor_sum << " (Binary: ";
        printBinary(-xor_sum);
        cout << ")" << endl;
        
        int result = xor_sum & -xor_sum;
        cout << "Result: " << result << " (Binary: ";
        printBinary(result);
        cout << ")" << endl;
        
        cout << "This isolates the rightmost set bit!" << endl;
        cout << "=====================================" << endl;
    }
};

int main() {
    Solution solution;
    
    cout << "=== Single Number III - Detailed Explanation ===" << endl << endl;
    
    // Test cases
    vector<vector<int>> testCases = {
        {1, 2, 1, 3, 2, 5},      // Expected: [3, 5]
        {2, 1, 2, 3, 4, 1},      // Expected: [3, 4]
        {1, 2, 3, 4, 5, 6, 1, 2, 3, 4}, // Expected: [5, 6]
        {0, 1, 0, 1, 2, 3},      // Expected: [2, 3]
        {1, 1, 2, 2, 3, 4},      // Expected: [3, 4]
    };
    
    cout << "Test Results:" << endl;
    cout << "=============" << endl;
    
    for (int i = 0; i < testCases.size(); i++) {
        vector<int> nums = testCases[i];
        vector<int> result = solution.singleNumberIII(nums);
        
        cout << "Test " << (i + 1) << ":" << endl;
        cout << "Input: [";
        for (int j = 0; j < nums.size(); j++) {
            cout << nums[j];
            if (j < nums.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
        cout << "Result: [" << result[0] << ", " << result[1] << "]" << endl;
        
        // Detailed step-by-step explanation
        cout << "\nStep-by-step analysis:" << endl;
        
        // Step 1: Calculate XOR sum
        int xor_sum = 0;
        for (int num : nums) xor_sum ^= num;
        cout << "1. XOR sum of all numbers: " << xor_sum << endl;
        
        // Step 2: Find rightmost set bit
        int rightmost_bit = xor_sum & -xor_sum;
        cout << "2. Rightmost set bit: " << rightmost_bit << endl;
        
        // Step 3: Show separation
        cout << "3. Numbers with bit " << rightmost_bit << " set: ";
        for (int num : nums) {
            if (num & rightmost_bit) cout << num << " ";
        }
        cout << endl;
        
        cout << "   Numbers without bit " << rightmost_bit << " set: ";
        for (int num : nums) {
            if (!(num & rightmost_bit)) cout << num << " ";
        }
        cout << endl;
        
        cout << "----------------------------------------" << endl << endl;
    }
    
    cout << "\n=== Algorithm Explanation ===" << endl;
    cout << "=============================" << endl;
    cout << "1. XOR Properties Used:" << endl;
    cout << "   - a ^ a = 0 (number XORed with itself = 0)" << endl;
    cout << "   - a ^ 0 = a (number XORed with 0 = number itself)" << endl;
    cout << "   - XOR is associative: (a ^ b) ^ c = a ^ (b ^ c)" << endl;
    cout << "   - XOR is commutative: a ^ b = b ^ a" << endl;
    
    cout << "\n2. Why This Works:" << endl;
    cout << "   - When we XOR all numbers, pairs cancel out" << endl;
    cout << "   - We're left with: single1 ^ single2" << endl;
    cout << "   - Since single1 ≠ single2, xor_sum ≠ 0" << endl;
    cout << "   - xor_sum has at least one set bit where single1 and single2 differ" << endl;
    
    cout << "\n3. Rightmost Set Bit Trick:" << endl;
    cout << "   - x & -x isolates the rightmost set bit" << endl;
    cout << "   - This bit must be different between single1 and single2" << endl;
    cout << "   - We use this bit to separate numbers into two groups" << endl;
    
    cout << "\n4. Final Separation:" << endl;
    cout << "   - Group 1: Numbers with the differing bit set" << endl;
    cout << "   - Group 2: Numbers without the differing bit set" << endl;
    cout << "   - single1 and single2 will be in different groups" << endl;
    cout << "   - XOR each group to get the single numbers" << endl;
    
    cout << "\n=== Time and Space Complexity ===" << endl;
    cout << "=================================" << endl;
    cout << "Time Complexity: O(n) - We traverse the array twice" << endl;
    cout << "Space Complexity: O(1) - We only use a few variables" << endl;
    
    cout << "\n=== Example Walkthrough ===" << endl;
    cout << "===========================" << endl;
    cout << "Input: [1, 2, 1, 3, 2, 5]" << endl;
    cout << "Step 1: XOR all = 1^2^1^3^2^5 = 3^5 = 6" << endl;
    cout << "Step 2: Rightmost set bit of 6 = 2" << endl;
    cout << "Step 3: Separate by bit 2:" << endl;
    cout << "  - With bit 2: 2, 2, 3 → XOR = 3" << endl;
    cout << "  - Without bit 2: 1, 1, 5 → XOR = 5" << endl;
    cout << "Result: [3, 5]" << endl;
    
    return 0;
}