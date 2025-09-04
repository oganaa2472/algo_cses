#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> preOrderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    vector<int> res;
    preOrderTraversal(root, res);
    return res;
}

void preOrderTraversal(TreeNode* root, vector<int>& res) {
    if (root == nullptr) return;
    res.push_back(root->val);
    preOrderTraversal(root->left, res);
    preOrderTraversal(root->right, res);
    return res;
}