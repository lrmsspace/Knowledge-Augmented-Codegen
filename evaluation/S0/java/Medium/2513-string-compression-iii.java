// Source: https://leetcode.com/problems/string-compression-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given a string word, compress it using the following algorithm:
//
//
// 	Begin with an empty string comp. While word is not empty, use the following operation:
//
// 	
// 		Remove a maximum length prefix of word made of a single character c repeating at most 9 times.
// 		Append the length of the prefix followed by c to comp.
// 	
// 	
//
//
// Return the string comp.
//
// Example:
// Input: word = "abcde"
//
// Output: "1a1b1c1d1e"
//
// Explanation:
//
// Initially, comp = "". Apply the operation 5 times, choosing "a", "b", "c", "d", and "e" as the prefix in each operation.
//
// For each prefix, append "1" followed by the character to comp.
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists only of lowercase English letters.
//

class Solution {
    public String compressedString(String word) {
        StringBuilder compressed = new StringBuilder();
        int n = word.length();
        int i = 0;

        while (i < n) {
            char currentChar = word.charAt(i);
            int count = 0;

            // Count occurrences of the current character, up to a maximum of 9
            while (i < n && word.charAt(i) == currentChar && count < 9) {
                count++;
                i++;
            }

            // Append the count and the character to the compressed string
            compressed.append(count).append(currentChar);
        }

        return compressed.toString();           
    }
}
