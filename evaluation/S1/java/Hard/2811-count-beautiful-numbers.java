// Source: https://leetcode.com/problems/count-beautiful-numbers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers, l and r. A positive integer is called beautiful if the product of its digits is divisible by the sum of its digits.
//
// Return the count of beautiful numbers between l and r, inclusive.
//
// Example:
// Input: l = 10, r = 20
//
// Output: 2
//
// Explanation:
//
// The beautiful numbers in the range are 10 and 20.
//
// Constraints:
// 1 <= l <= r < 109
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
//   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
//   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
//   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
//   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int[][][] memo;
    private int b;
    private String decrement(String num) {
        char[] arr = num.toCharArray();
        int n = arr.length;
        int i = n - 1;
        while (i >= 0) {
            if (arr[i] > '0') {
                arr[i]--;
                break;
            } else {
                arr[i] = '9';
                i--;
            }
        }
        if (i == -1 && arr[0] == '0') {
            return new String(arr, 1, n - 1);
        }
        return new String(arr);
    }
    private int dfs(String num, int index, int sum, int product, boolean isTight) {
        if (index == num.length()) {
            return product % sum == 0 ? 1 : 0;
        }
        if (memo[index][sum][product] != -1 && !isTight) {
            return memo[index][sum][product];
        }
        int limit = isTight ? num.charAt(index) - '0' : 9;
        int total = 0;
        for (int digit = 0; digit <= limit; digit++) {
            total += dfs(num, index + 1, sum + digit, product * (digit == 0 ? 1 : digit), isTight && (digit == limit));
        }
        if (!isTight) {
            memo[index][sum][product] = total;
        }
        return total;
    }
    private int countBeautiful(int num) {
        String numStr = Integer.toString(num);
        int maxSum = 9 * numStr.length();
        memo = new int[numStr.length()][maxSum + 1][100000]; // product can be large, but we limit it for practical reasons
        for (int i = 0; i < numStr.length(); i++) {
            for (int j = 0; j <= maxSum; j++) {
                Arrays.fill(memo[i][j], -1);
            }
        }
        return dfs(numStr, 0, 0, 1, true);
    }
    public int beautifulNumbers(int l, int r) {
        return countBeautiful(r) - countBeautiful(l - 1);           
    }
}
