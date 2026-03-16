// Source: https://leetcode.com/problems/maximum-score-words-formed-by-letters/   |   Difficulty: Hard
//
// Problem Description:
// Given a list of words, list of  single letters (might be repeating) and score of every character.
//
// Return the maximum score of any valid set of words formed by using the given letters (words[i] cannot be used two or more times).
//
// It is not necessary to use all characters in letters and each letter can only be used once. Score of letters 'a', 'b', 'c', ... ,'z' is given by score[0], score[1], ... , score[25] respectively.
//
// Example:
// Input: words = ["dog","cat","dad","good"], letters = ["a","a","c","d","d","d","g","o","o"], score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
// Output: 23
// Explanation:
// Score  a=1, c=9, d=5, g=3, o=2
// Given letters, we can form the words "dad" (5+1+5) and "good" (3+2+2+5) with a score of 23.
// Words "dad" and "dog" only get a score of 21.
//
// Constraints:
// 1 <= words.length <= 14
// 	1 <= words[i].length <= 15
// 	1 <= letters.length <= 100
// 	letters[i].length == 1
// 	score.length == 26
// 	0 <= score[i] <= 10
// 	words[i], letters[i] contains only lower case English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        vector<int> letterCount(26, 0);
        for (char c : letters) {
            letterCount[c - 'a']++;
        }

        int maxScore = 0;
        int n = words.size();

        // Generate all subsets of words using bit manipulation
        for (int mask = 0; mask < (1 << n); ++mask) {
            vector<int> currentLetterCount(26, 0);
            int currentScore = 0;
            bool valid = true;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) { // If the i-th word is included in the subset
                    for (char c : words[i]) {
                        currentLetterCount[c - 'a']++;
                        if (currentLetterCount[c - 'a'] > letterCount[c - 'a']) {
                            valid = false; // More letters needed than available
                            break;
                        }
                        currentScore += score[c - 'a']; // Add score for this character
                    }
                    if (!valid) {
                        break; // No need to check further if already invalid
                    }
                }
            }

            if (valid) {
                maxScore = max(maxScore, currentScore); // Update max score if this subset is valid
            }
        }

        return maxScore;            
    }
};
