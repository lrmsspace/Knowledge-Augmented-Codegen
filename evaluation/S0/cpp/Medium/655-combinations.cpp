// Source: https://leetcode.com/problems/combinations/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
//
// You may return the answer in any order.
//
// Example:
// Input: n = 4, k = 2
// Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
// Explanation: There are 4 choose 2 = 6 total combinations.
// Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
//
// Constraints:
// 1 <= n <= 20
// 	1 <= k <= n
//

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> combination;
        backtrack(n, k, 1, combination, result);
        return result;          
    }
};
