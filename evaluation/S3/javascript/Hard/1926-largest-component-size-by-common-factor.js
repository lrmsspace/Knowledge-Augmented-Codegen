// Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array of unique positive integers nums. Consider the following graph:
//
//
// 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
// 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
//
//
// Return the size of the largest connected component in the graph.
//
// Example:
// Input: nums = [4,6,15,35]
// Output: 4
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 105
// 	All the values of nums are unique.
//
// Helpful references (internal KB):
// - Integer factorization (number, array, enumeration, sieve, counting)
//   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
//   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
//   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
//   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
//   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var largestComponentSize = function(nums) {
    const maxNum = Math.max(...nums);
    const primeFactors = Array(maxNum + 1).fill(0).map(() => []);
    for (let i = 2; i <= maxNum; i++) {
        if (primeFactors[i].length === 0) {
            for (let j = i; j <= maxNum; j += i) {
                primeFactors[j].push(i);
            }
        }
    }
        
    const parent = Array(nums.length).fill(0).map((_, i) => i);
    const find = (x) => {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    const union = (x, y) => {
        parent[find(x)] = find(y);
    };
    const factorToIndex = new Map();
    for (let i = 0; i < nums.length; i++) {
        for (const factor of primeFactors[nums[i]]) {
            if (factorToIndex.has(factor)) {
                union(i, factorToIndex.get(factor));
            }
            factorToIndex.set(factor, i);
        }
    }
    const componentSize = new Map();
    let maxSize = 0;
    for (let i = 0; i < nums.length; i++) {
        const root = find(i);
        componentSize.set(root, (componentSize.get(root) || 0) + 1);
        maxSize = Math.max(maxSize, componentSize.get(root));
    }
    return maxSize;
        
};
