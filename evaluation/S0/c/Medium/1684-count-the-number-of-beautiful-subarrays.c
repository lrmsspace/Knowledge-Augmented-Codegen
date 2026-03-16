// Source: https://leetcode.com/problems/count-the-number-of-beautiful-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. In one operation, you can:
//
//
// 	Choose two different indices i and j such that 0 <= i, j < nums.length.
// 	Choose a non-negative integer k such that the kth bit (0-indexed) in the binary representation of nums[i] and nums[j] is 1.
// 	Subtract 2k from nums[i] and nums[j].
//
//
// A subarray is beautiful if it is possible to make all of its elements equal to 0 after applying the above operation any number of times (including zero).
//
// Return the number of beautiful subarrays in the array nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Note: Subarrays where all elements are initially 0 are considered beautiful, as no operation is needed.
//
// Example:
// Input: nums = [4,3,1,2,4]
// Output: 2
// Explanation: There are 2 beautiful subarrays in nums: [4,3,1,2,4] and [4,3,1,2,4].
// - We can make all elements in the subarray [3,1,2] equal to 0 in the following way:
//   - Choose [3, 1, 2] and k = 1. Subtract 21 from both numbers. The subarray becomes [1, 1, 0].
//   - Choose [1, 1, 0] and k = 0. Subtract 20 from both numbers. The subarray becomes [0, 0, 0].
// - We can make all elements in the subarray [4,3,1,2,4] equal to 0 in the following way:
//   - Choose [4, 3, 1, 2, 4] and k = 2. Subtract 22 from both numbers. The subarray becomes [0, 3, 1, 2, 0].
//   - Choose [0, 3, 1, 2, 0] and k = 0. Subtract 20 from both numbers. The subarray becomes [0, 2, 0, 2, 0].
//   - Choose [0, 2, 0, 2, 0] and k = 1. Subtract 21 from both numbers. The subarray becomes [0, 0, 0, 0, 0].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
//

long long beautifulSubarrays(int* nums, int numsSize) {
    long long count = 0;
    int prefixXor = 0;
    int freqMap[1 << 21]; // Since nums[i] can be up to 10^6, we need 21 bits to represent it.
    for (int i = 0; i < (1 << 21); i++) {
        freqMap[i] = 0;
    }
    freqMap[0] = 1; // There's one way to have a prefix XOR of 0 (the empty subarray).

    for (int i = 0; i < numsSize; i++) {
        prefixXor ^= nums[i];
        count += freqMap[prefixXor];
        freqMap[prefixXor]++;
    }

    return count;       
}
