// Source: https://leetcode.com/problems/monotone-increasing-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer has monotone increasing digits if and only if each pair of adjacent digits x and y satisfy x <= y.
//
// Given an integer n, return the largest number that is less than or equal to n with monotone increasing digits.
//
// Example:
// Input: n = 10
// Output: 9
//
// Constraints:
// 0 <= n <= 109
//

class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string s = to_string(n);
        int mark = s.size();
        for (int i = s.size() - 1; i > 0; --i) {
            if (s[i] < s[i - 1]) {
                mark = i;
                s[i - 1]--;
            }
        }
        for (int i = mark; i < s.size(); ++i) {
            s[i] = '9';
        }
        return stoi(s);         
    }
};
