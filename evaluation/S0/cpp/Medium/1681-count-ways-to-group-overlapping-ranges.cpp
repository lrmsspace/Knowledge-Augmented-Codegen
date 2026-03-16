// Source: https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array ranges where ranges[i] = [starti, endi] denotes that all integers between starti and endi (both inclusive) are contained in the ith range.
//
// You are to split ranges into two (possibly empty) groups such that:
//
//
// 	Each range belongs to exactly one group.
// 	Any two overlapping ranges must belong to the same group.
//
//
// Two ranges are said to be overlapping if there exists at least one integer that is present in both ranges.
//
//
// 	For example, [1, 3] and [2, 5] are overlapping because 2 and 3 occur in both ranges.
//
//
// Return the total number of ways to split ranges into two groups. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: ranges = [[6,10],[5,15]]
// Output: 2
// Explanation: 
// The two ranges are overlapping, so they must be in the same group.
// Thus, there are two possible ways:
// - Put both the ranges together in group 1.
// - Put both the ranges together in group 2.
//
// Constraints:
// 1 <= ranges.length <= 105
// 	ranges[i].length == 2
// 	0 <= starti <= endi <= 109
//

class Solution {
public:
    int countWays(vector<vector<int>>& ranges) {
        const int MOD = 1e9 + 7;
        sort(ranges.begin(), ranges.end());

        int groups = 0;
        long long currentEnd = -1;

        for (const auto& range : ranges) {
            if (range[0] > currentEnd) {
                groups++;
                currentEnd = range[1];
            } else {
                currentEnd = max(currentEnd, (long long)range[1]);
            }
        }

        long long result = 1;
        for (int i = 0; i < groups; ++i) {
            result = (result * 2) % MOD;
        }

        return (int)result;         
    }
};
