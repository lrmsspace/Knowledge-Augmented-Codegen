// Source: https://leetcode.com/problems/poor-pigs/   |   Difficulty: Hard
//
// Problem Description:
// There are buckets buckets of liquid, where exactly one of the buckets is poisonous. To figure out which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die or not. Unfortunately, you only have minutesToTest minutes to determine which bucket is poisonous.
//
// You can feed the pigs according to these steps:
//
//
// 	Choose some live pigs to feed.
// 	For each pig, choose which buckets to feed it. The pig will consume all the chosen buckets simultaneously and will take no time. Each pig can feed from any number of buckets, and each bucket can be fed from by any number of pigs.
// 	Wait for minutesToDie minutes. You may not feed any other pigs during this time.
// 	After minutesToDie minutes have passed, any pigs that have been fed the poisonous bucket will die, and all others will survive.
// 	Repeat this process until you run out of time.
//
//
// Given buckets, minutesToDie, and minutesToTest, return the minimum number of pigs needed to figure out which bucket is poisonous within the allotted time.
//
// Example:
// Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
// Output: 2
// Explanation: We can determine the poisonous bucket as follows:
// At time 0, feed the first pig buckets 1 and 2, and feed the second pig buckets 2 and 3.
// At time 15, there are 4 possible outcomes:
// - If only the first pig dies, then bucket 1 must be poisonous.
// - If only the second pig dies, then bucket 3 must be poisonous.
// - If both pigs die, then bucket 2 must be poisonous.
// - If neither pig dies, then bucket 4 must be poisonous.
//
// Constraints:
// 1 <= buckets <= 1000
// 	1 <= minutesToDie <= minutesToTest <= 100
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Discrete Logarithm (array, number, binary-search, mod-exp)
//   • When to use: Use when solving for the exponent 'x' in the modular equation a^x = b (mod m), especially when 'm' is large and a and m are coprime. It's suitable for finding a solution within O(sqrt(m) log m) time.
//   • Idea: This algorithm, also known as Baby-step Giant-step, finds the smallest non-negative integer 'x' satisfying a^x = b (mod m) using a meet-in-the-middle approach. It achieves a time complexity of O(sqrt(m) log m).
//   • Invariants: The map stores (a^q mod m, q) for all baby steps q in [0, n-1].; For each giant step p, a^(np) mod m is correctly computed.
//   • Tips: Choose 'n' as ceil(sqrt(m)) for balanced steps.; Use a hash map to store baby steps for O(1) average lookup.
//   • Pitfalls: Incorrect choice of 'n' can lead to suboptimal time complexity.; Failure to check if 'a' and 'm' are coprime may yield no solution or incorrect results.
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
    int pigs = 0;
    int states = minutesToTest / minutesToDie + 1; // Number of states a pig can represent
    while (states * pigs < buckets) {
        pigs++;
    }
    return pigs;        
}
