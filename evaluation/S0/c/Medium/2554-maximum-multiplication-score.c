// Source: https://leetcode.com/problems/maximum-multiplication-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array a of size 4 and another integer array b of size at least 4.
//
// You need to choose 4 indices i0, i1, i2, and i3 from the array b such that i0 < i1 < i2 < i3. Your score will be equal to the value a[0] * b[i0] + a[1] * b[i1] + a[2] * b[i2] + a[3] * b[i3].
//
// Return the maximum score you can achieve.
//
// Example:
// Input: a = [3,2,5,6], b = [2,-6,4,-5,-3,2,-7]
//
// Output: 26
//
// Explanation:
// We can choose the indices 0, 1, 2, and 5. The score will be 3 * 2 + 2 * (-6) + 5 * 4 + 6 * 2 = 26.
//
// Constraints:
// a.length == 4
// 	4 <= b.length <= 105
// 	-105 <= a[i], b[i] <= 105
//

long long maxScore(int* a, int aSize, int* b, int bSize) {
    long long dp[4] = {0};
    for (int i = 0; i < bSize; i++) {
        for (int j = 3; j >= 0; j--) {
            long long val = (long long)a[j] * (long long)b[i];
            if (j == 0) {
                dp[j] = fmax(dp[j], val);
            } else {
                dp[j] = fmax(dp[j], dp[j - 1] + val);
            }
        }
    }
    return dp[3];       
}
