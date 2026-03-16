// Source: https://leetcode.com/problems/find-products-of-elements-of-big-array/   |   Difficulty: Hard
//
// Problem Description:
// The powerful array of a non-negative integer x is defined as the shortest sorted array of powers of two that sum up to x. The table below illustrates examples of how the powerful array is determined. It can be proven that the powerful array of x is unique.
//
//
// 	
// 		
// 			num
// 			Binary Representation
// 			powerful array
// 		
// 		
// 			1
// 			00001
// 			[1]
// 		
// 		
// 			8
// 			01000
// 			[8]
// 		
// 		
// 			10
// 			01010
// 			[2, 8]
// 		
// 		
// 			13
// 			01101
// 			[1, 4, 8]
// 		
// 		
// 			23
// 			10111
// 			[1, 2, 4, 16]
// 		
// 	
//
//
// The array big_nums is created by concatenating the powerful arrays for every positive integer i in ascending order: 1, 2, 3, and so on. Thus, big_nums begins as [1, 2, 1, 2, 4, 1, 4, 2, 4, 1, 2, 4, 8, ...].
//
// You are given a 2D integer matrix queries, where for queries[i] = [fromi, toi, modi] you should calculate (big_nums[fromi] * big_nums[fromi + 1] * ... * big_nums[toi]) % modi.
//
// Return an integer array answer such that answer[i] is the answer to the ith query.
//
// Example:
// Input: queries = [[1,3,7]]
//
// Output: [4]
//
// Explanation:
//
// There is one query.
//
// big_nums[1..3] = [2,1,2]. The product of them is 4. The result is 4 % 7 = 4.
//
// Constraints:
// 1 <= queries.length <= 500
// 	queries[i].length == 3
// 	0 <= queries[i][0] <= queries[i][1] <= 1015
// 	1 <= queries[i][2] <= 105
//
// Helpful references (internal KB):
// - Binary Exponentiation by Factoring (number, mod-exp, enumeration)
//   • When to use: Used to solve discrete logarithm problems of the form g^x = y mod m, specifically when the modulus m is a power of 2. It iteratively determines the bits of the exponent x.
//   • Idea: It solves the discrete logarithm problem g^x = y mod m by iteratively determining the bits of x, specifically optimized for moduli that are powers of 2. The approach involves modular exponentiation and inverse operations, typically resulting in a complexity of O(log^2 m) or O(log m) depending on modular inverse efficiency.
//   • Invariants: After k steps, the k least significant bits of x are correctly identified.; The current effective target y' is congruent to g^(2^k * x_remaining) modulo 2^d.
//   • Tips: Carefully handle modular arithmetic with powers of 2, as properties differ from prime moduli.; The order of g modulo 2^d is crucial for determining the number of bits to recover.
//   • Pitfalls: Incorrectly calculating modular inverses for non-coprime numbers with 2^d.; Off-by-one errors when determining the number of squaring steps.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} queries
 * @return {number[]}
 */
var findProductsOfElements = function(queries) {
    const mod = 1e9 + 7;
    const maxIndex = Math.max(...queries.map(q => q[1]));
    const bigNums = [];
    let currentNum = 1;
    let currentPower = 1;
    for (let i = 0; i <= maxIndex; i++) {
        while (currentPower <= i) {
            bigNums.push(currentPower);
            currentPower *= 2;
        }
        if (bigNums.length > 0) {
            bigNums.push(bigNums[bigNums.length - 1]);
        }
    }

    const prefixProducts = [1];
    for (let i = 0; i < bigNums.length; i++) {
        prefixProducts.push((prefixProducts[i] * bigNums[i]) % mod);
    }
    
    const results = [];
    for (const [l, r] of queries) {
        const product = (prefixProducts[r + 1] * modInverse(prefixProducts[l], mod)) % mod;
        results.push(product);
    }
    return results;
};

/**
 * @param {number} a
 * @param {number} m
 * @return {number}
 */
function modInverse(a, m) {
    return modExp(a, m - 2, m);
}

/**
 * @param {number} base
 * @param {number} exp
 * @param {number} mod
 * @return {number}
 */
function modExp(base, exp, mod) {
    let result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 === 1) {
            result = (result * base) % mod;
        }
        exp = Math.floor(exp / 2);
        base = (base * base) % mod;
    }
    return result;
}

