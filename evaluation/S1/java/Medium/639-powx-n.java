// Source: https://leetcode.com/problems/powx-n/   |   Difficulty: Medium
//
// Problem Description:
// Implement pow(x, n), which calculates x raised to the power n (i.e., xn).
//
// Example:
// Input: x = 2.00000, n = 10
// Output: 1024.00000
//
// Constraints:
// -100.0 < x < 100.0
// 	-231 <= n <= 231-1
// 	n is an integer.
// 	Either x is not zero or n > 0.
// 	-104 <= xn <= 104
//
// Helpful references (internal KB):
// - Binary Exponentiation (number, mod-exp, recursion)
//   • When to use: Use this algorithm to efficiently compute large integer powers of a number, especially when results need to be taken modulo a specific value. It is crucial for problems requiring powers with large exponents.
//   • Idea: Binary exponentiation, also known as exponentiation by squaring, computes a^n by breaking down the exponent n into its binary representation. This method significantly reduces the number of multiplications required, achieving an O(log n) time complexity.
//   • Invariants: In the iterative approach, (current_result * (original_base ^ original_exponent)) remains constant.; The exponent n is always non-negative and decreases towards zero.
//   • Tips: Apply the modulo operation at each multiplication step to prevent intermediate overflow.; The iterative approach is generally preferred over recursion to avoid potential stack overflow for very large exponents.
//   • Pitfalls: Forgetting to apply modulo at each step can lead to integer overflow, especially with large bases.; Incorrectly handling the base case for n=0 or n=1.
// - Discrete Root
//  (number, mod-exp)
//   • When to use: Use this algorithm to find all solutions x for the modular equation x^k = a (mod n) when n is a prime number. It is applicable when solving for an unknown base in a modular power.
//   • Idea: This algorithm solves the discrete root problem by transforming it into a discrete logarithm problem using a primitive root modulo n. The overall time complexity is dominated by the discrete logarithm step, typically O(sqrt(n) log n) using Baby-step Giant-step.
//   • Invariants: All calculations are performed within the finite field modulo n.; The primitive root g generates all non-zero residues modulo n.
//   • Tips: Handle the special case where a = 0 separately, as x = 0 is the only solution.; Ensure the modulus n is prime, as primitive roots are guaranteed to exist.
//   • Pitfalls: Assuming n is prime when it is not, which invalidates the primitive root approach.; Forgetting to check for the existence of solutions for the discrete logarithm.
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public double myPow(double x, int n) {
        if (n == 0) {
            return 1.0;
        }
        if (n < 0) {
            x = 1 / x;
            // Handle edge case where n is Integer.MIN_VALUE
            if (n == Integer.MIN_VALUE) {
                n = Integer.MAX_VALUE;
                x = x * x; // Compensate for the extra multiplication
            } else {
                n = -n;
            }
        }
        
        double result = 1.0;
        double current_product = x;
        
        while (n > 0) {
            if ((n % 2) == 1) { // If n is odd
                result *= current_product;
            }
            current_product *= current_product; // Square the base
            n /= 2; // Divide n by 2
        }
        
        return result;          
    }
}
