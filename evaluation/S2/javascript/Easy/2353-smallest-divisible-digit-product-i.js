// Source: https://leetcode.com/problems/smallest-divisible-digit-product-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integers n and t. Return the smallest number greater than or equal to n such that the product of its digits is divisible by t.
//
// Example:
// Input: n = 10, t = 2
//
// Output: 10
//
// Explanation:
//
// The digit product of 10 is 0, which is divisible by 2, making it the smallest number greater than or equal to 10 that satisfies the condition.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= t <= 10
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
// - Discrete Root
//  (number, gcd, mod-exp)
//   • When to use: Used to find all solutions to a discrete root problem of the form x^k 
//  a mod n, given one solution and a primitive root g for the modulus n.
//   • Idea: This algorithm finds all solutions to a discrete root congruence x^k a mod n by leveraging properties of primitive roots and Euler's totient function phi(n).
//   • Invariants: The base g is a primitive root modulo n.; The exponent y_0 + i * (phi(n) / gcd(k, phi(n))) is always an integer for valid i.
//   • Tips: Ensure the base g is indeed a primitive root modulo n.; Accurately calculate Euler's totient function phi(n).
//   • Pitfalls: Assuming g is a primitive root when it is not, leading to incorrect results.; Errors in calculating phi(n) or gcd(k, phi(n)).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number} t
 * @return {number}
 */
var smallestNumber = function(n, t) {
    for (let num = n; num <= 999999999; num++) {
        const digits = String(num).split('');
        const product = digits.reduce((acc, digit) => acc * parseInt(digit), 1);
        
        if (product % t === 0) {
            return num;
        }
    }
    
    return -1; // This line should never be reached given the constraints.
};
