// Source: https://leetcode.com/problems/sum-of-two-integers/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers a and b, return the sum of the two integers without using the operators + and -.
//
// Example:
// Input: a = 1, b = 2
// Output: 3
//
// Constraints:
// -1000 <= a, b <= 1000
//

class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1; // Calculate carry bits
            a = a ^ b;               // Sum without carry
            b = carry;               // Update b to carry
        }
        return a;           
    }
};
