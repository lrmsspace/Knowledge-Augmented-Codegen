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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumCount(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Precompute primes up to 10^5 using Sieve of Eratosthenes
    int maxVal = 100000;
    char *isPrime = (char*)malloc((maxVal + 1) * sizeof(char));
    for (int i = 0; i <= maxVal; ++i) isPrime[i] = 1;
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i <= maxVal; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= maxVal; j += i) {
                isPrime[j] = 0;
            }
        }
    }

    // Count initial distinct primes
    int distinctCount = 0;
    char *primeCount = (char*)calloc(maxVal + 1, sizeof(char));
    for (int i = 0; i < numsSize; ++i) {
        if (isPrime[nums[i]] && primeCount[nums[i]] == 0) {
            primeCount[nums[i]] = 1;
            distinctCount++;
        }
    }

    int *results = (int*)malloc(queriesSize * sizeof(int));
    for (int q = 0; q < queriesSize; ++q) {
        int idx = queries[q][0];
        int val = queries[q][1];
        int oldVal = nums[idx];

        // Update the number at index idx
        nums[idx] = val;

        // Update distinct prime count
        if (isPrime[oldVal]) {
            primeCount[oldVal]--;
            if (primeCount[oldVal] == 0) {
                distinctCount--;
            }
        }
        if (isPrime[val]) {
            if (primeCount[val] == 0) {
                distinctCount++;
            }
            primeCount[val]++;
        }

        results[q] = distinctCount;
    }

    free(isPrime);
    free(primeCount);

    *returnSize = queriesSize;
    return results;     
}
