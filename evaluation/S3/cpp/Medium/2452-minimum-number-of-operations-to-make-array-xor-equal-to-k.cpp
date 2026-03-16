// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and a positive integer k.
//
// You can apply the following operation on the array any number of times:
//
//
// 	Choose any element of the array and flip a bit in its binary representation. Flipping a bit means changing a 0 to 1 or vice versa.
//
//
// Return the minimum number of operations required to make the bitwise XOR of all elements of the final array equal to k.
//
// Note that you can flip leading zero bits in the binary representation of elements. For example, for the number (101)2 you can flip the fourth bit and obtain (1101)2.
//
// Example:
// Input: nums = [2,1,3,4], k = 1
// Output: 2
// Explanation: We can do the following operations:
// - Choose element 2 which is 3 == (011)2, we flip the first bit and we obtain (010)2 == 2. nums becomes [2,1,2,4].
// - Choose element 0 which is 2 == (010)2, we flip the third bit and we obtain (110)2 = 6. nums becomes [6,1,2,4].
// The XOR of elements of the final array is (6 XOR 1 XOR 2 XOR 4) == 1 == k.
// It can be shown that we cannot make the XOR equal to k in less than 2 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
// 	0 <= k <= 106
//
// Helpful references (internal KB):
// - Bit manipulation (number, enumeration, simulation)
//   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
//   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
//   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
//   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size(), maxNum = 0;
        for (int num : nums) maxNum = max(maxNum, num);
        int maxBit = 0;
        while ((1 << maxBit) <= maxNum) maxBit++;
        vector<int> count(1 << maxBit);
        for (int num : nums) count[num]++;
        int ans = INT_MAX;
        for (int mask = 0; mask < (1 << maxBit); mask++) {
            int xorSum = 0, operations = 0;
            for (int submask = mask; ; submask = (submask - 1) & mask) {
                xorSum ^= submask * count[submask];
                operations += count[submask] * __builtin_popcount(submask ^ mask);
                if (submask == 0) break;
            }
            if (xorSum == k) ans = min(ans, operations);
        }
        return ans == INT_MAX ? -1 : ans;           
    }
};
