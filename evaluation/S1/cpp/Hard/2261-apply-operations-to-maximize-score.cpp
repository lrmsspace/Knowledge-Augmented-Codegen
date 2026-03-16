// Source: https://leetcode.com/problems/apply-operations-to-maximize-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n positive integers and an integer k.
//
// Initially, you start with a score of 1. You have to maximize your score by applying the following operation at most k times:
//
//
// 	Choose any non-empty subarray nums[l, ..., r] that you haven't chosen previously.
// 	Choose an element x of nums[l, ..., r] with the highest prime score. If multiple such elements exist, choose the one with the smallest index.
// 	Multiply your score by x.
//
//
// Here, nums[l, ..., r] denotes the subarray of nums starting at index l and ending at the index r, both ends being inclusive.
//
// The prime score of an integer x is equal to the number of distinct prime factors of x. For example, the prime score of 300 is 3 since 300 = 2 * 2 * 3 * 5 * 5.
//
// Return the maximum possible score after applying at most k operations.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [8,3,9,3,8], k = 2
// Output: 81
// Explanation: To get a score of 81, we can apply the following operations:
// - Choose subarray nums[2, ..., 2]. nums[2] is the only element in this subarray. Hence, we multiply the score by nums[2]. The score becomes 1 * 9 = 9.
// - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 1, but nums[2] has the smaller index. Hence, we multiply the score by nums[2]. The score becomes 9 * 9 = 81.
// It can be proven that 81 is the highest score one can obtain.
//
// Constraints:
// 1 <= nums.length == n <= 105
// 	1 <= nums[i] <= 105
// 	1 <= k <= min(n * (n + 1) / 2, 109)
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
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        const int MAX_NUM = 100000;

        // Sieve of Eratosthenes to calculate prime scores
        vector<int> primeScore(MAX_NUM + 1, 0);
        for (int i = 2; i <= MAX_NUM; ++i) {
            if (primeScore[i] == 0) { // i is prime
                for (int j = i; j <= MAX_NUM; j += i) {
                    primeScore[j]++;
                }
            }
        }

        int n = nums.size();
        vector<int> left(n), right(n);
        stack<int> stk;

        // Calculate left boundaries
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && primeScore[nums[stk.top()]] < primeScore[nums[i]]) {
                stk.pop();
            }
            left[i] = stk.empty() ? -1 : stk.top();
            stk.push(i);
        }

        while (!stk.empty()) stk.pop();

        // Calculate right boundaries
        for (int i = n - 1; i >= 0; --i) {
            while (!stk.empty() && primeScore[nums[stk.top()]] <= primeScore[nums[i]]) {
                stk.pop();
            }
            right[i] = stk.empty() ? n : stk.top();
            stk.push(i);
        }

        // Create pairs of (num, index) and sort by num descending
        vector<pair<int, int>> numIndexPairs;
        for (int i = 0; i < n; ++i) {
            numIndexPairs.emplace_back(nums[i], i);
        }
        sort(numIndexPairs.rbegin(), numIndexPairs.rend());

        long long result = 1;
        for (const auto& [num, idx] : numIndexPairs) {
            long long count = (long long)(idx - left[idx]) * (right[idx] - idx);
            long long use = min(count, (long long)k);
            result = (result * modPow(num, use, MOD)) % MOD;
            k -= use;
            if (k == 0) break;
        }

        return result;          
    }
};
