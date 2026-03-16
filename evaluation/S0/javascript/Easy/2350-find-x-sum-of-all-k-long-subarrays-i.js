// Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/   |   Difficulty: Easy
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
// 1 <= n == nums.length <= 50
// 	1 <= nums[i] <= 50
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
    const result = [];
    for (let i = 0; i <= n - k; i++) {
        const subarray = nums.slice(i, i + k);
        const freqMap = {};
        for (const num of subarray) {   
            freqMap[num] = (freqMap[num] || 0) + 1;
        }
        const freqArray = Object.entries(freqMap).map(([num, freq]) => [parseInt(num), freq]);
        freqArray.sort((a, b) => {
            if (b[1] === a[1]) {
                return b[0] - a[0];
            }
            return b[1] - a[1];
        });
        const topXElements = new Set(freqArray.slice(0, x).map(([num, freq]) => num));
        let xSum = 0;
        for (const num of subarray) {
            if (topXElements.has(num)) {
                xSum += num;
            }
        }
        result.push(xSum);
    }
    return result;
    
};
