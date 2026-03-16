// Source: https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of size n consisting of positive integers.
//
// You are also given a 2D array queries of size m where queries[i] = [indexi, ki].
//
// Initially all elements of the array are unmarked.
//
// You need to apply m queries on the array in order, where on the ith query you do the following:
//
//
// 	Mark the element at index indexi if it is not already marked.
// 	Then mark ki unmarked elements in the array with the smallest values. If multiple such elements exist, mark the ones with the smallest indices. And if less than ki unmarked elements exist, then mark all of them.
//
//
// Return an array answer of size m where answer[i] is the sum of unmarked elements in the array after the ith query.
//
// Example:
// Input: nums = [1,2,2,1,2,3,1], queries = [[1,2],[3,3],[4,2]]
//
// Output: [8,3,0]
//
// Explanation:
//
// We do the following queries on the array:
//
//
// 	Mark the element at index 1, and 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 2 + 2 + 3 + 1 = 8.
// 	Mark the element at index 3, since it is already marked we skip it. Then we mark 3 of the smallest unmarked elements with the smallest indices, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 3.
// 	Mark the element at index 4, since it is already marked we skip it. Then we mark 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 0.
//
// Constraints:
// n == nums.length
// 	m == queries.length
// 	1 <= m <= n <= 105
// 	1 <= nums[i] <= 105
// 	queries[i].length == 2
// 	0 <= indexi, ki <= n - 1
//

/**
 * @param {number[]} nums
 * @param {number[][]} queries
 * @return {number[]}
 */
var unmarkedSumArray = function(nums, queries) {
    const n = nums.length;
    const m = queries.length;
    const indexedNums = nums.map((value, index) => [value, index]);
    indexedNums.sort((a, b) => a[0] - b[0] || a[1] - b[1]);
    const fenwickTree = new Array(n + 1).fill(0);
    const marked = new Array(n).fill(false);
    let totalSum = nums.reduce((acc, val) => acc + val, 0);
    const result = [];
    let currentIndex = 0;
    for (let i = 0; i < m; i++) {
        const [index, k] = queries[i];
        if (!marked[index]) {
            marked[index] = true;
            totalSum -= nums[index];
            let fenwickIndex = index + 1;
            while (fenwickIndex <= n) {
                fenwickTree[fenwickIndex] += 1;
                fenwickIndex += fenwickIndex & -fenwickIndex;
            }       
        }
        let toMark = k;
        while (toMark > 0 && currentIndex < n) {
            const [value, originalIndex] = indexedNums[currentIndex];
            const fenwickIndex = originalIndex + 1;
            let markedCount = 0;
            let tempIndex = fenwickIndex;
            while (tempIndex > 0) {
                markedCount += fenwickTree[tempIndex];
                tempIndex -= tempIndex & -tempIndex;
            }   
            if (!marked[originalIndex]) {
                marked[originalIndex] = true;
                totalSum -= value;
                let updateIndex = fenwickIndex;
                while (updateIndex <= n) {
                    fenwickTree[updateIndex] += 1;
                    updateIndex += updateIndex & -updateIndex;
                }   
                toMark--;
            }   
            currentIndex++;
        }   
        result.push(totalSum);
    }
    return result;
};
