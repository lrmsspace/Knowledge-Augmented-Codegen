// Source: https://leetcode.com/problems/reverse-words-in-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given an input string s, reverse the order of the words.
//
// A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
//
// Return a string of the words in reverse order concatenated by a single space.
//
// Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.
//
// Example:
// Input: s = "the sky is blue"
// Output: "blue is sky the"
//
// Constraints:
// 1 <= s.length <= 104
// 	s contains English letters (upper-case and lower-case), digits, and spaces ' '.
// 	There is at least one word in s.
//
//
//  
// Follow-up: If the string data type is mutable in your language, can you solve it in-place with O(1) extra space?
//

class Solution {
public:
    string reverseWords(string s) {
        // Remove leading spaces
        int left = 0;
        while (left < s.size() && s[left] == ' ') {
            left++;
        }

        // Remove trailing spaces
        int right = s.size() - 1;
        while (right >= 0 && s[right] == ' ') {
            right--;
        }

        deque<string> words;
        string word;

        while (left <= right) {
            char c = s[left];

            if (c == ' ') {
                if (!word.empty()) {
                    words.push_front(word);
                    word.clear();
                }
            } else {
                word += c;
            }
            left++;
        }

        // Add the last word if exists
        if (!word.empty()) {
            words.push_front(word);
        }

        // Join words with a single space
        string result;
        for (const string& w : words) {
            if (!result.empty()) {
                result += ' ';
            }
            result += w;
        }

        return result;          
    }
};
