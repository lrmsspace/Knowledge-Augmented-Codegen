// Source: https://leetcode.com/problems/maximum-gap/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the maximum difference between two successive elements in its sorted form. If the array contains less than two elements, return 0.
//
// You must write an algorithm that runs in linear time and uses linear extra space.
//
// Example:
// Input: nums = [3,6,9,1]
// Output: 3
// Explanation: The sorted form of the array is [1,3,6,9], either (3,6) or (6,9) has the maximum difference 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var maximumGap = function(nums) {
    


    if (nums.length < 2) return 0;

    const min = Math.min(...nums);
    const max = Math.max(...nums);
    const bucketSize = Math.max(1, Math.floor((max - min) / (nums.length - 1)));
    const bucketCount = Math.floor((max - min) / bucketSize) + 1;
    const buckets = Array.from({ length: bucketCount }, () => ({ min: Infinity, max: -Infinity }));
    for (const num of nums) {
        const bucketIndex = Math.floor((num - min) / bucketSize);
        buckets[bucketIndex].min = Math.min(buckets[bucketIndex].min, num);
        buckets[bucketIndex].max = Math.max(buckets[bucketIndex].max, num);
    }

    let maxGap = 0;
    let previousMax = min;
    for (const bucket of buckets) {
        if (bucket.min === Infinity) continue;
        maxGap = Math.max(maxGap, bucket.min - previousMax);
        previousMax = bucket.max;
    }
    return maxGap;
    
};
