// Source: https://leetcode.com/problems/thousand-separator/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, add a dot (".") as the thousands separator and return it in string format.
//
// Example:
// Input: n = 987
// Output: "987"
//
// Constraints:
// 0 <= n <= 231 - 1
//

class Solution {
public:
    string thousandSeparator(int n) {
        string num = to_string(n);
        int len = num.length();
        if (len <= 3) return num;

        string result;
        int count = 0;
        for (int i = len - 1; i >= 0; --i) {
            result.push_back(num[i]);
            count++;
            if (count == 3 && i != 0) {
                result.push_back('.');
                count = 0;
            }
        }
        reverse(result.begin(), result.end());
        return result;          
    }
};
