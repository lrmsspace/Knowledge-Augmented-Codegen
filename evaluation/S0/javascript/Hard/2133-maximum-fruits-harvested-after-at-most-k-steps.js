// Source: https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/   |   Difficulty: Hard
//
// Problem Description:
// Fruits are available at some positions on an infinite x-axis. You are given a 2D integer array fruits where fruits[i] = [positioni, amounti] depicts amounti fruits at the position positioni. fruits is already sorted by positioni in ascending order, and each positioni is unique.
//
// You are also given an integer startPos and an integer k. Initially, you are at the position startPos. From any position, you can either walk to the left or right. It takes one step to move one unit on the x-axis, and you can walk at most k steps in total. For every position you reach, you harvest all the fruits at that position, and the fruits will disappear from that position.
//
// Return the maximum total number of fruits you can harvest.
//
// Example:
// Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
// Output: 9
// Explanation: 
// The optimal way is to:
// - Move right to position 6 and harvest 3 fruits
// - Move right to position 8 and harvest 6 fruits
// You moved 3 steps and harvested 3 + 6 = 9 fruits in total.
//
// Constraints:
// 1 <= fruits.length <= 105
// 	fruits[i].length == 2
// 	0 <= startPos, positioni <= 2 * 105
// 	positioni-1 < positioni for any i > 0 (0-indexed)
// 	1 <= amounti <= 104
// 	0 <= k <= 2 * 105
//

/**
 * @param {number[][]} fruits
 * @param {number} startPos
 * @param {number} k
 * @return {number}
 */
var maxTotalFruits = function(fruits, startPos, k) {
    const n = fruits.length;
    const prefixSums = new Array(n).fill(0);
    prefixSums[0] = fruits[0][1];
    for (let i = 1; i < n; i++) {
        prefixSums[i] = prefixSums[i - 1] + fruits[i][1];
    }
    const getSum = (left, right) => {
        if (left > right) {
            return 0;
        }
        return prefixSums[right] - (left > 0 ? prefixSums[left - 1] : 0);
    }
    let maxFruits = 0;
    for (let leftSteps = 0; leftSteps <= k; leftSteps++) {  
        const rightSteps = k - 2 * leftSteps;
        const leftPos = startPos - leftSteps;
        const rightPos = startPos + rightSteps;
        const leftIndex = binarySearch(fruits, leftPos);
        const rightIndex = binarySearch(fruits, rightPos);
        maxFruits = Math.max(maxFruits, getSum(leftIndex, rightIndex));
    }
    for (let rightSteps = 0; rightSteps <= k; rightSteps++) {
        const leftSteps = k - 2 * rightSteps;
        const leftPos = startPos - leftSteps;
        const rightPos = startPos + rightSteps;
        const leftIndex = binarySearch(fruits, leftPos);
        const rightIndex = binarySearch(fruits, rightPos);
        maxFruits = Math.max(maxFruits, getSum(leftIndex, rightIndex));
    }
    return maxFruits;
};
