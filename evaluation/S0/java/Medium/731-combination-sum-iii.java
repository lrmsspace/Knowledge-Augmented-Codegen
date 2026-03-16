// Source: https://leetcode.com/problems/combination-sum-iii/   |   Difficulty: Medium
//
// Problem Description:
// Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
//
//
// 	Only numbers 1 through 9 are used.
// 	Each number is used at most once.
//
//
// Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.
//
// Example:
// Input: k = 3, n = 7
// Output: [[1,2,4]]
// Explanation:
// 1 + 2 + 4 = 7
// There are no other valid combinations.
//
// Constraints:
// 2 <= k <= 9
// 	1 <= n <= 60
//

class Solution {
    public List<List<Integer>> combinationSum3(int k, int n) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(result, new ArrayList<>(), k, n, 1);
        return result;
        
    }
}
