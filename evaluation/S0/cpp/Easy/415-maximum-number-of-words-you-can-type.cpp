// Source: https://leetcode.com/problems/maximum-number-of-words-you-can-type/   |   Difficulty: Easy
//
// Problem Description:
// There is a malfunctioning keyboard where some letter keys do not work. All other keys on the keyboard work properly.
//
// Given a string text of words separated by a single space (no leading or trailing spaces) and a string brokenLetters of all distinct letter keys that are broken, return the number of words in text you can fully type using this keyboard.
//
// Example:
// Input: text = "hello world", brokenLetters = "ad"
// Output: 1
// Explanation: We cannot type "world" because the 'd' key is broken.
//
// Constraints:
// 1 <= text.length <= 104
// 	0 <= brokenLetters.length <= 26
// 	text consists of words separated by a single space without any leading or trailing spaces.
// 	Each word only consists of lowercase English letters.
// 	brokenLetters consists of distinct lowercase English letters.
//

class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        unordered_set<char> brokenSet(brokenLetters.begin(), brokenLetters.end());
        int count = 0;
        stringstream ss(text);
        string word;

        while (ss >> word) {
            bool canType = true;
            for (char c : word) {
                if (brokenSet.count(c)) {
                    canType = false;
                    break;
                }
            }
            if (canType) {
                count++;
            }
        }

        return count;           
    }
};
