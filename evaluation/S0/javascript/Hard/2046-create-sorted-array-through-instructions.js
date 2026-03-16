// Source: https://leetcode.com/problems/create-sorted-array-through-instructions/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array instructions, you are asked to create a sorted array from the elements in instructions. You start with an empty container nums. For each element from left to right in instructions, insert it into nums. The cost of each insertion is the minimum of the following:
//
//
// 	The number of elements currently in nums that are strictly less than instructions[i].
// 	The number of elements currently in nums that are strictly greater than instructions[i].
//
//
// For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1) (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].
//
// Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 109 + 7
//
// Example:
// Input: instructions = [1,5,6,2]
// Output: 1
// Explanation: Begin with nums = [].
// Insert 1 with cost min(0, 0) = 0, now nums = [1].
// Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
// Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
// Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
// The total cost is 0 + 0 + 0 + 1 = 1.
//
// Constraints:
// 1 <= instructions.length <= 105
// 	1 <= instructions[i] <= 105
//

/**
 * @param {number[]} instructions
 * @return {number}
 */
var createSortedArray = function(instructions) {
    const MOD = 1e9 + 7;
    const maxVal = Math.max(...instructions);
    const fenwickTree = new Array(maxVal + 1).fill(0);
    const update = (index) => {
        while (index <= maxVal) {
            fenwickTree[index] += 1;
            index += index & -index;
        }
    };
    const query = (index) => {
        let sum = 0;
        while (index > 0) {
            sum += fenwickTree[index];
            index -= index & -index;
        }
        return sum;
    };
    let cost = 0;
    for (let i = 0; i < instructions.length; i++) {
        const num = instructions[i];
        const lessCount = query(num - 1);
        const greaterCount = i - query(num);
        cost = (cost + Math.min(lessCount, greaterCount)) % MOD;
        update(num);
    }
    return cost;
};
