// Source: https://leetcode.com/problems/number-of-common-factors/   |   Difficulty: Easy
//
// Problem Description:
// Given two positive integers a and b, return the number of common factors of a and b.
//
// An integer x is a common factor of a and b if x divides both a and b.
//
// Example:
// Input: a = 12, b = 6
// Output: 4
// Explanation: The common factors of 12 and 6 are 1, 2, 3, 6.
//
// Constraints:
// 1 <= a, b <= 1000
//
// Helpful references (internal KB):
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
// - Extended Euclidean Algorithm (number, gcd, simulation)
//   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
//   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
//   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
//   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
//   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
// - Integer factorization (number, enumeration)
//   • When to use: Use when needing to decompose a composite integer into its prime factors, especially for numbers where trial division is feasible. It's suitable for problems requiring the unique prime components of a number.
//   • Idea: Integer factorization decomposes a given composite number into a product of its prime factors. The most common approach, trial division, involves testing divisibility by prime numbers up to the square root of the number, with optimizations for small primes and patterns like modulo 6.
//   • Invariants: The product of found prime factors multiplied by the current number equals the original number.; All prime factors found so far are less than or equal to the current trial divisor.
//   • Tips: Handle small prime factors (2, 3, 5) separately for efficiency.; Optimize trial division by checking only primes or numbers of form 6k +/- 1.
//   • Pitfalls: Forgetting to handle the case where the remaining number is a prime factor itself.; Inefficiently checking all numbers instead of only potential prime divisors.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int commonFactors(int a, int b) {
    int count = 0;
    for (int i = 1; i <= a && i <= b; ++i) {
        if (a % i == 0 && b % i == 0) {
            count++;
        }
    }
    return count;       
}
