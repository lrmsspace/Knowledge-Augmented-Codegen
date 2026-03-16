// Source: https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s.
//
// A string t is called good if all characters of t occur the same number of times.
//
// You can perform the following operations any number of times:
//
//
//  Delete a character from s.
//  Insert a character in s.
//  Change a character in s to its next letter in the alphabet.
//
//
// Note that you cannot change 'z' to 'a' using the third operation.
//
// Return the minimum number of operations required to make s good.
//
// Example:
// Input: s = "acab"
//
// Output: 1
//
// Explanation:
//
// We can make s good by deleting one occurrence of character 'a'.
//
// Constraints:
// 3 <= s.length <= 2 * 104
//  s contains only lowercase English letters.
//

class Solution {
    public int makeStringGood(String s) {
        int n = s.length();
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        int minOperations = Integer.MAX_VALUE;

        for (int targetFreq = 1; targetFreq <= n; targetFreq++) {
            int currentOperations = 0;
            for (int f : freq) {
                if (f == 0) continue;
                if (f < targetFreq) {
                    currentOperations += (targetFreq - f);
                } else if (f > targetFreq) {
                    currentOperations += (f - targetFreq);
                }
            }
            minOperations = Math.min(minOperations, currentOperations);
        }

        return minOperations;           
    }
}
