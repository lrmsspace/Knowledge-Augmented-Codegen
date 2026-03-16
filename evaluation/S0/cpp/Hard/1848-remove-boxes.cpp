// Source: https://leetcode.com/problems/remove-boxes/   |   Difficulty: Hard
//
// Problem Description:
// You are given several boxes with different colors represented by different positive numbers.
//
// You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (i.e., composed of k boxes, k >= 1), remove them and get k * k points.
//
// Return the maximum points you can get.
//
// Example:
// Input: boxes = [1,3,2,2,2,3,4,3,1]
// Output: 23
// Explanation:
// [1, 3, 2, 2, 2, 3, 4, 3, 1] 
// ----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
// ----> [1, 3, 3, 3, 1] (1*1=1 points) 
// ----> [1, 1] (3*3=9 points) 
// ----> [] (2*2=4 points)
//
// Constraints:
// 1 <= boxes.length <= 100
// 	1 <= boxes[i] <= 100
//

class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        // dp[l][r][k]: max points for boxes[l..r] with k same color boxes as boxes[r] to the right
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));
        
        function<int(int, int, int)> dfs = [&](int l, int r, int k) {
            if (l > r) return 0;
            if (dp[l][r][k] != 0) return dp[l][r][k];
            
            // Remove boxes[r] and the k same color boxes
            int res = dfs(l, r - 1, 0) + (k + 1) * (k + 1);
            
            // Try to merge boxes[r] with some boxes of the same color in boxes[l..r-1]
            for (int i = l; i < r; i++) {
                if (boxes[i] == boxes[r]) {
                    res = max(res, dfs(l, i, k + 1) + dfs(i + 1, r - 1, 0));
                }
            }
            
            dp[l][r][k] = res;
            return res;
        };
        
        return dfs(0, n - 1, 0);            
    }
};
