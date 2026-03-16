// Source: https://leetcode.com/problems/three-equal-parts/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array arr which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.
//
// If it is possible, return any [i, j] with i + 1 < j, such that:
//
//
// 	arr[0], arr[1], ..., arr[i] is the first part,
// 	arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
// 	arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
// 	All three parts have equal binary values.
//
//
// If it is not possible, return [-1, -1].
//
// Note that the entire part is used when considering what binary value it represents. For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.
//
// Example:
// Input: arr = [1,0,1,0,1]
// Output: [0,3]
//
// Constraints:
// 3 <= arr.length <= 3 * 104
// 	arr[i] is 0 or 1
//

/**
 * @param {number[]} arr
 * @return {number[]}
 */
var threeEqualParts = function(arr) {
    const n = arr.length;
    const totalOnes = arr.reduce((sum, num) => sum + num, 0);
    if (totalOnes % 3 !== 0) {
        return [-1, -1];
    }
    if (totalOnes === 0) {
        return [0, n - 1];
    }
    const onesPerPart = totalOnes / 3;
    let firstPartEnd = -1;
    let secondPartStart = -1;
    let secondPartEnd = -1;
    let thirdPartStart = -1;
    let countOnes = 0;
    for (let i = 0; i < n; i++) {
        if (arr[i] === 1) {
            countOnes++;
            if (countOnes === 1) {
                firstPartEnd = i;
            } else if (countOnes === onesPerPart + 1) {
                secondPartStart = i;
            } else if (countOnes === 2 * onesPerPart + 1) {
                thirdPartStart = i;
            }
        }
    }
    const partLength = n - thirdPartStart;
    if (firstPartEnd + partLength > secondPartStart || secondPartStart + partLength > thirdPartStart) {
        return [-1, -1];
    }
    for (let i = 0; i < partLength; i++) {
        if (arr[firstPartEnd + i] !== arr[secondPartStart + i] || arr[secondPartStart + i] !== arr[thirdPartStart + i]) {
            return [-1, -1];
        }
    }
    return [firstPartEnd + partLength - 1, secondPartStart + partLength];   
};
