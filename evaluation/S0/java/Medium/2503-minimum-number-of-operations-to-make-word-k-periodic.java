// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-word-k-periodic/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word of size n, and an integer k such that k divides n.
//
// In one operation, you can pick any two indices i and j, that are divisible by k, then replace the substring of length k starting at i with the substring of length k starting at j. That is, replace the substring word[i..i + k - 1] with the substring word[j..j + k - 1].
//
// Return the minimum number of operations required to make word k-periodic.
//
// We say that word is k-periodic if there is some string s of length k such that word can be obtained by concatenating s an arbitrary number of times. For example, if word == “ababab”, then word is 2-periodic for s = "ab".
//
// Example:
// Input: word = "leetcodeleet", k = 4
//
// Output: 1
//
// Explanation:
//
// We can obtain a 4-periodic string by picking i = 4 and j = 0. After this operation, word becomes equal to "leetleetleet".
//
// Constraints:
// 1 <= n == word.length <= 105
// 	1 <= k <= word.length
// 	k divides word.length.
// 	word consists only of lowercase English letters.
//

class Solution {
    public int minimumOperationsToMakeKPeriodic(String word, int k) {
        int n = word.length();
        int groups = n / k;
        int[][] count = new int[k][26];

        for (int i = 0; i < n; i++) {
            count[i % k][word.charAt(i) - 'a']++;
        }

        int operations = 0;
        for (int i = 0; i < k; i++) {
            int maxFreq = 0;
            for (int j = 0; j < 26; j++) {
                maxFreq = Math.max(maxFreq, count[i][j]);
            }
            operations += (groups - maxFreq);
        }

        return operations;          
    }
}
