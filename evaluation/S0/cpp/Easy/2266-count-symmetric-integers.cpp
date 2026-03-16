// Source: https://leetcode.com/problems/count-symmetric-integers/   |   Difficulty: Easy
//
// Problem Description:
// You are given two positive integers low and high.
//
// An integer x consisting of 2 * n digits is symmetric if the sum of the first n digits of x is equal to the sum of the last n digits of x. Numbers with an odd number of digits are never symmetric.
//
// Return the number of symmetric integers in the range [low, high].
//
// Example:
// Input: low = 1, high = 100
// Output: 9
// Explanation: There are 9 symmetric integers between 1 and 100: 11, 22, 33, 44, 55, 66, 77, 88, and 99.
//
// Constraints:
// 1 <= low <= high <= 104
//

class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        auto isSymmetric = [](int num) {
            string s = to_string(num);
            int n = s.size();
            if (n % 2 != 0) return false;
            int half = n / 2;
            int sum1 = 0, sum2 = 0;
            for (int i = 0; i < half; ++i) {
                sum1 += s[i] - '0';
                sum2 += s[i + half] - '0';
            }
            return sum1 == sum2;
        };

        int count = 0;
        for (int i = low; i <= high; ++i) {
            if (isSymmetric(i)) {
                ++count;
            }
        }
        return count;           
    }
};
