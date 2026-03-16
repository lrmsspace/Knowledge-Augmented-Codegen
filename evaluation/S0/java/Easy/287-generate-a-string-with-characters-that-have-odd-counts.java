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
    public String generateTheString(int n) {
        StringBuilder sb = new StringBuilder();
        char ch = 'a';
        if (n % 2 == 0) {
            for (int i = 0; i < n - 1; i++) {
                sb.append(ch);
            }
            sb.append((char)(ch + 1));
        } else {
            for (int i = 0; i < n; i++) {
                sb.append(ch);
            }
        }
        return sb.toString();           
    }
}
