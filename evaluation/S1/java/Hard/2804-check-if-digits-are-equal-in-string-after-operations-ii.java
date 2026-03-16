// Source: https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of digits. Perform the following operation repeatedly until the string has exactly two digits:
//
//
// 	For each pair of consecutive digits in s, starting from the first digit, calculate a new digit as the sum of the two digits modulo 10.
// 	Replace s with the sequence of newly calculated digits, maintaining the order in which they are computed.
//
//
// Return true if the final two digits in s are the same; otherwise, return false.
//
// Example:
// Input: s = "3902"
//
// Output: true
//
// Explanation:
//
//
// 	Initially, s = "3902"
// 	First operation:
// 	
// 		(s[0] + s[1]) % 10 = (3 + 9) % 10 = 2
// 		(s[1] + s[2]) % 10 = (9 + 0) % 10 = 9
// 		(s[2] + s[3]) % 10 = (0 + 2) % 10 = 2
// 		s becomes "292"
// 	
// 	
// 	Second operation:
// 	
// 		(s[0] + s[1]) % 10 = (2 + 9) % 10 = 1
// 		(s[1] + s[2]) % 10 = (9 + 2) % 10 = 1
// 		s becomes "11"
// 	
// 	
// 	Since the digits in "11" are the same, the output is true.
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of only digits.
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean hasSameDigits(String s) {
        int n = s.length();
        int[] coeff = new int[n];
        coeff[0] = 1;

        for (int i = 1; i < n; i++) {
            coeff[i] = (coeff[i - 1] * 9) % 10;
        }

        int firstDigitSum = 0;
        int secondDigitSum = 0;

        for (int i = 0; i < n; i++) {
            int digit = s.charAt(i) - '0';
            if ((n - 1 - i) % 2 == 0) {
                firstDigitSum = (firstDigitSum + digit * coeff[i]) % 10;
            } else {
                secondDigitSum = (secondDigitSum + digit * coeff[i]) % 10;
            }
        }

        return firstDigitSum == secondDigitSum;         
    }
}
