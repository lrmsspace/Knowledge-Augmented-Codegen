// Source: https://leetcode.com/problems/smallest-good-base/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n represented as a string, return the smallest good base of n.
//
// We call k >= 2 a good base of n, if all digits of n base k are 1's.
//
// Example:
// Input: n = "13"
// Output: "3"
// Explanation: 13 base 3 is 111.
//
// Constraints:
// n is an integer in the range [3, 1018].
// 	n does not contain any leading zeros.
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration)
//   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
//   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
//   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
//   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
//   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: When searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It is efficient for functions where direct differentiation or analytical solutions are complex.
//   • Idea: Ternary search is an algorithm that efficiently finds the extremum of a unimodal function within a given interval by repeatedly narrowing the search space. It typically achieves a logarithmic time complexity, O(log N), where N is the interval size.
//   • Invariants: The extremum of the unimodal function always lies within the current search interval [l, r].; The function value at m1 is compared with m2 to narrow the interval while preserving unimodality.
//   • Tips: Ensure the function is strictly unimodal within the search interval.; Handle discrete intervals carefully, especially the stopping condition (r - l) < 3.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Incorrect stopping conditions can lead to infinite loops or suboptimal answers.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* smallestGoodBase(char* n) {
    unsigned long long num = 0;
    for (char *p = n; *p; p++) {
        num = num * 10 + (*p - '0');
    }

    int max_m = 63; /* since 2^63 > 10^18 */
    for (int m = max_m; m >= 2; m--) {
        unsigned long long left = 2, right = num - 1;
        while (left <= right) {
            unsigned long long mid = left + (right - left) / 2;
            /* Compute sum = mid^0 + mid^1 + ... + mid^(m-1) */
            unsigned long long sum = 1;
            unsigned long long term = 1;
            for (int i = 1; i < m; i++) {
                if (term > (num - sum) / mid) { /* overflow check */
                    sum = num + 1; /* force sum > num */
                    break;
                }
                term *= mid;
                sum += term;
            }
            if (sum == num) {
                /* Found the base */
                char *res = (char*)malloc(22 * sizeof(char)); /* enough for base up to 10^18 */
                if (!res) return NULL;
                sprintf(res, "%llu", mid);
                return res;
            } else if (sum < num) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    /* Fallback: base is num - 1 */
    char *res = (char*)malloc(22 * sizeof(char));
    if (!res) return NULL;
    sprintf(res, "%llu", num - 1);
    return res;     
}
