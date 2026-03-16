// Source: https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, find any substring of length 2 which is also present in the reverse of s.
//
// Return true if such a substring exists, and false otherwise.
//
// Example:
// Input: s = "leetcode"
//
// Output: true
//
// Explanation: Substring "ee" is of length 2 which is also present in reverse(s) == "edocteel".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of lowercase English letters.
//

class Solution {
public:
    bool isSubstringPresent(string s) {
        int n = s.size();
        for (int i = 0; i < n - 1; ++i) {
            string sub = s.substr(i, 2);
            string rev_sub = string(sub.rbegin(), sub.rend());
            if (s.find(rev_sub) != string::npos) {
                return true;
            }
        }
        return false;           
    }
};
