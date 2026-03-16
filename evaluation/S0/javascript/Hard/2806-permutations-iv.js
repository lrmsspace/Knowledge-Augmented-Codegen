// Source: https://leetcode.com/problems/permutations-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given two integers, n and k, an alternating permutation is a permutation of the first n positive integers such that no two adjacent elements are both odd or both even.
//
// Return the k-th alternating permutation sorted in lexicographical order. If there are fewer than k valid alternating permutations, return an empty list.
//
// Example:
// Input: n = 4, k = 6
//
// Output: [3,4,1,2]
//
// Explanation:
//
// The lexicographically-sorted alternating permutations of [1, 2, 3, 4] are:
//
//
// 	[1, 2, 3, 4]
// 	[1, 4, 3, 2]
// 	[2, 1, 4, 3]
// 	[2, 3, 4, 1]
// 	[3, 2, 1, 4]
// 	[3, 4, 1, 2] ← 6th permutation
// 	[4, 1, 2, 3]
// 	[4, 3, 2, 1]
//
//
// Since k = 6, we return [3, 4, 1, 2].
//
// Constraints:
// 1 <= n <= 100
// 	1 <= k <= 1015
//

/**
 * @param {number} n
 * @param {number} k
 * @return {number[]}
 */
var permute = function(n, k) {
    const oddCount = Math.ceil(n / 2);
    const evenCount = Math.floor(n / 2);
    const factorial = [1n];
    for (let i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * BigInt(i);
    }
    const countAlternatingPermutations = (odd, even, startWithOdd) => {
        if (Math.abs(odd - even) > 1) return 0n;
        const oddPerms = factorial[odd];
        const evenPerms = factorial[even];
        return oddPerms * evenPerms;
    }
    const result = [];
    const used = Array(n + 1).fill(false);
    let startWithOdd = oddCount >= evenCount;
    for (let i = 0; i < n; i++) {
        for (let num = 1; num <= n; num++) {
            if (used[num]) continue;
            const isOdd = num % 2 === 1;
            if (isOdd !== startWithOdd) continue;
            const remainingOdd = isOdd ? oddCount - 1 : oddCount;
            const remainingEven = isOdd ? evenCount : evenCount - 1;
            const permsCount = countAlternatingPermutations(remainingOdd, remainingEven, !startWithOdd);
            if (BigInt(k) > permsCount) {
                k -= Number(permsCount);
            }
            else {
                result.push(num);
                used[num] = true;
                if (isOdd) oddCount--;
                else evenCount--;
                startWithOdd = !startWithOdd;
                break;
            }
        }
    }
    return result;  
};
