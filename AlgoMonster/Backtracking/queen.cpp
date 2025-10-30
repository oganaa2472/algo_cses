/*
Index = j - i + 3

index 0 → (3,0)
index 1 → (2,0) (3,1)
index 2 → (1,0) (2,1) (3,2)
index 3 → (0,0) (1,1) (2,2) (3,3)
index 4 → (0,1) (1,2) (2,3)
index 5 → (0,2) (1,3)
index 6 → (0,3)
So indices also go from 0 → 6 (again 2n - 1 total).*/
class Solution {
public:
    int n ;
    vector<vector<string>> solutions;
    vector<int> column; 
    vector<int> diag1;  
    vector<int> diag2; 
    vector<string> board;
    void solve(int i){
        if(i==n) {
            solutions.push_back(board);
        }
        for(int j = 0;j<n;j++){
            if (column[j] || diag1[j + i] || diag2[j - i + n - 1]) 
                continue;
            board[j][i] ='Q';
            column[j] = diag1[j + i] = diag2[j - i + n - 1] = 1;
            solve(i+1);
            board[j][i] = '.';
            column[j] = diag1[j + i] = diag2[j - i + n - 1] = 0;
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        solutions.clear();
        column.assign(n, 0);
        diag1.assign(2 * n - 1, 0);
        diag2.assign(2 * n - 1, 0);
        board.assign(n, string(n, '.'));
        solve(0);
        return solutions;
    }
};