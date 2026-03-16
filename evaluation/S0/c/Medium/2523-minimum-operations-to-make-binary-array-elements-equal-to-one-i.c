// Source: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// You can do the following operation on the array any number of times (possibly zero):
//
//
// 	Choose any 3 consecutive elements from the array and flip all of them.
//
//
// Flipping an element means changing its value from 0 to 1, and from 1 to 0.
//
// Return the minimum number of operations required to make all elements in nums equal to 1. If it is impossible, return -1.
//
// Example:
// Input: nums = [0,1,1,1,0,0]
//
// Output: 3
//
// Explanation:
// We can do the following operations:
//
//
// 	Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
// 	Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
// 	Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//

int minOperations(int* nums, int numsSize) {
    int total_zeros = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            total_zeros++;
        }
    }

    // If there are no zeros, no operations are needed
    if (total_zeros == 0) {
        return 0;
    }

    // If the number of zeros is odd, it's impossible to make all elements equal to 1
    if (total_zeros % 2 != 0) {
        return -1;
    }

    int operations = 0;
    for (int i = 0; i < numsSize - 2; i++) {
        if (nums[i] == 0) {
            // Perform the flip operation on nums[i], nums[i+1], nums[i+2]
            nums[i] = 1 - nums[i];
            nums[i + 1] = 1 - nums[i + 1];
            nums[i + 2] = 1 - nums[i + 2];
            operations++;
        }
    }

    // After processing, check if all elements are equal to 1
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            return -1;
        }
    }

    return operations;      
}
