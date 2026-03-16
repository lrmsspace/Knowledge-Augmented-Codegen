// Source: https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n which represents an array nums containing the numbers from 1 to n in order. Additionally, you are given a 2D array conflictingPairs, where conflictingPairs[i] = [a, b] indicates that a and b form a conflicting pair.
//
// Remove exactly one element from conflictingPairs. Afterward, count the number of non-empty subarrays of nums which do not contain both a and b for any remaining conflicting pair [a, b].
//
// Return the maximum number of subarrays possible after removing exactly one conflicting pair.
//
// Example:
// Input: n = 4, conflictingPairs = [[2,3],[1,4]]
//
// Output: 9
//
// Explanation:
//
//
// 	Remove [2, 3] from conflictingPairs. Now, conflictingPairs = [[1, 4]].
// 	There are 9 subarrays in nums where [1, 4] do not appear together. They are [1], [2], [3], [4], [1, 2], [2, 3], [3, 4], [1, 2, 3] and [2, 3, 4].
// 	The maximum number of subarrays we can achieve after removing one element from conflictingPairs is 9.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= conflictingPairs.length <= 2 * n
// 	conflictingPairs[i].length == 2
// 	1 <= conflictingPairs[i][j] <= n
// 	conflictingPairs[i][0] != conflictingPairs[i][1]
//

/**
 * @param {number} n
 * @param {number[][]} conflictingPairs
 * @return {number}
 */
var maxSubarrays = function(n, conflictingPairs) {
    const totalSubarrays = (n * (n + 1)) / 2;
    const pairMap = new Map();
    for (const [a, b] of conflictingPairs) {
        if (!pairMap.has(a)) pairMap.set(a, new Set());
        if (!pairMap.has(b)) pairMap.set(b, new Set());
        pairMap.get(a).add(b);
        pairMap.get(b).add(a);
    }
    let maxValidSubarrays = 0;
    for (const [removeA, removeB] of conflictingPairs) {
        let left = 1;
        let validSubarrays = 0;
        const blocked = new Set();
        for (let right = 1; right <= n; right++) {
            if (pairMap.has(right)) {
                for (const conflict of pairMap.get(right)) {
                    if (conflict !== removeA && conflict !== removeB) {
                        blocked.add(conflict);
                    }
                }
            }
            while (blocked.has(right)) {
                if (pairMap.has(left)) {
                    for (const conflict of pairMap.get(left)) {
                        blocked.delete(conflict);
                    }
                }
                left++;
            }
            validSubarrays += right - left + 1;
        }
        maxValidSubarrays = Math.max(maxValidSubarrays, validSubarrays);
    }
    return maxValidSubarrays;
};
