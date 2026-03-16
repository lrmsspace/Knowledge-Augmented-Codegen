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
public:
    int numberOfSpecialChars(string word) {
        unordered_set<char> lowerSet;
        unordered_set<char> specialSet;

        for (char c : word) {
            if (islower(c)) {
                lowerSet.insert(c);
            } else {
                char lowerC = tolower(c);
                if (lowerSet.count(lowerC)) {
                    specialSet.insert(lowerC);
                }
            }
        }

        return specialSet.size();           
    }
};
