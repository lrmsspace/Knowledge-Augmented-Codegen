// Source: https://leetcode.com/problems/number-of-unique-xor-triplets-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of length n, where nums is a permutation of the numbers in the range [1, n].
//
// A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
//
// Return the number of unique XOR triplet values from all possible triplets (i, j, k).
//
// Example:
// Input: nums = [1,2]
//
// Output: 2
//
// Explanation:
//
// The possible XOR triplet values are:
//
//
// 	(0, 0, 0) → 1 XOR 1 XOR 1 = 1
// 	(0, 0, 1) → 1 XOR 1 XOR 2 = 2
// 	(0, 1, 1) → 1 XOR 2 XOR 2 = 1
// 	(1, 1, 1) → 2 XOR 2 XOR 2 = 2
//
//
// The unique XOR values are {1, 2}, so the output is 2.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= n
// 	nums is a permutation of integers from 1 to n.
//
// Helpful references (internal KB):
// - Fast Fourier transform (array, divide-and-conquer, recursion)
//   • When to use: Use when performing fast polynomial multiplication, large number multiplication, or general convolutions, especially when an O(N log N) time complexity is required for large inputs.
//   • Idea: The Fast Fourier Transform (FFT) is an algorithm that computes the Discrete Fourier Transform (DFT) and its inverse in O(N log N) time. It leverages a divide-and-conquer strategy to efficiently transform a polynomial's coefficients to its point-value representation and vice-versa.
//   • Invariants: At the start of each recursive call, the input array length N is a power of two.; The DFT of the current polynomial is correctly computed from the DFTs of its even and odd coefficient sub-polynomials.
//   • Tips: Pad polynomials with zeros to a power-of-two length for efficient processing.; Use complex numbers for roots of unity, or modular arithmetic for Number Theoretic Transform (NTT).
//   • Pitfalls: Forgetting to pad polynomials to a sufficient degree (sum of degrees) for multiplication.; Numerical precision issues when using floating-point complex numbers for large N.
// - Fast Fourier transform (number, array, mod-exp)
//   • When to use: Use when you need to perform polynomial multiplication or convolution efficiently for large inputs, or when dealing with modular arithmetic for exact integer results.
//   • Idea: The Fast Fourier Transform (FFT) is an algorithm that computes the Discrete Fourier Transform (DFT) and its inverse in O(N log N) time. It efficiently transforms a sequence of values from the time domain to the frequency domain, enabling fast polynomial multiplication and convolution.
//   • Invariants: After each stage k, all sub-problems of size 2^k have their DFTs computed correctly.; The bit-reversal permutation ensures elements are in their correct final positions before butterfly operations begin.
//   • Tips: Precompute bit-reversal permutation for repeated calls with the same input size N.; Precompute roots of unity and their powers to optimize calculations.
//   • Pitfalls: Rounding errors can occur with standard FFT when dealing with large numbers or precision-sensitive calculations.; Incorrect implementation of the bit-reversal permutation can lead to wrong results.
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var uniqueXorTriplets = function(nums) {
    const uniqueXors = new Set();
    const n = nums.length;
    
    for (let i = 0; i < n; i++) {
        for (let j = i; j < n; j++) {
            for (let k = j; k < n; k++) {
                const xorValue = nums[i] ^ nums[j] ^ nums[k];
                uniqueXors.add(xorValue);
            }
        }
    }
    
    return uniqueXors.size;
};
