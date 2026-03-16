// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-substring-operation/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s consisting of lowercase English letters. Perform the following operation:
//
//
// 	Select any non-empty substring then replace every letter of the substring with the preceding letter of the English alphabet. For example, 'b' is converted to 'a', and 'a' is converted to 'z'.
//
//
// Return the lexicographically smallest string after performing the operation.
//
// Example:
// Input: s = "cbabc"
//
// Output: "baabc"
//
// Explanation:
//
// Perform the operation on the substring starting at index 0, and ending at index 1 inclusive.
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of lowercase English letters
//

class Solution {
public:
    string smallestString(string s) {
        int n = s.size();
        bool operationDone = false;

        for (int i = 0; i < n; ++i) {
            if (s[i] == 'a') {
                if (operationDone) {
                    break;
                }
                continue;
            } else {
                s[i] = s[i] - 1;
                operationDone = true;
            }
        }

        if (!operationDone) {
            s[n - 1] = 'z';
        }

        return s;           
    }
};
