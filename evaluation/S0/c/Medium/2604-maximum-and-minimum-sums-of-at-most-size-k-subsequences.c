// Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subsequences of nums with at most k elements.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 24
//
// Explanation:
//
// The subsequences of nums with at most 2 elements are:
//
//
// 	
// 		
// 			Subsequence 
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
// 			[1, 3]
// 			1
// 			3
// 			4
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
// 			24
// 		
// 	
//
//
// The output would be 24.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	1 <= k <= min(70, nums.length)
//

int minMaxSums(int* nums, int numsSize, int k) {
    #define MOD 1000000007
    #define MAX_K 70

    // Precompute binomial coefficients C(n, k)
    long long C[MAX_K + 1][MAX_K + 1] = {0};
    for (int i = 0; i <= MAX_K; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }

    // Sort the array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    long long result = 0;

    // Calculate contributions of each element as minimum
    for (int i = 0; i < numsSize; i++) {
        int maxChoose = (k - 1 < numsSize - i - 1) ? k - 1 : numsSize - i - 1;
        for (int j = 0; j <= maxChoose; j++) {
            result = (result + (long long)nums[i] * C[numsSize - i - 1][j]) % MOD;
        }
    }

    // Calculate contributions of each element as maximum
    for (int i = 0; i < numsSize; i++) {
        int maxChoose = (k - 1 < i) ? k - 1 : i;
        for (int j = 0; j <= maxChoose; j++) {
            result = (result + (long long)nums[i] * C[i][j]) % MOD;
        }
    }

    return (int)result;     
}
