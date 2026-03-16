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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isValid(string word) {
        if (word.length() < 3) return false;

        bool hasVowel = false;
        bool hasConsonant = false;

        for (char c : word) {
            if (isalnum(c)) {
                if (isalpha(c)) {
                    char lowerC = tolower(c);
                    if (lowerC == 'a' || lowerC == 'e' || lowerC == 'i' || lowerC == 'o' || lowerC == 'u') {
                        hasVowel = true;
                    } else {
                        hasConsonant = true;
                    }
                }
            } else {
                return false; // Invalid character found
            }
        }

        return hasVowel && hasConsonant;            
    }
};
