// Source: https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, transform string s into string t using the following operation any number of times:
//
//
// 	Choose a non-empty substring in s and sort it in place so the characters are in ascending order.
//
// 	
// 		For example, applying the operation on the underlined substring in "14234" results in "12344".
// 	
// 	
//
//
// Return true if it is possible to transform s into t. Otherwise, return false.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "84532", t = "34852"
// Output: true
// Explanation: You can transform s into t using the following sort operations:
// "84532" (from index 2 to 3) -> "84352"
// "84352" (from index 0 to 2) -> "34852"
//
// Constraints:
// s.length == t.length
// 	1 <= s.length <= 105
// 	s and t consist of only digits.
//

class Solution {
public:
    bool isTransformable(string s, string t) {
        vector<queue<int>> pos(10);
        for (int i = 0; i < s.size(); i++) {
            pos[s[i] - '0'].push(i);
        }
        
        for (char c : t) {
            int digit = c - '0';
            if (pos[digit].empty()) {
                return false;
            }
            int currPos = pos[digit].front();
            pos[digit].pop();
            
            for (int smallerDigit = 0; smallerDigit < digit; smallerDigit++) {
                if (!pos[smallerDigit].empty() && pos[smallerDigit].front() < currPos) {
                    return false;
                }
            }
        }
        
        return true;            
    }
};
