// Source: https://leetcode.com/problems/verbal-arithmetic-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// Given an equation, represented by words on the left side and the result on the right side.
//
// You need to check if the equation is solvable under the following rules:
//
//
// 	Each character is decoded as one digit (0 - 9).
// 	No two characters can map to the same digit.
// 	Each words[i] and result are decoded as one number without leading zeros.
// 	Sum of numbers on the left side (words) will equal to the number on the right side (result).
//
//
// Return true if the equation is solvable, otherwise return false.
//
// Example:
// Input: words = ["SEND","MORE"], result = "MONEY"
// Output: true
// Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
// Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
//
// Constraints:
// 2 <= words.length <= 5
// 	1 <= words[i].length, result.length <= 7
// 	words[i], result contain only uppercase English letters.
// 	The number of different characters used in the expression is at most 10.
//

class Solution {
    public boolean isSolvable(String[] words, String result) {
        int n = words.length;
        int[] charToDigit = new int[26];
        boolean[] usedDigits = new boolean[10];
        boolean[] leadingChars = new boolean[26];
        Arrays.fill(charToDigit, -1);

        for (String word : words) {
            leadingChars[word.charAt(0) - 'A'] = true;
        }
        leadingChars[result.charAt(0) - 'A'] = true;

        return backtrack(words, result, charToDigit, usedDigits, leadingChars, 0, 0, 0);                    
    }
}
