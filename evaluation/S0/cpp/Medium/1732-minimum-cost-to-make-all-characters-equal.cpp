// Source: https://leetcode.com/problems/minimum-cost-to-make-all-characters-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary string s of length n on which you can apply two types of operations:
//
//
// 	Choose an index i and invert all characters from index 0 to index i (both inclusive), with a cost of i + 1
// 	Choose an index i and invert all characters from index i to index n - 1 (both inclusive), with a cost of n - i
//
//
// Return the minimum cost to make all characters of the string equal.
//
// Invert a character means if its value is '0' it becomes '1' and vice-versa.
//
// Example:
// Input: s = "0011"
// Output: 2
// Explanation: Apply the second operation with i = 2 to obtain s = "0000" for a cost of 2. It can be shown that 2 is the minimum cost to make all characters equal.
//
// Constraints:
// 1 <= s.length == n <= 105
// 	s[i] is either '0' or '1'
//

class Solution {
public:
    long long minimumCost(string s) {
        long long n = s.length();
        vector<long long> prefixCost(n + 1, 0);
        vector<long long> suffixCost(n + 1, 0);

        // Calculate prefix costs to make all characters '0'
        for (long long i = 1; i <= n; ++i) {
            prefixCost[i] = prefixCost[i - 1];
            if (s[i - 1] == '1') {
                prefixCost[i] += i; // Cost to flip from 0 to i-1
            }
        }

        // Calculate suffix costs to make all characters '1'
        for (long long i = n - 1; i >= 0; --i) {
            suffixCost[i] = suffixCost[i + 1];
            if (s[i] == '0') {
                suffixCost[i] += (n - i); // Cost to flip from i to n-1
            }
        }

        // Find the minimum cost by considering all split points
        long long minCost = LLONG_MAX;
        for (long long i = 0; i <= n; ++i) {
            minCost = min(minCost, prefixCost[i] + suffixCost[i]);
        }

        return minCost;         
    }
};
