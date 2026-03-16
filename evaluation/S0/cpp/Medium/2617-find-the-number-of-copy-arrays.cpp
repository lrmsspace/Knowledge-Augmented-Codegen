// Source: https://leetcode.com/problems/find-the-number-of-copy-arrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array original of length n and a 2D array bounds of length n x 2, where bounds[i] = [ui, vi].
//
// You need to find the number of possible arrays copy of length n such that:
//
//
// 	(copy[i] - copy[i - 1]) == (original[i] - original[i - 1]) for 1 <= i <= n - 1.
// 	ui <= copy[i] <= vi for 0 <= i <= n - 1.
//
//
// Return the number of such arrays.
//
// Example:
// Input: original = [1,2,3,4], bounds = [[1,2],[2,3],[3,4],[4,5]]
//
// Output: 2
//
// Explanation:
//
// The possible arrays are:
//
//
// 	[1, 2, 3, 4]
// 	[2, 3, 4, 5]
//
// Constraints:
// 2 <= n == original.length <= 105
// 	1 <= original[i] <= 109
// 	bounds.length == n
// 	bounds[i].length == 2
// 	1 <= bounds[i][0] <= bounds[i][1] <= 109
//

class Solution {
public:
    int countArrays(vector<int>& original, vector<vector<int>>& bounds) {
        const int MOD = 1e9 + 7;
        long long lowerBound = bounds[0][0];
        long long upperBound = bounds[0][1];

        for (size_t i = 1; i < original.size(); ++i) {
            int diff = original[i] - original[i - 1];
            lowerBound = std::max(lowerBound + diff, (long long)bounds[i][0]);
            upperBound = std::min(upperBound + diff, (long long)bounds[i][1]);

            if (lowerBound > upperBound) {
                return 0;
            }
        }

        return (upperBound - lowerBound + 1) % MOD;         
    }
};
