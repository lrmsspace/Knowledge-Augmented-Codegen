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

class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        unordered_map<int, long long> prefixXorCount;
        prefixXorCount[0] = 1; // Initial prefix XOR is 0
        int prefixXor = 0;
        long long beautifulSubarrayCount = 0;

        for (int num : nums) {
            prefixXor ^= num;
            beautifulSubarrayCount += prefixXorCount[prefixXor];
            prefixXorCount[prefixXor]++;
        }

        return beautifulSubarrayCount;          
    }
};
