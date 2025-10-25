
---

## 💡 Intuition
The **Boyer–Moore Voting Algorithm** efficiently finds the majority element in a single pass.  
It keeps track of a **candidate** and a **counter**:
- If the current number matches the candidate, increment the counter.
- Otherwise, decrement the counter.
- When the counter reaches zero, switch the candidate to the current number.

By the end of the array, the candidate will represent the majority element because it occurs more times than all other elements combined.

---

## ⚙️ Approach

1. Initialize:
   - `candidate` (arbitrary at start)
   - `count = 0`
2. Iterate through each number:
   - If `count == 0`, set `candidate = num`.
   - If `num == candidate`, increment `count`; else decrement.
3. After the loop, the `candidate` is the majority element.

---

## 🧩 Code Implementation (Java)

```java
class Solution {
    public int majorityElement(int[] nums) {
        int candidate = nums[0];
        int count = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }
            count += (num == candidate) ? 1 : -1;
        }
        return candidate;
    }
}
