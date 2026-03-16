// Source: https://leetcode.com/problems/find-the-original-typed-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
//
// You are given a string word, which represents the final output displayed on Alice's screen. You are also given a positive integer k.
//
// Return the total number of possible original strings that Alice might have intended to type, if she was trying to type a string of size at least k.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: word = "aabbccdd", k = 7
//
// Output: 5
//
// Explanation:
//
// The possible strings are: "aabbccdd", "aabbccd", "aabbcdd", "aabccdd", and "abbccdd".
//
// Constraints:
// 1 <= word.length <= 5 * 105
//  word consists only of lowercase English letters.
//  1 <= k <= 2000
//

class Solution {
    public int possibleStringCount(String word, int k) {
        final int MOD = 1_000_000_007;
        int n = word.length();
        long result = 1;
        int count = 1;

        for (int i = 1; i <= n; i++) {
            if (i < n && word.charAt(i) == word.charAt(i - 1)) {
                count++;
            } else {
                for (int j = 1; j <= count - k; j++) {
                    result = (result + nCr(count - 1, j)) % MOD;
                }
                count = 1;
            }
        }

        return (int) result;            
    }
}
