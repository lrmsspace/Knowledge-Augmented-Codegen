// Source: https://leetcode.com/problems/count-special-integers/   |   Difficulty: Hard
//
// Problem Description:
// We call a positive integer special if all of its digits are distinct.
//
// Given a positive integer n, return the number of special integers that belong to the interval [1, n].
//
// Example:
// Input: n = 20
// Output: 19
// Explanation: All the integers from 1 to 20, except 11, are special. Thus, there are 19 special integers.
//
// Constraints:
// 1 <= n <= 2 * 109
//

class Solution {
public:
    int countSpecialNumbers(int n) {
        string s = to_string(n);
        int len = s.length();
        int result = 0;

        // Count special numbers with fewer digits than n
        for (int i = 1; i < len; ++i) {
            int count = 9;
            int availableDigits = 9;
            for (int j = 1; j < i; ++j) {
                count *= availableDigits;
                --availableDigits;
            }
            result += count;
        }

        // Count special numbers with the same number of digits as n
        vector<bool> used(10, false);
        for (int i = 0; i < len; ++i) {
            int digit = s[i] - '0';
            for (int d = (i == 0 ? 1 : 0); d < digit; ++d) {
                if (!used[d]) {
                    int count = 1;
                    int availableDigits = 10 - (i + 1);
                    for (int j = i + 1; j < len; ++j) {
                        count *= availableDigits;
                        --availableDigits;
                    }
                    result += count;
                }
            }
            if (used[digit]) {
                break;
            }
            used[digit] = true;
            if (i == len - 1) {
                result += 1; // Include n itself if all digits are unique
            }
        }

        return result;          
    }
};
