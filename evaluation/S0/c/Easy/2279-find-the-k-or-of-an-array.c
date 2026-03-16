// Source: https://leetcode.com/problems/find-the-k-or-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums, and an integer k. Let's introduce K-or operation by extending the standard bitwise OR. In K-or, a bit position in the result is set to 1 if at least k numbers in nums have a 1 in that position.
//
// Return the K-or of nums.
//
// Example:
// Input: nums = [7,12,9,8,9,15], k = 4 
//
// Output: 9 
//
// Explanation: 
//
// Represent numbers in binary:
//
//
// 	
// 		
// 			Number
// 			Bit 3
// 			Bit 2
// 			Bit 1
// 			Bit 0
// 		
// 		
// 			7
// 			0
// 			1
// 			1
// 			1
// 		
// 		
// 			12
// 			1
// 			1
// 			0
// 			0
// 		
// 		
// 			9
// 			1
// 			0
// 			0
// 			1
// 		
// 		
// 			8
// 			1
// 			0
// 			0
// 			0
// 		
// 		
// 			9
// 			1
// 			0
// 			0
// 			1
// 		
// 		
// 			15
// 			1
// 			1
// 			1
// 			1
// 		
// 		
// 			Result = 9
// 			1
// 			0
// 			0
// 			1
// 		
// 	
//
//
// Bit 0 is set in 7, 9, 9, and 15. Bit 3 is set in 12, 9, 8, 9, and 15.
// Only bits 0 and 3 qualify. The result is (1001)2 = 9.
//
// Constraints:
// 1 <= nums.length <= 50
// 	0 <= nums[i] < 231
// 	1 <= k <= nums.length
//

int findKOr(int* nums, int numsSize, int k) {
    int bitCount[32] = {0};
    int result = 0;

    // Count the number of 1s in each bit position
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < 32; j++) {
            if (nums[i] & (1 << j)) {
                bitCount[j]++;
            }
        }
    }

    // Construct the result based on the counts
    for (int j = 0; j < 32; j++) {
        if (bitCount[j] >= k) {
            result |= (1 << j);
        }
    }

    return result;      
}
