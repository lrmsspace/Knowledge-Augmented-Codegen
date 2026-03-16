// Source: https://leetcode.com/problems/count-the-number-of-special-characters-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.
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
// The special characters in word are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 50
// 	word consists of only lowercase and uppercase English letters.
//

class Solution {
public:
    int numberOfSpecialChars(string word) {
        unordered_set<char> lowerSet, upperSet;
        for (char ch : word) {
            if (islower(ch)) {
                lowerSet.insert(ch);
            } else {
                upperSet.insert(ch);
            }
        }

        int specialCount = 0;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (lowerSet.count(ch) && upperSet.count(toupper(ch))) {
                ++specialCount;
            }
        }

        return specialCount;            
    }
};
