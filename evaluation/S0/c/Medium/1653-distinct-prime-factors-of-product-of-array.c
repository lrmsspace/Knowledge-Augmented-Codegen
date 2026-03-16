// Source: https://leetcode.com/problems/distinct-prime-factors-of-product-of-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of positive integers nums, return the number of distinct prime factors in the product of the elements of nums.
//
// Note that:
//
//
// 	A number greater than 1 is called prime if it is divisible by only 1 and itself.
// 	An integer val1 is a factor of another integer val2 if val2 / val1 is an integer.
//
// Example:
// Input: nums = [2,4,3,7,10,6]
// Output: 4
// Explanation:
// The product of all the elements in nums is: 2 * 4 * 3 * 7 * 10 * 6 = 10080 = 25 * 32 * 5 * 7.
// There are 4 distinct prime factors so we return 4.
//
// Constraints:
// 1 <= nums.length <= 104
// 	2 <= nums[i] <= 1000
//

int distinctPrimeFactors(int* nums, int numsSize) {
    int is_prime[1001];
    for (int i = 0; i <= 1000; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= 1000; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= 1000; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    int distinct_count = 0;
    int counted[1001] = {0};

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        for (int p = 2; p <= num; p++) {
            if (is_prime[p] && num % p == 0 && !counted[p]) {
                counted[p] = 1;
                distinct_count++;
            }
        }
    }

    return distinct_count;      
}
