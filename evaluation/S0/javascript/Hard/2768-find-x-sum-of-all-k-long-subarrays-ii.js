// Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers and two integers k and x.
//
// The x-sum of an array is calculated by the following procedure:
//
//
// 	Count the occurrences of all elements in the array.
// 	Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
// 	Calculate the sum of the resulting array.
//
//
// Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
//
// Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].
//
// Example:
// Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
//
// Output: [6,10,12]
//
// Explanation:
//
//
// 	For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
// 	For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
// 	For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.
//
// Constraints:
// nums.length == n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 109
// 	1 <= x <= k <= nums.length
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @param {number} x
 * @return {number[]}
 */
var findXSum = function(nums, k, x) {
    const n = nums.length;  
    const freqMap = new Map();
    const freqCount = new Map();
    let currentSum = 0;
    const result = [];                  
    const addFreq = (num) => {
        const oldFreq = freqMap.get(num) || 0;
        const newFreq = oldFreq + 1;
        freqMap.set(num, newFreq);
        if (oldFreq > 0) {
            const oldSet = freqCount.get(oldFreq);
            oldSet.delete(num);
            if (oldSet.size === 0) {
                freqCount.delete(oldFreq);
            }
        }
        if (!freqCount.has(newFreq)) {
            freqCount.set(newFreq, new Set());
        }
        freqCount.get(newFreq).add(num);
        if (newFreq <= x) {
            currentSum += num;
        } else {
            const maxFreq = Math.max(...freqCount.keys());
            if (newFreq > maxFreq) {
                const maxSet = freqCount.get(maxFreq);
                const toRemove = Math.min(...maxSet);
                currentSum -= toRemove;
                maxSet.delete(toRemove);
                if (maxSet.size === 0) {
                    freqCount.delete(maxFreq);
                }
                currentSum += num;
            }
        }
    }
    const removeFreq = (num) => {
        const oldFreq = freqMap.get(num);
        const newFreq = oldFreq - 1;
        freqMap.set(num, newFreq);
        const oldSet = freqCount.get(oldFreq);
        oldSet.delete(num);
        if (oldSet.size === 0) {
            freqCount.delete(oldFreq);
        }
        if (newFreq > 0) {
            if (!freqCount.has(newFreq)) {
                freqCount.set(newFreq, new Set());
            }
            freqCount.get(newFreq).add(num);
        }
        if (oldFreq <= x) {
            currentSum -= num;
            const maxFreq = Math.max(...freqCount.keys());
            if (maxFreq > x) {  
                const maxSet = freqCount.get(maxFreq);
                const toAdd = Math.min(...maxSet);
                currentSum += toAdd;
                maxSet.delete(toAdd);
                if (maxSet.size === 0) {
                    freqCount.delete(maxFreq);
                }
            }
        }
    }
    for (let i = 0; i < k; i++) {
        addFreq(nums[i]);
    }
    result.push(currentSum);
    for (let i = k; i < n; i++) {
        addFreq(nums[i]);
        removeFreq(nums[i - k]);
        result.push(currentSum);
    }
    return result;
};
