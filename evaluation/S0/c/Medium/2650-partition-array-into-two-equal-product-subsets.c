// Source: https://leetcode.com/problems/partition-array-into-two-equal-product-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums containing distinct positive integers and an integer target.
//
// Determine if you can partition nums into two non-empty disjoint subsets, with each element belonging to exactly one subset, such that the product of the elements in each subset is equal to target.
//
// Return true if such a partition exists and false otherwise.
// A subset of an array is a selection of elements of the array.
//
// Example:
// Input: nums = [3,1,6,8,4], target = 24
//
// Output: true
//
// Explanation: The subsets [3, 8] and [1, 6, 4] each have a product of 24. Hence, the output is true.
//
// Constraints:
// 3 <= nums.length <= 12
// 	1 <= target <= 1015
// 	1 <= nums[i] <= 100
// 	All elements of nums are distinct.
//

bool checkEqualPartitions(int* nums, int numsSize, long long target) {
    int totalSubsets = 1 << numsSize; // Total number of subsets
    for (int mask = 1; mask < totalSubsets - 1; mask++) { // Exclude empty set and full set
        long long product1 = 1;
        long long product2 = 1;
        for (int i = 0; i < numsSize; i++) {
            if (mask & (1 << i)) {
                product1 *= nums[i];
            } else {
                product2 *= nums[i];
            }
        }
        if (product1 == target && product2 == target) {
            return true;
        }
    }
    return false;       
}
