// Source: https://leetcode.com/problems/count-the-number-of-infection-sequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an array sick sorted in increasing order, representing positions of infected people in a line of n people.
//
// At each step, one uninfected person adjacent to an infected person gets infected. This process continues until everyone is infected.
//
// An infection sequence is the order in which uninfected people become infected, excluding those initially infected.
//
// Return the number of different infection sequences possible, modulo 109+7.
//
// Example:
// Input: n = 5, sick = [0,4]
//
// Output: 4
//
// Explanation:
//
// There is a total of 6 different sequences overall.
//
//
// 	Valid infection sequences are [1,2,3], [1,3,2], [3,2,1] and [3,1,2].
// 	[2,3,1] and [2,1,3] are not valid infection sequences because the person at index 2 cannot be infected at the first step.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= sick.length <= n - 1
// 	0 <= sick[i] <= n - 1
// 	sick is sorted in increasing order.
//
// Helpful references (internal KB):
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[]} sick
 * @return {number}
 */
var numberOfSequence = function(n, sick) {
    const MOD = 1e9 + 7;
    const m = sick.length;
    const left = sick[0];
    const right = n - 1 - sick[m - 1];
    const middle = [];
    for (let i = 1; i < m; i++) {
        middle.push(sick[i] - sick[i - 1] - 1);
    }

    const fact = new Array(n + 1).fill(0);
    fact[0] = 1;
    for (let i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    let result = fact[left + right];
    for (const x of middle) {
        result = (result * fact[x]) % MOD;
        result = (result * modInverse(x + left + right, MOD)) % MOD;
        left += x + 1;
        result = (result * modInverse(left, MOD)) % MOD;
    }
    return result;

    function modInverse(a, m) {
        let m0 = m, t, q;
        let x0 = 0, x1 = 1;

        if (m === 1) return 0;

        while (a > 1) {
            q = Math.floor(a / m);
            t = m;

            m = a % m; a = t;
            t = x0;

            x0 = x1 - q * x0; x1 = t;
        }

        if (x1 < 0) x1 += m0;

        return x1;
    }
};
