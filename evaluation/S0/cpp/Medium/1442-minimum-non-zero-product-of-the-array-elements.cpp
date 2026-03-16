// Source: https://leetcode.com/problems/minimum-non-zero-product-of-the-array-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer p. Consider an array nums (1-indexed) that consists of the integers in the inclusive range [1, 2p - 1] in their binary representations. You are allowed to do the following operation any number of times:
//
//
// 	Choose two elements x and y from nums.
// 	Choose a bit in x and swap it with its corresponding bit in y. Corresponding bit refers to the bit that is in the same position in the other integer.
//
//
// For example, if x = 1101 and y = 0011, after swapping the 2nd bit from the right, we have x = 1111 and y = 0001.
//
// Find the minimum non-zero product of nums after performing the above operation any number of times. Return this product modulo 109 + 7.
//
// Note: The answer should be the minimum product before the modulo operation is done.
//
// Example:
// Input: p = 1
// Output: 1
// Explanation: nums = [1].
// There is only one element, so the product equals that element.
//
// Constraints:
// 1 <= p <= 60
//

class Solution {
public:
    int minNonZeroProduct(int p) {
        const long long MOD = 1e9 + 7;
        long long maxNum = (1LL << p) - 1;
        long long secondMaxNum = maxNum - 1;
        long long count = (maxNum - 1) / 2;

        // Fast exponentiation
        long long power = 1;
        long long base = secondMaxNum % MOD;
        while (count > 0) {
            if (count & 1) {
                power = (power * base) % MOD;
            }
            base = (base * base) % MOD;
            count >>= 1;
        }

        return (power * (maxNum % MOD)) % MOD;          
    }
};
