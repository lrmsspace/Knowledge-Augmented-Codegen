// Source: https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, return the minimum number of character swaps to make it alternating, or -1 if it is impossible.
//
// The string is called alternating if no two adjacent characters are equal. For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
//
// Any two characters may be swapped, even if they are not adjacent.
//
// Example:
// Input: s = "111000"
// Output: 1
// Explanation: Swap positions 1 and 4: "111000" -> "101010"
// The string is now alternating.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
//

/**
 * @param {string} s
 * @return {number}
 */
var minSwaps = function(s) {
    const count0 = [...s].filter(c => c === '0').length;
    const count1 = s.length - count0;
    if (Math.abs(count0 - count1) > 1) {
        return -1;
    }
    const swapsForPattern = (startChar) => {
        let swaps = 0;
        for (let i = 0; i < s.length; i++) {
            const expectedChar = (i % 2 === 0) ? startChar : (startChar === '0' ? '1' : '0');
            if (s[i] !== expectedChar) {
                swaps++;
            }
        }
        return swaps / 2;
    }
    if (count0 > count1) {
        return swapsForPattern('0');
    }
    else if (count1 > count0) {
        return swapsForPattern('1');
    }
    else {
        return Math.min(swapsForPattern('0'), swapsForPattern('1'));
    }
        
};
