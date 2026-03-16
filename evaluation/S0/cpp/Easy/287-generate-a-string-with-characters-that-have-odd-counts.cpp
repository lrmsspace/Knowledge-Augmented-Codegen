// Source: https://leetcode.com/problems/generate-a-string-with-characters-that-have-odd-counts/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return a string with n characters such that each character in such string occurs an odd number of times.
//
// The returned string must contain only lowercase English letters. If there are multiples valid strings, return any of them.
//
// Example:
// Input: n = 4
// Output: "pppz"
// Explanation: "pppz" is a valid string since the character 'p' occurs three times and the character 'z' occurs once. Note that there are many other valid strings such as "ohhh" and "love".
//
// Constraints:
// 1 <= n <= 500
//

class Solution {
public:
    string generateTheString(int n) {
        string result;
        if (n % 2 == 0) {
            result.append(n - 1, 'a');
            result.push_back('b');
        } else {
            result.append(n, 'a');
        }
        return result;          
    }
};
