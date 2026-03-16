// Source: https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums having length n and a 2D integer array queries where queries[i] = [idx, val].
//
// For each query:
//
//
// 	Update nums[idx] = val.
// 	Choose an integer k with 1 <= k < n to split the array into the non-empty prefix nums[0..k-1] and suffix nums[k..n-1] such that the sum of the counts of distinct prime values in each part is maximum.
//
//
// Note: The changes made to the array in one query persist into the next query.
//
// Return an array containing the result for each query, in the order they are given.
//
// Example:
// Input: nums = [2,1,3,1,2], queries = [[1,2],[3,3]]
//
// Output: [3,4]
//
// Explanation:
//
//
// 	Initially nums = [2, 1, 3, 1, 2].
// 	After 1st query, nums = [2, 2, 3, 1, 2]. Split nums into [2] and [2, 3, 1, 2]. [2] consists of 1 distinct prime and [2, 3, 1, 2] consists of 2 distinct primes. Hence, the answer for this query is 1 + 2 = 3.
// 	After 2nd query, nums = [2, 2, 3, 3, 2]. Split nums into [2, 2, 3] and [3, 2] with an answer of 2 + 2 = 4.
// 	The output is [3, 4].
//
// Constraints:
// 2 <= n == nums.length <= 5 * 104
// 	1 <= queries.length <= 5 * 104
// 	1 <= nums[i] <= 105
// 	0 <= queries[i][0] < nums.length
// 	1 <= queries[i][1] <= 105
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumCount(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Precompute smallest prime factors (SPF) for numbers up to 10^5
    const int MAX_NUM = 100000;
    int spf[MAX_NUM + 1]; // spf[i] = smallest prime factor of i
    for (int i = 0; i <= MAX_NUM; ++i) spf[i] = i;
    for (int i = 2; i * i <= MAX_NUM; ++i) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j <= MAX_NUM; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    // Function to count distinct primes in a number using SPF
    int countDistinctPrimes(int x) {
        int count = 0;
        int lastPrime = 0;
        while (x > 1) {
            int prime = spf[x];
            if (prime != lastPrime) {
                count++;
                lastPrime = prime;
            }
            x /= prime;
        }
        return count;
    }

    // Prepare result array
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    // Process each query
    for (int q = 0; q < queriesSize; ++q) {
        int idx = queries[q][0];
        int val = queries[q][1];
        nums[idx] = val;

        // Count distinct primes in prefix and suffix
        int maxDistinct = 0;
        for (int split = 1; split < numsSize; ++split) {
            // Count distinct primes in prefix nums[0..split-1]
            int prefixCount[100001] = {0};
            int prefixDistinct = 0;
            for (int i = 0; i < split; ++i) {
                int num = nums[i];
                while (num > 1) {
                    int prime = spf[num];
                    if (prefixCount[prime] == 0) {
                        prefixDistinct++;
                    }
                    prefixCount[prime]++;
                    num /= prime;
                }
            }

            // Count distinct primes in suffix nums[split..numsSize-1]
            int suffixCount[100001] = {0};
            int suffixDistinct = 0;
            for (int i = split; i < numsSize; ++i) {
                int num = nums[i];
                while (num > 1) {
                    int prime = spf[num];
                    if (suffixCount[prime] == 0) {
                        suffixDistinct++;
                    }
                    suffixCount[prime]++;
                    num /= prime;
                }
            }

            int totalDistinct = prefixDistinct + suffixDistinct;
            if (totalDistinct > maxDistinct) {
                maxDistinct = totalDistinct;
            }
        }
        result[q] = maxDistinct;
    }
    return result;

}
