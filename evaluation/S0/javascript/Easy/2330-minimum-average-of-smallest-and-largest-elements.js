// Source: https://leetcode.com/problems/minimum-average-of-smallest-and-largest-elements/   |   Difficulty: Easy
//
// Problem Description:
// You have an array of floating point numbers averages which is initially empty. You are given an array nums of n integers where n is even.
//
// You repeat the following procedure n / 2 times:
//
//
// 	Remove the smallest element, minElement, and the largest element maxElement, from nums.
// 	Add (minElement + maxElement) / 2 to averages.
//
//
// Return the minimum element in averages.
//
// Example:
// Input: nums = [7,8,3,4,15,13,4,1]
//
// Output: 5.5
//
// Explanation:
//
//
// 	
// 		
// 			step
// 			nums
// 			averages
// 		
// 		
// 			0
// 			[7,8,3,4,15,13,4,1]
// 			[]
// 		
// 		
// 			1
// 			[7,8,3,4,13,4]
// 			[8]
// 		
// 		
// 			2
// 			[7,8,4,4]
// 			[8,8]
// 		
// 		
// 			3
// 			[7,4]
// 			[8,8,6]
// 		
// 		
// 			4
// 			[]
// 			[8,8,6,5.5]
// 		
// 	
//
// The smallest element of averages, 5.5, is returned.
//
// Constraints:
// 2 <= n == nums.length <= 50
// 	n is even.
// 	1 <= nums[i] <= 50
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumAverage = function(nums) {
    nums.sort((a, b) => a - b);
    const n = nums.length;
    let minAverage = Infinity;
    for (let i = 0; i < n / 2; i++) {
        const average = (nums[i] + nums[n - 1 - i]) / 2;
        minAverage = Math.min(minAverage, average);
    }
    return minAverage;
};
