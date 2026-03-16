// Source: https://leetcode.com/problems/maximum-score-from-removing-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and two integers x and y. You can perform two types of operations any number of times.
//
//
// 	Remove substring "ab" and gain x points.
//
// 	
// 		For example, when removing "ab" from "cabxbae" it becomes "cxbae".
// 	
// 	
// 	Remove substring "ba" and gain y points.
// 	
// 		For example, when removing "ba" from "cabxbae" it becomes "cabxe".
// 	
// 	
//
//
// Return the maximum points you can gain after applying the above operations on s.
//
// Example:
// Input: s = "cdbcbbaaabab", x = 4, y = 5
// Output: 19
// Explanation:
// - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
// - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
// - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
// - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
// Total score = 5 + 4 + 5 + 5 = 19.
//
// Constraints:
// 1 <= s.length <= 105
// 	1 <= x, y <= 104
// 	s consists of lowercase English letters.
//

class Solution {
public:
    int maximumGain(string s, int x, int y) {
        int totalScore = 0;
        stack<char> charStack;

        // Determine the order of removal based on points
        char firstChar = x >= y ? 'a' : 'b';
        char secondChar = x >= y ? 'b' : 'a';
        int firstPoints = max(x, y);
        int secondPoints = min(x, y);

        // First pass: remove the higher point substring
        for (char c : s) {
            if (!charStack.empty() && charStack.top() == firstChar && c == secondChar) {
                charStack.pop();
                totalScore += firstPoints;
            } else {
                charStack.push(c);
            }
        }

        // Prepare for second pass
        string remainingStr;
        while (!charStack.empty()) {
            remainingStr += charStack.top();
            charStack.pop();
        }
        reverse(remainingStr.begin(), remainingStr.end());

        // Second pass: remove the lower point substring
        for (char c : remainingStr) {
            if (!charStack.empty() && charStack.top() == secondChar && c == firstChar) {
                charStack.pop();
                totalScore += secondPoints;
            } else {
                charStack.push(c);
            }
        }

        return totalScore;          
    }
};
