// Source: https://leetcode.com/problems/valid-word/   |   Difficulty: Easy
//
// Problem Description:
// A word is considered valid if:
//
//
// 	It contains a minimum of 3 characters.
// 	It contains only digits (0-9), and English letters (uppercase and lowercase).
// 	It includes at least one vowel.
// 	It includes at least one consonant.
//
//
// You are given a string word.
//
// Return true if word is valid, otherwise, return false.
//
// Example:
// Input: word = "234Adas"
//
// Output: true
//
// Explanation:
//
// This word satisfies the conditions.
//
// Constraints:
// 1 <= word.length <= 20
// 	word consists of English uppercase and lowercase letters, digits, '@', '#', and '$'.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isValid(String word) {
        if (word.length() < 3) {
            return false;
        }

        boolean hasVowel = false;
        boolean hasConsonant = false;

        for (char ch : word.toCharArray()) {
            if (Character.isDigit(ch) || Character.isLetter(ch)) {
                if (isVowel(ch)) {
                    hasVowel = true;
                } else if (Character.isLetter(ch)) {
                    hasConsonant = true;
                }
            } else {
                return false;
            }
        }

        return hasVowel && hasConsonant;            
    }
}
