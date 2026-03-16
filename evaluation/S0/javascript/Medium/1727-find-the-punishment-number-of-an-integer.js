// Source: https://leetcode.com/problems/find-the-punishment-number-of-an-integer/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, return the punishment number of n.
//
// The punishment number of n is defined as the sum of the squares of all integers i such that:
//
//
// 	1 <= i <= n
// 	The decimal representation of i * i can be partitioned into contiguous substrings such that the sum of the integer values of these substrings equals i.
//
// Example:
// Input: n = 10
// Output: 182
// Explanation: There are exactly 3 integers i in the range [1, 10] that satisfy the conditions in the statement:
// - 1 since 1 * 1 = 1
// - 9 since 9 * 9 = 81 and 81 can be partitioned into 8 and 1 with a sum equal to 8 + 1 == 9.
// - 10 since 10 * 10 = 100 and 100 can be partitioned into 10 and 0 with a sum equal to 10 + 0 == 10.
// Hence, the punishment number of 10 is 1 + 81 + 100 = 182
//
// Constraints:
// 1 <= n <= 1000
//

/**
 * @param {number} n
 * @return {number}
 */
var punishmentNumber = function(n) {
    let punishmentSum = 0;
        
    const canPartition = (numStr, targetSum, startIndex) => {
        if (targetSum === 0 && startIndex === numStr.length) {
            return true;
        }
        if (targetSum < 0 || startIndex >= numStr.length) {
            return false;
        }
        for (let endIndex = startIndex + 1; endIndex <= numStr.length; endIndex++) {
            const substring = numStr.slice(startIndex, endIndex);
            const substringValue = parseInt(substring, 10);
            if (canPartition(numStr, targetSum - substringValue, endIndex)) {
                return true;
            }
        }
        return false;
    }
    for (let i = 1; i <= n; i++) {
        const square = i * i;
        const squareStr = square.toString();
        if (canPartition(squareStr, i, 0)) {
            punishmentSum += square;
        }
    }
    return punishmentSum;   
            
};
