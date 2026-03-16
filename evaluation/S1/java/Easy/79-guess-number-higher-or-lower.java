// Source: https://leetcode.com/problems/guess-number-higher-or-lower/   |   Difficulty: Easy
//
// Problem Description:
// We are playing the Guess Game. The game is as follows:
//
// I pick a number from 1 to n. You have to guess which number I picked (the number I picked stays the same throughout the game).
//
// Every time you guess wrong, I will tell you whether the number I picked is higher or lower than your guess.
//
// You call a pre-defined API int guess(int num), which returns three possible results:
//
//
// 	-1: Your guess is higher than the number I picked (i.e. num > pick).
// 	1: Your guess is lower than the number I picked (i.e. num < pick).
// 	0: your guess is equal to the number I picked (i.e. num == pick).
//
//
// Return the number that I picked.
//
// Example:
// Input: n = 10, pick = 6
// Output: 6
//
// Constraints:
// 1 <= n <= 231 - 1
// 	1 <= pick <= n
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Primality tests (number, mod-exp, randomized, probability-statistics, simulation)
//   • When to use: Use when needing to efficiently determine if a large number is prime or composite, especially for cryptographic applications or number theory problems. It's suitable for verifying primality with high probability, or deterministically for numbers within certain bounds.
//   • Idea: The Miller-Rabin primality test is a probabilistic algorithm that determines if a given number is composite or a strong probable prime. It leverages properties of modular arithmetic and Fermat's Little Theorem to achieve a polynomial time complexity, typically O(k * log^3 n) for k iterations.
//   • Invariants: The number `n` being tested is an odd integer greater than 2.; The expression `n-1` is decomposed into `2^s * d`, where `d` is an odd integer.
//   • Tips: Pre-check for small prime divisors to quickly filter out many composite numbers.; Perform multiple iterations with different random bases to increase the certainty of primality.
//   • Pitfalls: The probabilistic version can yield false positives (strong probable primes) if too few bases are tested.; Incorrectly implementing modular exponentiation can lead to incorrect results or performance issues.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

public class Solution extends GuessGame {
    public int guessNumber(int n) {
        int low = 1, high = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int res = guess(mid);
            if (res == 0) {
                return mid;
            } else if (res < 0) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1; // This line should never be reached if input is valid           
    }
}
