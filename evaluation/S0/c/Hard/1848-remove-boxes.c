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

int removeBoxes(int* boxes, int boxesSize) {
    int dp[100][100][100] = {0};
    for (int len = 1; len <= boxesSize; ++len) {
        for (int i = 0; i + len - 1 < boxesSize; ++i) {
            int j = i + len - 1;
            for (int k = 0; k <= i; ++k) {
                if (i == j) {
                    dp[i][j][k] = (k + 1) * (k + 1);
                } else {
                    int res = (k + 1) * (k + 1) + dp[i + 1][j][0];
                    for (int m = i + 1; m <= j; ++m) {
                        if (boxes[m] == boxes[i]) {
                            res = res > dp[i + 1][m - 1][0] + dp[m][j][k + 1] ? res : dp[i + 1][m - 1][0] + dp[m][j][k + 1];
                        }
                    }
                    dp[i][j][k] = res;
                }
            }
        }
    }
    return dp[0][boxesSize - 1][0];     
}
