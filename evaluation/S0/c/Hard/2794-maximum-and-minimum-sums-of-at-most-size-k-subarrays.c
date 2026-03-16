// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subarrays with at most k elements.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 20
//
// Explanation:
//
// The subarrays of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subarray
// 			Minimum
// 			Maximum
// 			Sum
// 		
// 		
// 			[1]
// 			1
// 			1
// 			2
// 		
// 		
// 			[2]
// 			2
// 			2
// 			4
// 		
// 		
// 			[3]
// 			3
// 			3
// 			6
// 		
// 		
// 			[1, 2]
// 			1
// 			2
// 			3
// 		
// 		
// 			[2, 3]
// 			2
// 			3
// 			5
// 		
// 		
// 			Final Total
// 			 
// 			 
// 			20
// 		
// 	
//
//
// The output would be 20.
//
// Constraints:
// 1 <= nums.length <= 80000
// 	1 <= k <= nums.length
// 	-106 <= nums[i] <= 106
//

long long minMaxSubarraySum(int* nums, int numsSize, int k) {
    long long total = 0;
    int mod = 1000000007;

    // Calculate sum of minimums
    int *minStack = (int*)malloc(numsSize * sizeof(int));
    int minTop = -1;
    long long *minCount = (long long*)calloc(numsSize, sizeof(long long));

    for (int i = 0; i < numsSize; ++i) {
        while (minTop >= 0 && nums[minStack[minTop]] > nums[i]) {
            minTop--;
        }
        int left = (minTop == -1) ? -1 : minStack[minTop];
        int right = i + k < numsSize ? i + k : numsSize;
        minCount[i] = (long long)(i - left) * (right - i);
        minStack[++minTop] = i;
    }

    for (int i = 0; i < numsSize; ++i) {
        total = (total + ((long long)nums[i] * minCount[i]) % mod) % mod;
    }

    free(minStack);
    free(minCount);

    // Calculate sum of maximums
    int *maxStack = (int*)malloc(numsSize * sizeof(int));
    int maxTop = -1;
    long long *maxCount = (long long*)calloc(numsSize, sizeof(long long));

    for (int i = 0; i < numsSize; ++i) {
        while (maxTop >= 0 && nums[maxStack[maxTop]] < nums[i]) {
            maxTop--;
        }
        int left = (maxTop == -1) ? -1 : maxStack[maxTop];
        int right = i + k < numsSize ? i + k : numsSize;
        maxCount[i] = (long long)(i - left) * (right - i);
        maxStack[++maxTop] = i;
    }

    for (int i = 0; i < numsSize; ++i) {
        total = (total + ((long long)nums[i] * maxCount[i]) % mod) % mod;
    }

    free(maxStack);
    free(maxCount);

    return total;       
}
