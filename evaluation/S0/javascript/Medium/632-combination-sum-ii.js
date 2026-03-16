// Source: https://leetcode.com/problems/combination-sum-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
//
// Each number in candidates may only be used once in the combination.
//
// Note: The solution set must not contain duplicate combinations.
//
// Example:
// Input: candidates = [10,1,2,7,6,1,5], target = 8
// Output: 
// [
// [1,1,6],
// [1,2,5],
// [1,7],
// [2,6]
// ]
//
// Constraints:
// 1 <= candidates.length <= 100
// 	1 <= candidates[i] <= 50
// 	1 <= target <= 30
//

/**
 * @param {number[]} candidates
 * @param {number} target
 * @return {number[][]}
 */
var combinationSum2 = function(candidates, target) {
    const result = [];
    candidates.sort((a, b) => a - b); // Sort to handle duplicates

    function backtrack(remaining, combination, start) {
        if (remaining === 0) {
            result.push([...combination]);
            return;
        }
        if (remaining < 0) {
            return;
        }

        for (let i = start; i < candidates.length; i++) {
            if (i > start && candidates[i] === candidates[i - 1]) continue; // Skip duplicates
            combination.push(candidates[i]);
            backtrack(remaining - candidates[i], combination, i + 1); // i + 1 because each number can only be used once
            combination.pop();
        }
    }

    backtrack(target, [], 0);
    return result;  
};  