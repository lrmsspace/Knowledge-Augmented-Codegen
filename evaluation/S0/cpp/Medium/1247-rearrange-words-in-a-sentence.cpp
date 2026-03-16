// Source: https://leetcode.com/problems/rearrange-words-in-a-sentence/   |   Difficulty: Medium
//
// Problem Description:
// Given a sentence text (A sentence is a string of space-separated words) in the following format:
//
//
// 	First letter is in upper case.
// 	Each word in text are separated by a single space.
//
//
// Your task is to rearrange the words in text such that all words are rearranged in an increasing order of their lengths. If two words have the same length, arrange them in their original order.
//
// Return the new text following the format shown above.
//
// Example:
// Input: text = "Leetcode is cool"
// Output: "Is cool leetcode"
// Explanation: There are 3 words, "Leetcode" of length 8, "is" of length 2 and "cool" of length 4.
// Output is ordered by length and the new first word starts with capital letter.
//
// Constraints:
// text begins with a capital letter and then contains lowercase letters and single space between words.
// 	1 <= text.length <= 10^5
//

class Solution {
public:
    string arrangeWords(string text) {
        vector<string> words;
        string word;
        for (char c : text) {
            if (c == ' ') {
                words.push_back(word);
                word.clear();
            } else {
                word += tolower(c);
            }
        }
        words.push_back(word);

        stable_sort(words.begin(), words.end(), [](const string& a, const string& b) {
            return a.length() < b.length();
        });

        string result;
        for (const string& w : words) {
            result += w + " ";
        }
        result[0] = toupper(result[0]);
        result.pop_back(); // Remove trailing space

        return result;          
    }
};
