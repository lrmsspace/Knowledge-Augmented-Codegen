// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-a-swap/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s containing only digits, return the lexicographically smallest string that can be obtained after swapping adjacent digits in s with the same parity at most once.
//
// Digits have the same parity if both are odd or both are even. For example, 5 and 9, as well as 2 and 4, have the same parity, while 6 and 9 do not.
//
// Example:
// Input: s = "45320"
//
// Output: "43520"
//
// Explanation: 
//
// s[1] == '5' and s[2] == '3' both have the same parity, and swapping them results in the lexicographically smallest string.
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists only of digits.
//

class Solution {
public:
    string getSmallestString(string s) {
        string even_digits = "", odd_digits = "";
        
        // Separate even and odd digits
        for (char c : s) {
            if ((c - '0') % 2 == 0) {
                even_digits += c;
            } else {
                odd_digits += c;
            }
        }
        
        // Sort both even and odd digits to get the smallest order
        sort(even_digits.begin(), even_digits.end());
        sort(odd_digits.begin(), odd_digits.end());
        
        string result = "";
        int even_index = 0, odd_index = 0;
        
        // Reconstruct the string by choosing from sorted even and odd digits
        for (char c : s) {
            if ((c - '0') % 2 == 0) {
                result += even_digits[even_index++];
            } else {
                result += odd_digits[odd_index++];
            }
        }
        
        return result;          
    }
};
