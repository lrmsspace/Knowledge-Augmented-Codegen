// Source: https://leetcode.com/problems/report-spam-message/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings message and an array of strings bannedWords.
//
// An array of words is considered spam if there are at least two words in it that exactly match any word in bannedWords.
//
// Return true if the array message is spam, and false otherwise.
//
// Example:
// Input: message = ["hello","world","leetcode"], bannedWords = ["world","hello"]
//
// Output: true
//
// Explanation:
//
// The words "hello" and "world" from the message array both appear in the bannedWords array.
//
// Constraints:
// 1 <= message.length, bannedWords.length <= 105
// 	1 <= message[i].length, bannedWords[i].length <= 15
// 	message[i] and bannedWords[i] consist only of lowercase English letters.
//

class Solution {
public:
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
        unordered_set<string> bannedSet(bannedWords.begin(), bannedWords.end());
        int count = 0;
        for (const string& word : message) {
            if (bannedSet.count(word)) {
                count++;
                if (count >= 2) {
                    return true;
                }
            }
        }
        return false;           
    }
};
