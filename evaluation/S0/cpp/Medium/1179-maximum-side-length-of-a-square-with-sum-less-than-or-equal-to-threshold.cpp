// Source: https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/   |   Difficulty: Medium
//
// Problem Description:
// Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.
//
// Example:
// Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
// Output: 2
// Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 300
// 	0 <= mat[i][j] <= 104
// 	0 <= threshold <= 105
//

class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> prefixSum(m + 1, vector<int>(n + 1, 0));

        // Compute prefix sum
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                prefixSum[i][j] = mat[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            }
        }

        int left = 0, right = min(m, n);
        int maxSide = 0;

        // Binary search for the maximum side length
        while (left <= right) {
            int mid = left + (right - left) / 2;
            bool found = false;

            for (int i = mid; i <= m; ++i) {
                for (int j = mid; j <= n; ++j) {
                    int total = prefixSum[i][j] - prefixSum[i - mid][j] - prefixSum[i][j - mid] + prefixSum[i - mid][j - mid];
                    if (total <= threshold) {
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }

            if (found) {
                maxSide = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return maxSide;         
    }
};
