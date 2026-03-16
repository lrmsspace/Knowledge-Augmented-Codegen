// Source: https://leetcode.com/problems/numbers-with-same-consecutive-differences/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, return an array of all the integers of length n where the difference between every two consecutive digits is k. You may return the answer in any order.
//
// Note that the integers should not have leading zeros. Integers as 02 and 043 are not allowed.
//
// Example:
// Input: n = 3, k = 7
// Output: [181,292,707,818,929]
// Explanation: Note that 070 is not a valid number, because it has leading zeroes.
//
// Constraints:
// 2 <= n <= 9
// 	0 <= k <= 9
//

class Solution {
    public int[] numsSameConsecDiff(int n, int k) {
        List<Integer> result = new ArrayList<>();

        for (int i = 1; i <= 9; i++) {
            backtrack(n - 1, k, i, result);
        }

        return result.stream().mapToInt(i -> i).toArray();          
    }
}
