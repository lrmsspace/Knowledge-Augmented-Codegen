// Source: https://leetcode.com/problems/string-transformation/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and t of equal length n. You can perform the following operation on the string s:
//
//
// 	Remove a suffix of s of length l where 0 < l < n and append it at the start of s.
// 	For example, let s = 'abcd' then in one operation you can remove the suffix 'cd' and append it in front of s making s = 'cdab'.
//
//
// You are also given an integer k. Return the number of ways in which s can be transformed into t in exactly k operations.
//
// Since the answer can be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcd", t = "cdab", k = 2
// Output: 2
// Explanation: 
// First way:
// In first operation, choose suffix from index = 3, so resulting s = "dabc".
// In second operation, choose suffix from index = 3, so resulting s = "cdab".
//
// Second way:
// In first operation, choose suffix from index = 1, so resulting s = "bcda".
// In second operation, choose suffix from index = 1, so resulting s = "cdab".
//
// Constraints:
// 2 <= s.length <= 5 * 105
// 	1 <= k <= 1015
// 	s.length == t.length
// 	s and t consist of only lowercase English alphabets.
//

class Solution {
    public int numberOfWays(String s, String t, long k) {
        int n = s.length();
        final int MOD = 1_000_000_007;

        // Count the number of valid rotations
        int validRotations = 0;
        String doubledS = s + s;
        for (int i = 1; i < n; i++) {
            if (doubledS.substring(i, i + n).equals(t)) {
                validRotations++;
            }
        }

        // If no valid rotations, return 0
        if (validRotations == 0) {
            return 0;
        }

        // Matrix exponentiation to count ways
        long[][] transitionMatrix = {
            {validRotations - 1, validRotations},
            {n - validRotations, n - validRotations - 1}
        };

        long[][] resultMatrix = matrixExponentiation(transitionMatrix, k);

        // The answer is in the first row and second column of the resulting matrix
        return (int)(resultMatrix[0][1] % MOD);         
    }
}
