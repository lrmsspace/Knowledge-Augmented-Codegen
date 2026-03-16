// Source: https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, m and k, and an integer array nums.
// A sequence of integers seq is called magical if:
//
//
// 	seq has a size of m.
// 	0 <= seq[i] < nums.length
// 	The binary representation of 2seq[0] + 2seq[1] + ... + 2seq[m - 1] has k set bits.
//
//
// The array product of this sequence is defined as prod(seq) = (nums[seq[0]] * nums[seq[1]] * ... * nums[seq[m - 1]]).
//
// Return the sum of the array products for all valid magical sequences.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// A set bit refers to a bit in the binary representation of a number that has a value of 1.
//
// Example:
// Input: m = 5, k = 5, nums = [1,10,100,10000,1000000]
//
// Output: 991600007
//
// Explanation:
//
// All permutations of [0, 1, 2, 3, 4] are magical sequences, each with an array product of 1013.
//
// Constraints:
// 1 <= k <= m <= 30
// 	1 <= nums.length <= 50
// 	1 <= nums[i] <= 108
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Operations on polynomials and series (array, recursion)
//   • When to use: Use when counting combinations or permutations with specific sum constraints, or when analyzing discrete probability distributions through polynomial multiplication.
//   • Idea: This technique represents combinatorial problems as coefficients of polynomials or formal power series. Solutions involve operations like polynomial multiplication and exponentiation, often with a time complexity dependent on the degree of the polynomials.
//   • Invariants: The degree of the product polynomial is the sum of the degrees of the input polynomials.; The coefficient of x^k in the product is the sum of A[i]*B[j] for all i+j=k.
//   • Tips: Represent individual choices as polynomial terms.; Multiply polynomials to combine independent events.
//   • Pitfalls: Incorrectly forming the initial generating function.; Naive polynomial multiplication can be computationally expensive.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} m
 * @param {number} k
 * @param {number[]} nums
 * @return {number}
 */
var magicalSum = function(m, k, nums) {
    const mod = 1e9 + 7;
    const n = nums.length;
    
    // Precompute factorials and inverse factorials for combinations
    const maxN = Math.max(m, n);
    const fact = new Array(maxN + 1).fill(1);
    for (let i = 1; i <= maxN; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    
    const invFact = new Array(maxN + 1).fill(1);
    invFact[maxN] = modExp(fact[maxN], mod - 2, mod);
    for (let i = maxN - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
    
    const comb = (n, r) => {
        if (r > n || r < 0) return 0;
        return ((fact[n] * invFact[r]) % mod * invFact[n - r]) % mod;
    };
    
    let result = 0;
    
    // Generate all magical sequences using bit manipulation
    for (let mask = 0; mask < (1 << n); mask++) {
        if (countSetBits(mask) === k) {
            const indices = [];
            for (let i = 0; i < n; i++) {
                if ((mask & (1 << i)) !== 0) {
                    indices.push(i);
                }
            }
            if (indices.length === m) {
                let product = 1;
                for (const idx of indices) {
                    product = (product * nums[idx]) % mod;
                }
                result = (result + product) % mod;
            }
        }
    }
    
    return result;
};
