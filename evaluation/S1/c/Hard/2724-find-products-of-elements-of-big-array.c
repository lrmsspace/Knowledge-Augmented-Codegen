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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findProductsOfElements(long long** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize || !queriesColSize || !queries || queriesSize <= 0) return NULL;

    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;

    for (int q = 0; q < queriesSize; ++q) {
        long long from = queries[q][0];
        long long to = queries[q][1];
        int mod = (int)queries[q][2];

        long long product = 1;
        for (long long i = from; i <= to; ++i) {
            long long num = i;
            while (num > 0) {
                if (num & 1) {
                    product = (product * (num & -num)) % mod;
                }
                num &= (num - 1);
            }
        }
        results[q] = (int)product;
    }

    *returnSize = queriesSize;
    return results;     
}
