// Source: https://leetcode.com/problems/contiguous-array/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
//
// Example:
// Input: nums = [0,1]
// Output: 2
// Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

int findMaxLength(int* nums, int numsSize) {
    int maxLength = 0;
    int count = 0;
    // Create a hash map to store the first occurrence of each count
    // Using an array to simulate the hash map for counts ranging from -numsSize to numsSize
    int hashMapSize = 2 * numsSize + 1;
    int* hashMap = (int*)malloc(hashMapSize * sizeof(int));
    for (int i = 0; i < hashMapSize; i++) {
        hashMap[i] = -2; // Initialize with -2 to indicate unvisited
    }
    hashMap[numsSize] = -1; // Base case: count 0 at index -1

    for (int i = 0; i < numsSize; i++) {
        count += (nums[i] == 1) ? 1 : -1;

        if (hashMap[count + numsSize] != -2) {
            // If this count has been seen before, calculate the length of the subarray
            int length = i - hashMap[count + numsSize];
            if (length > maxLength) {
                maxLength = length;
            }
        } else {
            // Store the first occurrence of this count
            hashMap[count + numsSize] = i;
        }
    }

    free(hashMap);
    return maxLength;       
}
