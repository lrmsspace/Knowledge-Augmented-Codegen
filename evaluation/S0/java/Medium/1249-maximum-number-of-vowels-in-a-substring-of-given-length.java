// Source: https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.
//
// Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
//
// Example:
// Input: s = "abciiidef", k = 3
// Output: 3
// Explanation: The substring "iii" contains 3 vowel letters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	1 <= k <= s.length
//

class Solution {
    public int maxVowels(String s, int k) {
        int maxVowels = 0;
        int currentVowels = 0;
        int left = 0;

        for (int right = 0; right < s.length(); right++) {
            char rightChar = s.charAt(right);
            if (isVowel(rightChar)) {
                currentVowels++;
            }

            if (right - left + 1 > k) {
                char leftChar = s.charAt(left);
                if (isVowel(leftChar)) {
                    currentVowels--;
                }
                left++;
            }

            if (right - left + 1 == k) {
                maxVowels = Math.max(maxVowels, currentVowels);
            }
        }

        return maxVowels;           
    }
}
