// Source: https://leetcode.com/problems/maximal-score-after-applying-k-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k. You have a starting score of 0.
//
// In one operation:
//
//
// 	choose an index i such that 0 <= i < nums.length,
// 	increase your score by nums[i], and
// 	replace nums[i] with ceil(nums[i] / 3).
//
//
// Return the maximum possible score you can attain after applying exactly k operations.
//
// The ceiling function ceil(val) is the least integer greater than or equal to val.
//
// Example:
// Input: nums = [10,10,10,10,10], k = 5
// Output: 50
// Explanation: Apply the operation to each array element exactly once. The final score is 10 + 10 + 10 + 10 + 10 = 50.
//
// Constraints:
// 1 <= nums.length, k <= 105
// 	1 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maxKelements = function(nums, k) {
    const maxHeap = [];

    const swap = (i, j) => {
        const temp = maxHeap[i];
        maxHeap[i] = maxHeap[j];
        maxHeap[j] = temp;
    };
    const heapifyUp = (index) => {
        let currentIndex = index;
        while (currentIndex > 0) {
            const parentIndex = Math.floor((currentIndex - 1) / 2);
            if (maxHeap[currentIndex] > maxHeap[parentIndex]) {
                swap(currentIndex, parentIndex);
                currentIndex = parentIndex;
            }
            else {
                break;
            }
        }
    }
    const heapifyDown = (index) => {
        let currentIndex = index;
        const length = maxHeap.length;
        while (true) {
            const leftChildIndex = 2 * currentIndex + 1;
            const rightChildIndex = 2 * currentIndex + 2;
            let largestIndex = currentIndex;
            if (leftChildIndex < length && maxHeap[leftChildIndex] > maxHeap[largestIndex]) {
                largestIndex = leftChildIndex;
            }
            if (rightChildIndex < length && maxHeap[rightChildIndex] > maxHeap[largestIndex]) {
                largestIndex = rightChildIndex;
            }
            if (largestIndex !== currentIndex) {
                swap(currentIndex, largestIndex);
                currentIndex = largestIndex;
            }
            else {
                break;
            }
        }
    }
    const insert = (value) => {
        maxHeap.push(value);
        heapifyUp(maxHeap.length - 1);
    }
    const extractMax = () => {
        if (maxHeap.length === 0) {
            return null;
        }
        const maxValue = maxHeap[0];
        const endValue = maxHeap.pop();
        if (maxHeap.length > 0) {
            maxHeap[0] = endValue;
            heapifyDown(0);
        }
        return maxValue;
    }   
    for (const num of nums) {
        insert(num);
    }
    let score = 0;
    for (let i = 0; i < k; i++) {
        const maxValue = extractMax();
        score += maxValue;
        const newValue = Math.ceil(maxValue / 3);
        insert(newValue);
    }
    return score;   
};
