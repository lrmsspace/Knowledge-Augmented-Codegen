// Source: https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/   |   Difficulty: Hard
//
// Problem Description:
// Let f(x) be the number of zeroes at the end of x!. Recall that x! = 1 * 2 * 3 * ... * x and by convention, 0! = 1.
//
//
// 	For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) = 2 because 11! = 39916800 has two zeroes at the end.
//
//
// Given an integer k, return the number of non-negative integers x have the property that f(x) = k.
//
// Example:
// Input: k = 0
// Output: 5
// Explanation: 0!, 1!, 2!, 3!, and 4! end with k = 0 zeroes.
//
// Constraints:
// 0 <= k <= 109
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Factorial modulo 
// p (number, counting)
//   • When to use: Use this when calculating factorials or expressions involving factorials in fractions modulo a prime `p`, especially when `p` is small and factors of `p` need to be explicitly handled for cancellation.
//   • Idea: This technique computes `n! mod p` by separating the factors of `p` from the remaining product, allowing for correct modular division in expressions like binomial coefficients.
//   • Invariants: The running product `P` always holds the value of `(i-1)!` with all factors of `p` removed, modulo `p`.; The variable `count_p` accurately stores the total exponent of `p` in `(i-1)!`.
//   • Tips: Precompute factorials and inverse factorials modulo `p` for terms not divisible by `p`.; Use Fermat's Little Theorem to find modular inverses when `p` is prime.
//   • Pitfalls: Incorrectly applying modular inverse when the divisor is a multiple of `p` or `p` is not prime.; Forgetting to handle the exponent of `p` separately, which can lead to an incorrect zero result.
// - Factorial modulo 
// p (number, counting, recursion)
//   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
//   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
//   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
//   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
//   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int preimageSizeFZF(int k) {
    // The number of trailing zeroes in n! is given by the formula:
    // f(n) = n / 5 + n / 25 + n / 125 + ... until n / 5^m = 0
    // We need to find how many non-negative integers n satisfy f(n) = k.

    // To find the range of n for which f(n) = k, we can use binary search.
    // We will search for the smallest n such that f(n) >= k and the largest n such that f(n) <= k.

    // Helper function to calculate f(n)
    int countTrailingZeroes(int n) {
        int count = 0;
        while (n > 0) {
            count += n / 5;
            n /= 5;
        }
        return count;
    }

    // Binary search for the smallest n such that f(n) >= k
    int left = 0, right = 5 * (k + 1); // upper bound for n
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (countTrailingZeroes(mid) < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int first = left;

    // Binary search for the largest n such that f(n) <= k
    left = 0, right = 5 * (k + 1);
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (countTrailingZeroes(mid) <= k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int last = left - 1;

    // The number of integers n such that f(n) = k is last - first + 1
    return last - first + 1;        
}
