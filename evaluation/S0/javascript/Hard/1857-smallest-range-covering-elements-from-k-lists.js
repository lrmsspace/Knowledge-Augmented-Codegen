// Source: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/   |   Difficulty: Hard
//
// Problem Description:
// You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
//
// We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.
//
// Example:
// Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
// Output: [20,24]
// Explanation: 
// List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
// List 2: [0, 9, 12, 20], 20 is in range [20,24].
// List 3: [5, 18, 22, 30], 22 is in range [20,24].
//
// Constraints:
// nums.length == k
// 	1 <= k <= 3500
// 	1 <= nums[i].length <= 50
// 	-105 <= nums[i][j] <= 105
// 	nums[i] is sorted in non-decreasing order.
//

/**
 * @param {number[][]} nums
 * @return {number[]}
 */
var smallestRange = function(nums) {
    

    const minHeap = new MinPriorityQueue();
    let max = -Infinity;
    for (let i = 0; i < nums.length; i++) {
        minHeap.enqueue([i, 0], nums[i][0]);
        max = Math.max(max, nums[i][0]);
    }

    let rangeStart = 0, rangeEnd = Infinity;
    while (minHeap.size() === nums.length) {
        const [listIndex, elementIndex] = minHeap.dequeue().element;
        const currentMin = nums[listIndex][elementIndex];
        if (max - currentMin < rangeEnd - rangeStart || (max - currentMin === rangeEnd - rangeStart && currentMin < rangeStart)) {
            rangeStart = currentMin;
            rangeEnd = max;
        }
        if (elementIndex + 1 < nums[listIndex].length) {
            minHeap.enqueue([listIndex, elementIndex + 1], nums[listIndex][elementIndex + 1]);
            max = Math.max(max, nums[listIndex][elementIndex + 1]);
        }
    }
    return [rangeStart, rangeEnd];
    
};
