// Source: https://leetcode.com/problems/to-lower-case/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, return the string after replacing every uppercase letter with the same lowercase letter.
//
// Example:
// Input: s = "Hello"
// Output: "hello"
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of printable ASCII characters.
//

class Solution {
public:
    string toLowerCase(string s) {
        for (char &c : s) {
            if (c >= 'A' && c <= 'Z') {
                c += 32; // Convert to lowercase by adding the ASCII difference
            }
        }
        return s;           
    }
};
