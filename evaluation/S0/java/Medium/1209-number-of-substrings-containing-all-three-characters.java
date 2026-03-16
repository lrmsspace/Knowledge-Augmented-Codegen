// Source: https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s consisting only of characters a, b and c.
//
// Return the number of substrings containing at least one occurrence of all these characters a, b and c.
//
// Example:
// Input: s = "abcabc"
// Output: 10
// Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).
//
// Constraints:
// 3 <= s.length <= 5 x 10^4
// 	s only consists of a, b or c characters.
//

class Solution {
    public int numberOfSubstrings(String s) {
        int n = s.length();
        int count = 0;
        int left = 0;
        int[] charCount = new int[3]; // To store counts of 'a', 'b', and 'c'

        for (int right = 0; right < n; right++) {
            charCount[s.charAt(right) - 'a']++;

            // Move the left pointer to the right as long as we have at least one of each character
            while (charCount[0] > 0 && charCount[1] > 0 && charCount[2] > 0) {
                count += n - right; // All substrings starting from left to the end are valid
                charCount[s.charAt(left) - 'a']--;
                left++;
            }
        }

        return count;           
    }
}
