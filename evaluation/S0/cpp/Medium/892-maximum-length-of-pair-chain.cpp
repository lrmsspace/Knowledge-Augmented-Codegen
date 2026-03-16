// Source: https://leetcode.com/problems/maximum-length-of-pair-chain/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and lefti < righti.
//
// A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this fashion.
//
// Return the length longest chain which can be formed.
//
// You do not need to use up all the given intervals. You can select pairs in any order.
//
// Example:
// Input: pairs = [[1,2],[2,3],[3,4]]
// Output: 2
// Explanation: The longest chain is [1,2] -> [3,4].
//
// Constraints:
// n == pairs.length
// 	1 <= n <= 1000
// 	-1000 <= lefti < righti <= 1000
//

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        int count = 0;
        int currentEnd = INT_MIN;

        for (const auto& p : pairs) {
            if (p[0] > currentEnd) {
                currentEnd = p[1];
                count++;
            }
        }

        return count;           
    }
};
