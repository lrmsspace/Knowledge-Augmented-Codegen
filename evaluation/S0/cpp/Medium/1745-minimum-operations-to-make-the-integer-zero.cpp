// Source: https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers num1 and num2.
//
// In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.
//
// Return the integer denoting the minimum number of operations needed to make num1 equal to 0.
//
// If it is impossible to make num1 equal to 0, return -1.
//
// Example:
// Input: num1 = 3, num2 = -2
// Output: 3
// Explanation: We can make 3 equal to 0 with the following operations:
// - We choose i = 2 and subtract 22 + (-2) from 3, 3 - (4 + (-2)) = 1.
// - We choose i = 2 and subtract 22 + (-2) from 1, 1 - (4 + (-2)) = -1.
// - We choose i = 0 and subtract 20 + (-2) from -1, (-1) - (1 + (-2)) = 0.
// It can be proven, that 3 is the minimum number of operations that we need to perform.
//
// Constraints:
// 1 <= num1 <= 109
//  -109 <= num2 <= 109
//

class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        int operations = 0;
        while (num1 > 0) {
            long long powerValue = (1LL << operations) + num2;
            if (powerValue <= 0) {
                operations++;
                continue;
            }
            num1 -= powerValue;
            operations++;
        }
        if (num1 < 0) return -1;
        int bitsNeeded = __builtin_popcount(num1);
        return bitsNeeded <= operations ? bitsNeeded : -1;          
    }
};
