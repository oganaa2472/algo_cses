class Solution {
public:
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    int dfs(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& memo) {
        if (memo[i][j] != 0) return memo[i][j];  // Return cached result if available
        
        int maxPath = 1;
        for (auto& dir : directions) {
            int x = i + dir[0], y = j + dir[1];
            if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size() && matrix[x][y] > matrix[i][j]) {
                maxPath = max(maxPath, 1 + dfs(matrix, x, y, memo));
            }
        }
        return memo[i][j] = maxPath;  // Cache result
    }
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        int maxPath = 0;
        vector<vector<int>> memo(matrix.size(), vector<int>(matrix[0].size(), 0));
        
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                maxPath = max(maxPath, dfs(matrix, i, j, memo));
            }
        }
        return maxPath;
    }
};