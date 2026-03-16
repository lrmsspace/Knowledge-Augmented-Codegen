// Source: https://leetcode.com/problems/count-k-reducible-numbers-less-than-n/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s representing a number n in its binary form.
//
// You are also given an integer k.
//
// An integer x is called k-reducible if performing the following operation at most k times reduces it to 1:
//
//
// 	Replace x with the count of set bits in its binary representation.
//
//
// For example, the binary representation of 6 is "110". Applying the operation once reduces it to 2 (since "110" has two set bits). Applying the operation again to 2 (binary "10") reduces it to 1 (since "10" has one set bit).
//
// Return an integer denoting the number of positive integers less than n that are k-reducible.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "111", k = 1
//
// Output: 3
//
// Explanation: 
//
// n = 7. The 1-reducible integers less than 7 are 1, 2, and 4.
//
// Constraints:
// 1 <= s.length <= 800
// 	s has no leading zeros.
// 	s consists only of the characters '0' and '1'.
// 	1 <= k <= 5
//

class Solution {
    public int countKReducibleNumbers(String s, int k) {
        int MOD = (int)1e9 + 7;
        int n = s.length();
        
        // Precompute the number of steps to reduce each number to 1
        int[] steps = new int[n + 1];
        for (int i = 2; i <= n; i++) {
            steps[i] = steps[Integer.bitCount(i)] + 1;
        }
        
        // Precompute binomial coefficients
        int[][] comb = new int[n + 1][n + 1];
        for (int i = 0; i <= n; i++) {
            comb[i][0] = comb[i][i] = 1;
            for (int j = 1; j < i; j++) {
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
            }
        }
        
        int result = 0;
        int onesCount = 0;
        
        // Count k-reducible numbers less than n
        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == '1') {
                int remainingBits = n - i - 1;
                for (int j = 0; j <= remainingBits; j++) {
                    int totalOnes = onesCount + j;
                    if (totalOnes > 0 && steps[totalOnes] == k - 1) {
                        result = (result + comb[remainingBits][j]) % MOD;
                    }
                }
                onesCount++;
            }
        }
        
        // Check if k == 1, we need to include the number 1 itself
        if (k == 1) {
            result = (result + MOD - 1) % MOD; // Exclude zero
        }
        
        return result;          
    }
}
