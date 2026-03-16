// Source: https://leetcode.com/problems/detect-capital/   |   Difficulty: Easy
//
// Problem Description:
// We define the usage of capitals in a word to be right when one of the following cases holds:
//
//
// 	All letters in this word are capitals, like "USA".
// 	All letters in this word are not capitals, like "leetcode".
// 	Only the first letter in this word is capital, like "Google".
//
//
// Given a string word, return true if the usage of capitals in it is right.
//
// Example:
// Input: word = "USA"
// Output: true
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists of lowercase and uppercase English letters.
//

class Solution {
public:
    bool detectCapitalUse(string word) {
        int n = word.size();
        if (n == 1) return true;

        bool firstCapital = isupper(word[0]);
        bool secondCapital = isupper(word[1]);

        if (firstCapital && secondCapital) {
            for (int i = 2; i < n; ++i) {
                if (islower(word[i])) return false;
            }
        } else if (firstCapital && !secondCapital) {
            for (int i = 2; i < n; ++i) {
                if (isupper(word[i])) return false;
            }
        } else {
            for (int i = 1; i < n; ++i) {
                if (isupper(word[i])) return false;
            }
        }

        return true;            
    }
};
