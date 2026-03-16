// Source: https://leetcode.com/problems/append-k-integers-with-minimal-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Append k unique positive integers that do not appear in nums to nums such that the resulting total sum is minimum.
//
// Return the sum of the k integers appended to nums.
//
// Example:
// Input: nums = [1,4,25,10,25], k = 2
// Output: 5
// Explanation: The two unique positive integers that do not appear in nums which we append are 2 and 3.
// The resulting sum of nums is 1 + 4 + 25 + 10 + 25 + 2 + 3 = 70, which is the minimum.
// The sum of the two integers appended is 2 + 3 = 5, so we return 5.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 108
//

long long minimalKSum(int* nums, int numsSize, int k) {
    // Create a hash set to store unique numbers from nums
    #define HASH_SIZE 200003
    int hash[HASH_SIZE] = {0};
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < HASH_SIZE) {
            hash[nums[i]] = 1;
        }
    }

    long long sum = 0;
    int count = 0;
    int current = 1;

    // Append k unique positive integers not in nums
    while (count < k) {
        if (current >= HASH_SIZE || hash[current] == 0) {
            sum += current;
            count++;
        }
        current++;
    }

    return sum;     
}
