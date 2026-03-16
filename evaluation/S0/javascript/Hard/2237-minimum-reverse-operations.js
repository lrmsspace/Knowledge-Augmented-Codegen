// Source: https://leetcode.com/problems/minimum-reverse-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an integer p representing an array arr of length n where all elements are set to 0's, except position p which is set to 1. You are also given an integer array banned containing restricted positions. Perform the following operation on arr:
//
//
// 	Reverse a subarray with size k if the single 1 is not set to a position in banned.
//
//
// Return an integer array answer with n results where the ith result is the minimum number of operations needed to bring the single 1 to position i in arr, or -1 if it is impossible.
//
// Example:
// Input: n = 4, p = 0, banned = [1,2], k = 4
//
// Output: [0,-1,-1,1]
//
// Explanation:
//
//
// 	Initially 1 is placed at position 0 so the number of operations we need for position 0 is 0.
// 	We can never place 1 on the banned positions, so the answer for positions 1 and 2 is -1.
// 	Perform the operation of size 4 to reverse the whole array.
// 	After a single operation 1 is at position 3 so the answer for position 3 is 1.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= p <= n - 1
// 	0 <= banned.length <= n - 1
// 	0 <= banned[i] <= n - 1
// 	1 <= k <= n 
// 	banned[i] != p
// 	all values in banned are unique
//

/**
 * @param {number} n
 * @param {number} p
 * @param {number[]} banned
 * @param {number} k
 * @return {number[]}
 */
var minReverseOperations = function(n, p, banned, k) {
    const answer = new Array(n).fill(-1);
    const bannedSet = new Set(banned);
    const queue = [p];
    answer[p] = 0;
    while (queue.length > 0) {
        const current = queue.shift();
        const currentDistance = answer[current];
        const leftBound = Math.max(current - k + 1, 0);
        const rightBound = Math.min(current + k - 1, n - 1);
        for (let i = leftBound; i <= rightBound; i++) {
            if (bannedSet.has(i) || answer[i] !== -1) {
                continue;
            }
            answer[i] = currentDistance + 1;
            queue.push(i);
        }
    }
    return answer;
};
