#include <iostream>
#include <algorithm>
#include <climits>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int max_sum = INT_MIN; // Initialize to lowest to handle negative values
        max_gain(root, max_sum); 
        return max_sum; // Return the updated maximum path sum
    }

private:
    int max_gain(TreeNode* node, int& max_sum) {
        if (!node) return 0; // Base case

        // Recursively calculate the maximum gain from left and right subtrees
        int left_gain = std::max(max_gain(node->left, max_sum), 0); // Consider only non-negative gains
        int right_gain = std::max(max_gain(node->right, max_sum), 0);

        // Current node's maximum path sum including both subtrees
        int current_max_path = node->val + left_gain + right_gain;

        // Update the global maximum path sum with the current node's maximum path sum
        max_sum = std::max(max_sum, current_max_path);

        // Return the maximum gain to be used by parent node (either including left or right child)
        return node->val + std::max(left_gain, right_gain);
    }
};