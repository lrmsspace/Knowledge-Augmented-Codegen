// Source: https://leetcode.com/problems/count-the-number-of-inversions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and a 2D array requirements, where requirements[i] = [endi, cnti] represents the end index and the inversion count of each requirement.
//
// A pair of indices (i, j) from an integer array nums is called an inversion if:
//
//
// 	i < j and nums[i] > nums[j]
//
//
// Return the number of permutations perm of [0, 1, 2, ..., n - 1] such that for all requirements[i], perm[0..endi] has exactly cnti inversions.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, requirements = [[2,2],[0,0]]
//
// Output: 2
//
// Explanation:
//
// The two permutations are:
//
//
// 	[2, 0, 1]
//
// 	
// 		Prefix [2, 0, 1] has inversions (0, 1) and (0, 2).
// 		Prefix [2] has 0 inversions.
// 	
// 	
// 	[1, 2, 0]
// 	
// 		Prefix [1, 2, 0] has inversions (0, 2) and (1, 2).
// 		Prefix [1] has 0 inversions.
//
// Constraints:
// 2 <= n <= 300
// 	1 <= requirements.length <= n
// 	requirements[i] = [endi, cnti]
// 	0 <= endi <= n - 1
// 	0 <= cnti <= 400
// 	The input is generated such that there is at least one i such that endi == n - 1.
// 	The input is generated such that all endi are unique.
//

/**
 * @param {number} n
 * @param {number[][]} requirements
 * @return {number}
 */
var numberOfPermutations = function(n, requirements) {
    const mod = 1e9 + 7;
    const dp = new Array(n + 1).fill(0).map(() => new Array(n * (n - 1) / 2 + 1).fill(0));
    dp[0][0] = 1;   
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= i * (i - 1) / 2; j++) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
            }
            if (j >= i) {
                dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + mod) % mod;
            }
        }
    }
    let result = 0;
    for (const [end, cnt] of requirements) {
        result = (result + dp[end + 1][cnt]) % mod;
    }
    return result;
}   
