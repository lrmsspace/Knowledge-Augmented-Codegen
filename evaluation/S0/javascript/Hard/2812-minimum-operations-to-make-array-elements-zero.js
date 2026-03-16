// Source: https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array queries, where queries[i] is of the form [l, r]. Each queries[i] defines an array of integers nums consisting of elements ranging from l to r, both inclusive.
//
// In one operation, you can:
//
//
// 	Select two integers a and b from the array.
// 	Replace them with floor(a / 4) and floor(b / 4).
//
//
// Your task is to determine the minimum number of operations required to reduce all elements of the array to zero for each query. Return the sum of the results for all queries.
//
// Example:
// Input: queries = [[1,2],[2,4]]
//
// Output: 3
//
// Explanation:
//
// For queries[0]:
//
//
// 	The initial array is nums = [1, 2].
// 	In the first operation, select nums[0] and nums[1]. The array becomes [0, 0].
// 	The minimum number of operations required is 1.
//
//
// For queries[1]:
//
//
// 	The initial array is nums = [2, 3, 4].
// 	In the first operation, select nums[0] and nums[2]. The array becomes [0, 3, 1].
// 	In the second operation, select nums[1] and nums[2]. The array becomes [0, 0, 0].
// 	The minimum number of operations required is 2.
//
//
// The output is 1 + 2 = 3.
//
// Constraints:
// 1 <= queries.length <= 105
// 	queries[i].length == 2
// 	queries[i] == [l, r]
// 	1 <= l < r <= 109
//

/**
 * @param {number[][]} queries
 * @return {number}
 */
var minOperations = function(queries) {
    let totalOperations = 0;

    for (const [l, r] of queries) {
        let count = 0;
        for (let num = l; num <= r; num++) {
            let current = num;
            while (current > 0) {
                current = Math.floor(current / 4);
                count++;
            }
        }
        totalOperations += Math.floor(count / 2);
    }
    return totalOperations;
};
