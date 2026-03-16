// Source: https://leetcode.com/problems/distinct-echo-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
//
// Example:
// Input: text = "abcabcabc"
// Output: 3
// Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
//
// Constraints:
// 1 <= text.length <= 2000
// 	text has only lowercase English letters.
//

class Solution {
public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        unordered_set<string> echoSubstrings;
        
        for (int length = 1; length <= n / 2; ++length) {
            for (int start = 0; start <= n - 2 * length; ++start) {
                if (text.substr(start, length) == text.substr(start + length, length)) {
                    echoSubstrings.insert(text.substr(start, 2 * length));
                }
            }
        }
        
        return echoSubstrings.size();           
    }
};
