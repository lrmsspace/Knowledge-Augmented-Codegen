// Source: https://leetcode.com/problems/largest-values-from-labels/   |   Difficulty: Medium
//
// Problem Description:
// You are given n item's value and label as two integer arrays values and labels. You are also given two integers numWanted and useLimit.
//
// Your task is to find a subset of items with the maximum sum of their values such that:
//
//
// 	The number of items is at most numWanted.
// 	The number of items with the same label is at most useLimit.
//
//
// Return the maximum sum.
//
// Example:
// Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], numWanted = 3, useLimit = 1
//
// Output: 9
//
// Explanation:
//
// The subset chosen is the first, third, and fifth items with the sum of values 5 + 3 + 1.
//
// Constraints:
// n == values.length == labels.length
// 	1 <= n <= 2 * 104
// 	0 <= values[i], labels[i] <= 2 * 104
// 	1 <= numWanted, useLimit <= n
//

/**
 * @param {number[]} values
 * @param {number[]} labels
 * @param {number} numWanted
 * @param {number} useLimit
 * @return {number}
 */
var largestValsFromLabels = function(values, labels, numWanted, useLimit) {
    const items = values.map((value, index) => ({ value, label: labels[index] }));
    items.sort((a, b) => b.value - a.value);
    const labelCount = new Map();
    let totalValue = 0;
    let itemsChosen = 0;
    for (const item of items) {
        const count = labelCount.get(item.label) || 0;
        if (count < useLimit) {
            totalValue += item.value;
            labelCount.set(item.label, count + 1);
            itemsChosen += 1;
            if (itemsChosen === numWanted) {
                break;
            }
        }
    }
    return totalValue;
        
};
