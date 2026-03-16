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

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var maximumScore = function(nums, k) {
    const mod = 1e9 + 7;
    const n = nums.length;
    const primeScores = new Array(n);

    // Function to calculate the prime score of a number
    const calculatePrimeScore = (num) => {
        let score = 0;
        for (let i = 2; i * i <= num; i++) {
            if (num % i === 0) {
                score++;
                while (num % i === 0) {
                    num /= i;
                }
            }
        }
        if (num > 1) {
            score++;
        }
        return score;
    }

    // Calculate prime scores for all elements in nums
    for (let i = 0; i < n; i++) {
        primeScores[i] = calculatePrimeScore(nums[i]);
    }

    // Create an array of indices sorted by prime score and then by index
    const indices = Array.from({ length: n }, (_, i) => i);
    indices.sort((a, b) => {
        if (primeScores[a] === primeScores[b]) {
            return a - b; // Sort by index if prime scores are equal
        }
        return primeScores[b] - primeScores[a]; // Sort by prime score in descending order
    }
    );
    let score = 1;
    for (let i = 0; i < n && k > 0; i++) {
        const idx = indices[i];
        const subarrayCount = (idx + 1) * (n - idx);
        const operations = Math.min(k, subarrayCount);
        score = (score * BigInt(nums[idx]) ** BigInt(operations)) % BigInt(mod);
        k -= operations;
    }
    return Number(score);   
};
