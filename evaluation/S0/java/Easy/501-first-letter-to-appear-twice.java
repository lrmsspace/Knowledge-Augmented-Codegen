// Source: https://leetcode.com/problems/first-letter-to-appear-twice/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s consisting of lowercase English letters, return the first letter to appear twice.
//
// Note:
//
//
// 	A letter a appears twice before another letter b if the second occurrence of a is before the second occurrence of b.
// 	s will contain at least one letter that appears twice.
//
// Example:
// Input: s = "abccbaacz"
// Output: "c"
// Explanation:
// The letter 'a' appears on the indexes 0, 5 and 6.
// The letter 'b' appears on the indexes 1 and 4.
// The letter 'c' appears on the indexes 2, 3 and 7.
// The letter 'z' appears on the index 8.
// The letter 'c' is the first letter to appear twice, because out of all the letters the index of its second occurrence is the smallest.
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists of lowercase English letters.
// 	s has at least one repeated letter.
//

class Solution {
    public char repeatedCharacter(String s) {
        boolean[] seen = new boolean[26];

        for (char c : s.toCharArray()) {
            int index = c - 'a';
            if (seen[index]) {
                return c;
            }
            seen[index] = true;
        }

        // According to the problem constraints, this line should never be reached
        throw new IllegalArgumentException("Input string does not contain any repeated characters.");           
    }
}
