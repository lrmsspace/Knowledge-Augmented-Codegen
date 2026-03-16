// Source: https://leetcode.com/problems/maximum-prime-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// Return an integer that is the maximum distance between the indices of two (not necessarily different) prime numbers in nums.
//
// Example:
// Input: nums = [4,2,9,5,3]
//
// Output: 3
//
// Explanation: nums[1], nums[3], and nums[4] are prime. So the answer is |4 - 1| = 3.
//
// Constraints:
// 1 <= nums.length <= 3 * 105
// 	1 <= nums[i] <= 100
// 	The input is generated such that the number of prime numbers in the nums is at least one.
//

int maximumPrimeDifference(int* nums, int numsSize) {
    int is_prime[101] = {0};
    is_prime[2] = 1; is_prime[3] = 1; is_prime[5] = 1; is_prime[7] = 1;
    is_prime[11] = 1; is_prime[13] = 1; is_prime[17] = 1; is_prime[19] = 1;
    is_prime[23] = 1; is_prime[29] = 1; is_prime[31] = 1; is_prime[37] = 1;
    is_prime[41] = 1; is_prime[43] = 1; is_prime[47] = 1; is_prime[53] = 1;
    is_prime[59] = 1; is_prime[61] = 1; is_prime[67] = 1; is_prime[71] = 1;
    is_prime[73] = 1; is_prime[79] = 1; is_prime[83] = 1; is_prime[89] = 1;
    is_prime[97] = 1;

    int first_prime_index = -1;
    int last_prime_index = -1;

    for (int i = 0; i < numsSize; i++) {
        if (is_prime[nums[i]]) {
            if (first_prime_index == -1) {
                first_prime_index = i;
            }
            last_prime_index = i;
        }
    }

    return last_prime_index - first_prime_index;        
}
