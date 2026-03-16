// Source: https://leetcode.com/problems/count-the-number-of-special-characters-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.
//
// Return the number of special letters in word.
//
// Example:
// Input: word = "aaAbcBC"
//
// Output: 3
//
// Explanation:
//
// The special characters are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists of only lowercase and uppercase English letters.
//

class Solution {
    public int numberOfSpecialChars(String word) {
        boolean[] lowerSeen = new boolean[26];
        boolean[] upperSeen = new boolean[26];
        boolean[] isSpecial = new boolean[26];

        for (char c : word.toCharArray()) {
            if (Character.isLowerCase(c)) {
                int index = c - 'a';
                if (!upperSeen[index]) {
                    lowerSeen[index] = true;
                }
            } else {
                int index = c - 'A';
                if (lowerSeen[index]) {
                    isSpecial[index] = true;
                }
                upperSeen[index] = true;
            }
        }

        int specialCount = 0;
        for (boolean special : isSpecial) {
            if (special) {
                specialCount++;
            }
        }

        return specialCount;            
    }
}
