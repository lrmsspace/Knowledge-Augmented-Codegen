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

/**
 * @param {number} num1
 * @param {number} num2
 * @return {number}
 */
var minimizeXor = function(num1, num2) {
    const countSetBits = (num) => {
        let count = 0;
        while (num > 0) {
            count += num & 1;
            num >>= 1;
        }
        return count;
    };

    const setBitsNum2 = countSetBits(num2);
    let result = 0;
    let setBitsCount = 0;

    for (let i = 31; i >= 0; i--) {
        if ((num1 & (1 << i)) !== 0) {
            if (setBitsCount < setBitsNum2) {
                result |= (1 << i);
                setBitsCount++;
            }
        }
    }

    for (let i = 0; i < 32 && setBitsCount < setBitsNum2; i++) {
        if ((result & (1 << i)) === 0) {
            result |= (1 << i);
            setBitsCount++;
        }
    }

    return result;
};