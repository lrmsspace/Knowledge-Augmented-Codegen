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

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
var maximumCount = function(nums, queries) {
    const MAX_NUM = 100000;

    const spf = Array(MAX_NUM + 1).fill(0);
    for (let i = 2; i <= MAX_NUM; i++) {
        if (spf[i] === 0) {
            for (let j = i; j <= MAX_NUM; j += i) {
                if (spf[j] === 0) {
                    spf[j] = i;
                }
            }
        }
    }

    const getDistinctPrimes = (num) => {
        const primes = new Set();
        while (num > 1) {
            primes.add(spf[num]);
            num = Math.floor(num / spf[num]);
        }
        return primes;
    };
    const n = nums.length;
    const prefixCounts = Array(n).fill(0);
    const suffixCounts = Array(n).fill(0);
    const primeCountMapPrefix = new Map();
    const primeCountMapSuffix = new Map();
    for (let i = 0; i < n; i++) {
        const primes = getDistinctPrimes(nums[i]);
        for (const prime of primes) {
            primeCountMapPrefix.set(prime, (primeCountMapPrefix.get(prime) || 0) + 1);
        }
        prefixCounts[i] = primeCountMapPrefix.size;
    }
    for (let i = n - 1; i >= 0; i--) {
        const primes = getDistinctPrimes(nums[i]);
        for (const prime of primes) {
            primeCountMapSuffix.set(prime, (primeCountMapSuffix.get(prime) || 0) + 1);
        }
        suffixCounts[i] = primeCountMapSuffix.size;
    }
    const results = [];
    for (const [idx, val] of queries) {
        const oldPrimes = getDistinctPrimes(nums[idx]);
        const newPrimes = getDistinctPrimes(val);
        let maxCount = 0;
        for (let split = 1; split < n; split++) {
            let leftCount = prefixCounts[split - 1];
            let rightCount = suffixCounts[split];
            if (idx < split) {
                for (const prime of oldPrimes) {
                    if (!newPrimes.has(prime)) {
                        if (primeCountMapPrefix.get(prime) === 1) {
                            leftCount--;
                        }
                    }
                }
                for (const prime of newPrimes) {
                    if (!oldPrimes.has(prime)) {
                        if (!primeCountMapPrefix.has(prime) || primeCountMapPrefix.get(prime) === 0) {
                            leftCount++;
                        }
                    }
                }
            }
            else {
                for (const prime of oldPrimes) {
                    if (!newPrimes.has(prime)) {
                        if (primeCountMapSuffix.get(prime) === 1) {
                            rightCount--;
                        }
                    }
                }
                for (const prime of newPrimes) {
                    if (!oldPrimes.has(prime)) {
                        if (!primeCountMapSuffix.has(prime) || primeCountMapSuffix.get(prime) === 0) {
                            rightCount++;
                        }
                    }
                }
            }
            maxCount = Math.max(maxCount, leftCount + rightCount);
        }
        results.push(maxCount);
        for (const prime of oldPrimes) {
            primeCountMapPrefix.set(prime, primeCountMapPrefix.get(prime) - 1);
            if (primeCountMapPrefix.get(prime) === 0) {
                primeCountMapPrefix.delete(prime);
            }
            primeCountMapSuffix.set(prime, primeCountMapSuffix.get(prime) - 1);
            if (primeCountMapSuffix.get(prime) === 0) {
                primeCountMapSuffix.delete(prime);
            }
        }
        for (const prime of newPrimes) {
            primeCountMapPrefix.set(prime, (primeCountMapPrefix.get(prime) || 0) + 1);
            primeCountMapSuffix.set(prime, (primeCountMapSuffix.get(prime) || 0) + 1);
        }
        nums[idx] = val;
    }
    return results;
};
