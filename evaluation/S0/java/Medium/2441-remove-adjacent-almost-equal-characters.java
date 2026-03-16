// Source: https://leetcode.com/problems/remove-adjacent-almost-equal-characters/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string word.
//
// In one operation, you can pick any index i of word and change word[i] to any lowercase English letter.
//
// Return the minimum number of operations needed to remove all adjacent almost-equal characters from word.
//
// Two characters a and b are almost-equal if a == b or a and b are adjacent in the alphabet.
//
// Example:
// Input: word = "aaaaa"
// Output: 2
// Explanation: We can change word into "acaca" which does not have any adjacent almost-equal characters.
// It can be shown that the minimum number of operations needed to remove all adjacent almost-equal characters from word is 2.
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists only of lowercase English letters.
//

class Solution {
    public int removeAlmostEqualCharacters(String word) {
        int n = word.length();
        char[] arr = word.toCharArray();
        int count = 0;

        for (int i = 1; i < n; i++) {
            if (isAlmostEqual(arr[i], arr[i - 1])) {
                count++;
                arr[i] = getReplacementChar(arr[i - 1]);
            }
        }

        return count;           
    }
}
