// Source: https://leetcode.com/problems/largest-multiple-of-three/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of digits digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order. If there is no answer return an empty string.
//
// Since the answer may not fit in an integer data type, return the answer as a string. Note that the returning answer must not contain unnecessary leading zeros.
//
// Example:
// Input: digits = [8,1,9]
// Output: "981"
//
// Constraints:
// 1 <= digits.length <= 104
// 	0 <= digits[i] <= 9
//

/**
 * @param {number[]} digits
 * @return {string}
 */
var largestMultipleOfThree = function(digits) {
    const count = new Array(10).fill(0);
    let sum = 0;
    for (const digit of digits) {
        count[digit]++;
        sum += digit;
    }
    const mod = sum % 3;
    if (mod !== 0) {
        const remove = mod === 1 ? [1, 4, 7] : [2, 5, 8];
        let removed = false;
        for (const r of remove) {
            if (count[r] > 0) {
                count[r]--;
                removed = true;
                break;
            }
        }
        if (!removed) {
            const removeTwo = mod === 1 ? [2, 5, 8] : [1, 4, 7];
            let toRemove = 2;
            for (const r of removeTwo) {
                while (count[r] > 0 && toRemove > 0) {
                    count[r]--;
                    toRemove--;
                }
                if (toRemove === 0) {
                    break;
                }
            }
            if (toRemove > 0) {
                return "";
            }
        }
    }
    let result = "";
    for (let i = 9; i >= 0; i--) {
        result += i.toString().repeat(count[i]);
    }
    if (result.length === 0) {
        return "";
    }
    if (result[0] === "0") {
        return "0";
    }
    return result;
};
