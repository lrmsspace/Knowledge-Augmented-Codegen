// Source: https://leetcode.com/problems/concatenated-divisibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and a positive integer k.
//
// A permutation of nums is said to form a divisible concatenation if, when you concatenate the decimal representations of the numbers in the order specified by the permutation, the resulting number is divisible by k.
//
// Return the lexicographically smallest permutation (when considered as a list of integers) that forms a divisible concatenation. If no such permutation exists, return an empty list.
//
// Example:
// Input: nums = [3,12,45], k = 5
//
// Output: [3,12,45]
//
// Explanation:
//
//
// 	
// 		
// 			Permutation
// 			Concatenated Value
// 			Divisible by 5
// 		
// 	
// 	
// 		
// 			[3, 12, 45]
// 			31245
// 			Yes
// 		
// 		
// 			[3, 45, 12]
// 			34512
// 			No
// 		
// 		
// 			[12, 3, 45]
// 			12345
// 			Yes
// 		
// 		
// 			[12, 45, 3]
// 			12453
// 			No
// 		
// 		
// 			[45, 3, 12]
// 			45312
// 			No
// 		
// 		
// 			[45, 12, 3]
// 			45123
// 			No
// 		
// 	
//
//
// The lexicographically smallest permutation that forms a divisible concatenation is [3,12,45].
//
// Constraints:
// 1 <= nums.length <= 13
// 	1 <= nums[i] <= 105
// 	1 <= k <= 100
//

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var concatenatedDivisibility = function(nums, k) {
    const n = nums.length;
    const modValues = nums.map(num => {
        let mod = 0;
        for (const digit of num.toString()) {
            mod = (mod * 10 + parseInt(digit, 10)) % k;
        }
        return mod;
    });
    const fullMask = (1 << n) - 1;
    const dp = Array.from({ length: 1 << n }, () => Array(k).fill(null));
    dp[0][0] = [];
    for (let mask = 0; mask <= fullMask; mask++) {
        for (let mod = 0; mod < k; mod++) {
            if (dp[mask][mod] === null) continue;
            for (let i = 0; i < n; i++) {
                if ((mask & (1 << i)) !== 0) continue;
                const newMask = mask | (1 << i);
                const newMod = (mod * modValues[i] + modValues[i]) % k;
                const newPermutation = [...dp[mask][mod], nums[i]];
                if (dp[newMask][newMod] === null || isLexSmaller(newPermutation, dp[newMask][newMod])) {
                    dp[newMask][newMod] = newPermutation;
                }
            }
        }
    }
    return dp[fullMask][0] === null ? [] : dp[fullMask][0]; 
};
