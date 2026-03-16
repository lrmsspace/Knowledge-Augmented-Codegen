// Source: https://leetcode.com/problems/construct-string-with-minimum-cost/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string target, an array of strings words, and an integer array costs, both arrays of the same length.
//
// Imagine an empty string s.
//
// You can perform the following operation any number of times (including zero):
//
//
// 	Choose an index i in the range [0, words.length - 1].
// 	Append words[i] to s.
// 	The cost of operation is costs[i].
//
//
// Return the minimum cost to make s equal to target. If it's not possible, return -1.
//
// Example:
// Input: target = "abcdef", words = ["abdef","abc","d","def","ef"], costs = [100,1,1,10,5]
//
// Output: 7
//
// Explanation:
//
// The minimum cost can be achieved by performing the following operations:
//
//
// 	Select index 1 and append "abc" to s at a cost of 1, resulting in s = "abc".
// 	Select index 2 and append "d" to s at a cost of 1, resulting in s = "abcd".
// 	Select index 4 and append "ef" to s at a cost of 5, resulting in s = "abcdef".
//
// Constraints:
// 1 <= target.length <= 5 * 104
// 	1 <= words.length == costs.length <= 5 * 104
// 	1 <= words[i].length <= target.length
// 	The total sum of words[i].length is less than or equal to 5 * 104.
// 	target and words[i] consist only of lowercase English letters.
// 	1 <= costs[i] <= 104
//

/**
 * @param {string} target
 * @param {string[]} words
 * @param {number[]} costs
 * @return {number}
 */
var minimumCost = function(target, words, costs) {
    const dp = new Array(target.length + 1).fill(Infinity);
    dp[0] = 0; // Base case: cost to construct an empty string is 0
    for (let i = 1; i <= target.length; i++) {
        for (let j = 0; j < words.length; j++) {
            const word = words[j];
            const cost = costs[j];
            if (i >= word.length && target.slice(i - word.length, i) === word) {
                dp[i] = Math.min(dp[i], dp[i - word.length] + cost);
            }
        }
    }
    return dp[target.length] === Infinity ? -1 : dp[target.length]; 
};
