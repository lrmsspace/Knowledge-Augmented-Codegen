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

double minimumAverage(int* nums, int numsSize) {
    // Sort the array
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    // Calculate the minimum average of smallest and largest elements
    double minAverage = (nums[0] + nums[numsSize - 1]) / 2.0;

    return minAverage;      
}
