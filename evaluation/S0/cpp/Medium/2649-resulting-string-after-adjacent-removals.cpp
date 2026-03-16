// Source: https://leetcode.com/problems/resulting-string-after-adjacent-removals/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s consisting of lowercase English letters.
//
// You must repeatedly perform the following operation while the string s has at least two consecutive characters:
//
//
// 	Remove the leftmost pair of adjacent characters in the string that are consecutive in the alphabet, in either order (e.g., 'a' and 'b', or 'b' and 'a').
// 	Shift the remaining characters to the left to fill the gap.
//
//
// Return the resulting string after no more operations can be performed.
//
// Note: Consider the alphabet as circular, thus 'a' and 'z' are consecutive.
//
// Example:
// Input: s = "abc"
//
// Output: "c"
//
// Explanation:
//
//
// 	Remove "ab" from the string, leaving "c" as the remaining string.
// 	No further operations are possible. Thus, the resulting string after all possible removals is "c".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    string resultingString(string s) {
        string stack;
        for (char c : s) {
            if (!stack.empty() && abs(stack.back() - c) == 1) {
                stack.pop_back();
            } else {
                stack.push_back(c);
            }
        }
        return stack;           
    }
};
