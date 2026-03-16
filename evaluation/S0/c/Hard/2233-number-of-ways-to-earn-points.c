// Source: https://leetcode.com/problems/number-of-ways-to-earn-points/   |   Difficulty: Hard
//
// Problem Description:
// There is a test that has n types of questions. You are given an integer target and a 0-indexed 2D integer array types where types[i] = [counti, marksi] indicates that there are counti questions of the ith type, and each one of them is worth marksi points.
//
//
//
//
// Return the number of ways you can earn exactly target points in the exam. Since the answer may be too large, return it modulo 109 + 7.
//
// Note that questions of the same type are indistinguishable.
//
//
// 	For example, if there are 3 questions of the same type, then solving the 1st and 2nd questions is the same as solving the 1st and 3rd questions, or the 2nd and 3rd questions.
//
// Example:
// Input: target = 6, types = [[6,1],[3,2],[2,3]]
// Output: 7
// Explanation: You can earn 6 points in one of the seven ways:
// - Solve 6 questions of the 0th type: 1 + 1 + 1 + 1 + 1 + 1 = 6
// - Solve 4 questions of the 0th type and 1 question of the 1st type: 1 + 1 + 1 + 1 + 2 = 6
// - Solve 2 questions of the 0th type and 2 questions of the 1st type: 1 + 1 + 2 + 2 = 6
// - Solve 3 questions of the 0th type and 1 question of the 2nd type: 1 + 1 + 1 + 3 = 6
// - Solve 1 question of the 0th type, 1 question of the 1st type and 1 question of the 2nd type: 1 + 2 + 3 = 6
// - Solve 3 questions of the 1st type: 2 + 2 + 2 = 6
// - Solve 2 questions of the 2nd type: 3 + 3 = 6
//
// Constraints:
// 1 <= target <= 1000
// 	n == types.length
// 	1 <= n <= 50
// 	types[i].length == 2
// 	1 <= counti, marksi <= 50
//

int waysToReachTarget(int target, int** types, int typesSize, int* typesColSize) {
    const int MOD = 1000000007;
    int dp[1001];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < typesSize; i++) {
        int count = types[i][0];
        int marks = types[i][1];
        for (int t = target; t >= 0; t--) {
            for (int c = 1; c <= count; c++) {
                int prev = t - c * marks;
                if (prev < 0) break;
                dp[t] = (dp[t] + dp[prev]) % MOD;
            }
        }
    }
    return dp[target];      
}
