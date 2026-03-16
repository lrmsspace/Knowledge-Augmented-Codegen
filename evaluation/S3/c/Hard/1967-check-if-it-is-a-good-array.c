// Source: https://leetcode.com/problems/check-if-it-is-a-good-array/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums of positive integers. Your task is to select some subset of nums, multiply each element by an integer and add all these numbers. The array is said to be good if you can obtain a sum of 1 from the array by any possible subset and multiplicand.
//
// Return True if the array is good otherwise return False.
//
// Example:
// Input: nums = [12,5,7,23]
// Output: true
// Explanation: Pick numbers 5 and 7.
// 5*3 + 7*(-2) = 1
//
// Constraints:
// 1 <= nums.length <= 10^5
// 	1 <= nums[i] <= 10^9
//
// Helpful references (internal KB):
// - Linear Diophantine Equation (number, enumeration)
//   • When to use: Use when you need to find all integer solutions (x, y) for a linear equation of the form ax + by = c, or to determine if such solutions exist. It is also applicable for enumerating solutions within specified bounds.
//   • Idea: This method finds all integer solutions (x, y) to the linear equation ax + by = c. It utilizes the Extended Euclidean Algorithm to find a particular solution, then generates the general solution set using properties of the greatest common divisor in O(log(min(a,b))) time.
//   • Invariants: The equation a * x + b * y = c holds true for any generated integer solution (x, y).; For integer solutions to exist, c must be perfectly divisible by gcd(a, b).
//   • Tips: Always check if c is divisible by gcd(a, b); if not, no integer solutions exist.; Use the Extended Euclidean Algorithm to find a particular solution (x0, y0) for ax + by = gcd(a, b).
//   • Pitfalls: Forgetting to verify that c is a multiple of gcd(a, b) before proceeding.; Incorrectly scaling the particular solution obtained from the Extended Euclidean Algorithm.
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
// - Garner's algorithm
//  (number, array, enumeration)
//   • When to use: Use when reconstructing a large integer from a system of congruences with pairwise coprime moduli, offering an alternative to the direct Chinese Remainder Theorem approach.
//   • Idea: Garner's algorithm efficiently reconstructs an integer from its remainders modulo a set of pairwise coprime numbers, by computing its mixed radix representation coefficients. It typically runs in O(k^2 log M) time, where k is the number of moduli and M is the maximum modulus, assuming modular inverse takes log M time.
//   • Invariants: At the start of iteration j, the partial sum $V_{j-1}$ satisfies $V_{j-1} \equiv a_i \pmod{p_i}$ for all $i < j$.; For each iteration j, the coefficient $x_j$ is uniquely determined in the range $[0, p_j - 1]$.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Precompute modular inverses for efficiency, especially if many are needed.
//   • Pitfalls: Incorrectly calculating modular inverses, leading to wrong coefficients.; Not handling large intermediate products, which can cause integer overflow.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isGoodArray(int* nums, int numsSize) {
    // A good array is one where the greatest common divisor (GCD) of all its elements is 1.
    // If the GCD is greater than 1, it means that all numbers share a common factor, and we cannot obtain a sum of 1 by any combination of these numbers.

    int gcd = nums[0];
    for (int i = 1; i < numsSize; i++) {
        // Calculate GCD using Euclid's algorithm
        int a = gcd;
        int b = nums[i];
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        gcd = a;

        // If at any point the GCD becomes 1, we can stop and return true
        if (gcd == 1) {
            return true;
        }
    }

    // If after processing all numbers the GCD is greater than 1, return false
    return false;       
}
