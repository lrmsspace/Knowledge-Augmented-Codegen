// Source: https://leetcode.com/problems/minimize-xor/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers num1 and num2, find the positive integer x such that:
//
//
// 	x has the same number of set bits as num2, and
// 	The value x XOR num1 is minimal.
//
//
// Note that XOR is the bitwise XOR operation.
//
// Return the integer x. The test cases are generated such that x is uniquely determined.
//
// The number of set bits of an integer is the number of 1's in its binary representation.
//
// Example:
// Input: num1 = 3, num2 = 5
// Output: 3
// Explanation:
// The binary representations of num1 and num2 are 0011 and 0101, respectively.
// The integer 3 has the same number of set bits as num2, and the value 3 XOR 3 = 0 is minimal.
//
// Constraints:
// 1 <= num1, num2 <= 109
//

class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int count2 = __builtin_popcount(num2);
        int result = 0;

        // Set bits in result where num1 has bits set, until we reach count2
        for (int i = 31; i >= 0 && count2 > 0; --i) {
            if (num1 & (1 << i)) {
                result |= (1 << i);
                --count2;
            }
        }

        // If we still need to set more bits, set them from the least significant bit
        for (int i = 0; i <= 31 && count2 > 0; ++i) {
            if (!(result & (1 << i))) {
                result |= (1 << i);
                --count2;
            }
        }

        return result;          
    }
};
