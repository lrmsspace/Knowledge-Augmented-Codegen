// Source: https://leetcode.com/problems/find-the-count-of-numbers-which-are-not-special/   |   Difficulty: Medium
//
// Problem Description:
// You are given 2 positive integers l and r. For any number x, all positive divisors of x except x are called the proper divisors of x.
//
// A number is called special if it has exactly 2 proper divisors. For example:
//
//
// 	The number 4 is special because it has proper divisors 1 and 2.
// 	The number 6 is not special because it has proper divisors 1, 2, and 3.
//
//
// Return the count of numbers in the range [l, r] that are not special.
//
// Example:
// Input: l = 5, r = 7
//
// Output: 3
//
// Explanation:
//
// There are no special numbers in the range [5, 7].
//
// Constraints:
// 1 <= l <= r <= 109
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
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
 * @param {number} l
 * @param {number} r
 * @return {number}
 */
var nonSpecialCount = function(l, r) {
   // Step 1: Count the total numbers in the range [l, r]
    const totalCount = r - l + 1;

    // Step 2: Count the special numbers in the range [l, r]
    let specialCount = 0;
    for (let i = 2; i * i <= r; i++) {
        if (isPrime(i)) {
            const square = i * i;
            if (square >= l && square <= r) {
                specialCount++;
            }
        }
    }

    // Step 3: Calculate non-special count
    return totalCount - specialCount;

    // Helper function to check if a number is prime
    function isPrime(num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 === 0 || num % 3 === 0) return false;
        for (let j = 5; j * j <= num; j += 6) {
            if (num % j === 0 || num % (j + 2) === 0) return false;
        }
        return true;
    }
};
