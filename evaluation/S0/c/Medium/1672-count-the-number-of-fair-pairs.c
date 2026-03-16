// Source: https://leetcode.com/problems/count-the-number-of-fair-pairs/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed integer array nums of size n and two integers lower and upper, return the number of fair pairs.
//
// A pair (i, j) is fair if:
//
//
// 	0 <= i < j < n, and
// 	lower <= nums[i] + nums[j] <= upper
//
// Example:
// Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
// Output: 6
// Explanation: There are 6 fair pairs: (0,3), (0,4), (0,5), (1,3), (1,4), and (1,5).
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums.length == n
// 	-109 <= nums[i] <= 109
// 	-109 <= lower <= upper <= 109
//

long long countFairPairs(int* nums, int numsSize, int lower, int upper) {
    // Helper function for qsort
    int compare(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }

    // Binary search to find the lower bound
    int lower_bound(int* arr, int size, int target) {
        int left = 0, right = size;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    // Binary search to find the upper bound
    int upper_bound(int* arr, int size, int target) {
        int left = 0, right = size;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    // Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

    long long count = 0;

    // Count fair pairs
    for (int i = 0; i < numsSize; i++) {
        int low_target = lower - nums[i];
        int high_target = upper - nums[i];

        int low_index = lower_bound(nums + i + 1, numsSize - i - 1, low_target);
        int high_index = upper_bound(nums + i + 1, numsSize - i - 1, high_target);

        count += (high_index - low_index);
    }

    return count;       
}
