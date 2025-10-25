**Explanation:**
All non-zero elements `[1, 3, 12]` are moved to the front, and zeros are placed at the end.

---

## ⚙️ Approach

1. Use a pointer `j` to keep track of the **position of the next non-zero element**.
2. Iterate through the array using index `i`:
   - If `nums[i]` is not zero, assign it to `nums[j]` and increment `j`.
3. After processing all non-zero elements, fill the remaining positions in the array with `0`.

This approach preserves the order of non-zero elements and moves zeros to the end **in a single pass**.

---

## 💡 Example Walkthrough

| i | nums[i] | j | Array State          |
|---|----------|---|----------------------|
| 0 | 0        | 0 | [0, 1, 0, 3, 12]    |
| 1 | 1        | 0→1 | [1, 1, 0, 3, 12] |
| 2 | 0        | 1 | [1, 1, 0, 3, 12]    |
| 3 | 3        | 1→2 | [1, 3, 0, 3, 12] |
| 4 | 12       | 2→3 | [1, 3, 12, 3, 12] |
|   | —        |   | Fill zeros: [1, 3, 12, 0, 0] |

---

## 🧩 Code Implementation

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {
                nums[j] = nums[i];
                j++;
            }
        }
        while (j < n) {
            nums[j] = 0;
            j++;
        }
    }
};
