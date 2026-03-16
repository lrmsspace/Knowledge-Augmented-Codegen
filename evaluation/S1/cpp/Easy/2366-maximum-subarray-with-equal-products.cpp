// Source: https://leetcode.com/problems/maximum-subarray-with-equal-products/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of positive integers nums.
//
// An array arr is called product equivalent if prod(arr) == lcm(arr) * gcd(arr), where:
//
//
// 	prod(arr) is the product of all elements of arr.
// 	gcd(arr) is the GCD of all elements of arr.
// 	lcm(arr) is the LCM of all elements of arr.
//
//
// Return the length of the longest product equivalent subarray of nums.
//
// Example:
// Input: nums = [1,2,1,2,1,1,1]
//
// Output: 5
//
// Explanation: 
//
// The longest product equivalent subarray is [1, 2, 1, 1, 1], where prod([1, 2, 1, 1, 1]) = 2, gcd([1, 2, 1, 1, 1]) = 1, and lcm([1, 2, 1, 1, 1]) = 2.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 10
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxLength(vector<int>& nums) {
        const int MAX_NUM = 10;
        vector<int> spf(MAX_NUM + 1, 0); // Smallest Prime Factor
        for (int i = 2; i <= MAX_NUM; ++i) {
            if (spf[i] == 0) {
                for (int j = i; j <= MAX_NUM; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }

        vector<int> hash_count(1 << 10, -1); // To store first occurrence index of each prime factor combination
        hash_count[0] = -1; // Empty product

        int max_len = 0;
        int current_hash = 0;
        int left = 0;

        for (int right = 0; right < nums.size(); ++right) {
            int num = nums[right];
            int prime_mask = 0;
            bool valid = true;

            while (num > 1) {
                int prime = spf[num];
                int count = 0;
                while (num % prime == 0) {
                    num /= prime;
                    count++;
                }
                if (count > 1) { // If any prime factor has exponent > 1, invalid
                    valid = false;
                    break;
                }
                prime_mask |= (1 << (prime - 1));
            }

            if (!valid) {
                current_hash = 0;
                left = right + 1;
                continue;
            }

            while ((current_hash & prime_mask) != 0) {
                int left_num = nums[left];
                int left_mask = 0;
                while (left_num > 1) {
                    int prime = spf[left_num];
                    left_num /= prime;
                    left_mask |= (1 << (prime - 1));
                }
                current_hash ^= left_mask;
                left++;
            }

            current_hash |= prime_mask;
            max_len = max(max_len, right - left + 1);
        }

        return max_len;         
    }
};
