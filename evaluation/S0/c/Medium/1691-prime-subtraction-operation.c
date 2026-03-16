// Source: https://leetcode.com/problems/prime-subtraction-operation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n.
//
// You can perform the following operation as many times as you want:
//
//
// 	Pick an index i that you haven’t picked before, and pick a prime p strictly less than nums[i], then subtract p from nums[i].
//
//
// Return true if you can make nums a strictly increasing array using the above operation and false otherwise.
//
// A strictly increasing array is an array whose each element is strictly greater than its preceding element.
//
// Example:
// Input: nums = [4,9,6,10]
// Output: true
// Explanation: In the first operation: Pick i = 0 and p = 3, and then subtract 3 from nums[0], so that nums becomes [1,9,6,10].
// In the second operation: i = 1, p = 7, subtract 7 from nums[1], so nums becomes equal to [1,2,6,10].
// After the second operation, nums is sorted in strictly increasing order, so the answer is true.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	nums.length == n
//

bool primeSubOperation(int* nums, int numsSize) {
    bool is_prime[1001];
    for (int i = 0; i <= 1000; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= 1000; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= 1000; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int prev = 0;
    for (int i = 0; i < numsSize; i++) {
        int target = nums[i] - 1;
        while (target >= prev) {
            if (is_prime[target]) {
                break;
            }
            target--;
        }
        if (target < prev) {
            return false;
        }
        nums[i] -= target;
        prev = nums[i];
    }
    return true;        
}
