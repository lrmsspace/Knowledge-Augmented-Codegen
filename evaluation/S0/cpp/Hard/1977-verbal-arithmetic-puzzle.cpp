// Source: https://leetcode.com/problems/verbal-arithmetic-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// Given an equation, represented by words on the left side and the result on the right side.
//
// You need to check if the equation is solvable under the following rules:
//
//
// 	Each character is decoded as one digit (0 - 9).
// 	No two characters can map to the same digit.
// 	Each words[i] and result are decoded as one number without leading zeros.
// 	Sum of numbers on the left side (words) will equal to the number on the right side (result).
//
//
// Return true if the equation is solvable, otherwise return false.
//
// Example:
// Input: words = ["SEND","MORE"], result = "MONEY"
// Output: true
// Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
// Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
//
// Constraints:
// 2 <= words.length <= 5
// 	1 <= words[i].length, result.length <= 7
// 	words[i], result contain only uppercase English letters.
// 	The number of different characters used in the expression is at most 10.
//

class Solution {
public:
    bool isSolvable(vector<string>& words, string result) {
        unordered_map<char, int> charToIndex;
        vector<int> charCount(10, 0);
        vector<bool> leadingChar(10, false);
        int index = 0;

        for (const string& word : words) {
            int len = word.length();
            for (int i = 0; i < len; ++i) {
                char c = word[i];
                if (charToIndex.find(c) == charToIndex.end()) {
                    charToIndex[c] = index++;
                }
                charCount[charToIndex[c]] += pow(10, len - i - 1);
                if (i == 0 && len > 1) {
                    leadingChar[charToIndex[c]] = true;
                }
            }
        }

        int len = result.length();
        for (int i = 0; i < len; ++i) {
            char c = result[i];
            if (charToIndex.find(c) == charToIndex.end()) {
                charToIndex[c] = index++;
            }
            charCount[charToIndex[c]] -= pow(10, len - i - 1);
            if (i == 0 && len > 1) {
                leadingChar[charToIndex[c]] = true;
            }
        }

        vector<int> counts;
        vector<bool> isLeading;
        for (int i = 0; i < index; ++i) {
            counts.push_back(charCount[i]);
            isLeading.push_back(leadingChar[i]);
        }

        vector<bool> used(10, false);
        return backtrack(counts, isLeading, used, 0);           
    }
};
