// Source: https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s consisting of only the characters 'a' and 'b', return true if every 'a' appears before every 'b' in the string. Otherwise, return false.
//
// Example:
// Input: s = "aaabbb"
// Output: true
// Explanation:
// The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4, and 5.
// Hence, every 'a' appears before every 'b' and we return true.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i] is either 'a' or 'b'.
//

class Solution {
public:
    bool checkString(string s) {
        bool seen_b = false;
        for (char c : s) {
            if (c == 'b') {
                seen_b = true;
            } else if (seen_b && c == 'a') {
                return false;
            }
        }
        return true;            
    }
};
