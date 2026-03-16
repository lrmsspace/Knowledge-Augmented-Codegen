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
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
var maximumCount = function(nums, queries) {
    const isPrime = (n) => {
        if (n < 2) return false;
        if (n === 2) return true;
        if (n % 2 === 0) return false;
        for (let i = 3; i * i <= n; i += 2) {
            if (n % i === 0) return false;
        }
        return true;
    };

    const countDistinctPrimes = (arr) => {
        const primes = new Set();
        for (const num of arr) {
            if (isPrime(num)) {
                primes.add(num);
            }
        }
        return primes.size;
    };

    const results = [];
    for (const [idx, val] of queries) {
        nums[idx] = val;
        let maxCount = 0;
        for (let k = 1; k < nums.length; k++) {
            const prefixCount = countDistinctPrimes(nums.slice(0, k));
            const suffixCount = countDistinctPrimes(nums.slice(k));
            maxCount = Math.max(maxCount, prefixCount + suffixCount);
        }
        results.push(maxCount);
    }

    return results;
};
