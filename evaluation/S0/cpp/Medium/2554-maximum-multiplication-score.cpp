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

class Solution {
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<long long> dp(n, 0);

        // Initialize dp for the first coefficient
        for (int i = 0; i < n; ++i) {
            dp[i] = a[0] * b[i];
            if (i > 0) {
                dp[i] = max(dp[i], dp[i - 1]);
            }
        }

        // Update dp for the remaining coefficients
        for (int coeff = 1; coeff < 4; ++coeff) {
            long long maxPrev = LLONG_MIN;
            for (int i = coeff; i < n; ++i) {
                maxPrev = max(maxPrev, dp[i - 1]);
                dp[i] = maxPrev + (long long)a[coeff] * b[i];
                if (i > coeff) {
                    dp[i] = max(dp[i], dp[i - 1]);
                }
            }
        }

        return dp[n - 1];           
    }
};
