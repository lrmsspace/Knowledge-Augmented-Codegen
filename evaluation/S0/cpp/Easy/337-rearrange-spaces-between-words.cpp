// Source: https://leetcode.com/problems/rearrange-spaces-between-words/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string text of words that are placed among some number of spaces. Each word consists of one or more lowercase English letters and are separated by at least one space. It's guaranteed that text contains at least one word.
//
// Rearrange the spaces so that there is an equal number of spaces between every pair of adjacent words and that number is maximized. If you cannot redistribute all the spaces equally, place the extra spaces at the end, meaning the returned string should be the same length as text.
//
// Return the string after rearranging the spaces.
//
// Example:
// Input: text = "  this   is  a sentence "
// Output: "this   is   a   sentence"
// Explanation: There are a total of 9 spaces and 4 words. We can evenly divide the 9 spaces between the words: 9 / (4-1) = 3 spaces.
//
// Constraints:
// 1 <= text.length <= 100
// 	text consists of lowercase English letters and ' '.
// 	text contains at least one word.
//

class Solution {
public:
    string reorderSpaces(string text) {
        int spaceCount = 0;
        vector<string> words;
        string currentWord;

        for (char c : text) {
            if (c == ' ') {
                if (!currentWord.empty()) {
                    words.push_back(currentWord);
                    currentWord.clear();
                }
                spaceCount++;
            } else {
                currentWord += c;
            }
        }
        if (!currentWord.empty()) {
            words.push_back(currentWord);
        }

        int wordCount = words.size();
        string result;

        if (wordCount == 1) {
            result = words[0] + string(spaceCount, ' ');
        } else {
            int spacesBetweenWords = spaceCount / (wordCount - 1);
            int extraSpaces = spaceCount % (wordCount - 1);

            for (int i = 0; i < wordCount; ++i) {
                result += words[i];
                if (i < wordCount - 1) {
                    result += string(spacesBetweenWords, ' ');
                }
            }
            result += string(extraSpaces, ' ');
        }

        return result;          
    }
};
