// Source: https://leetcode.com/problems/bag-of-tokens/   |   Difficulty: Medium
//
// Problem Description:
// You start with an initial power of power, an initial score of 0, and a bag of tokens given as an integer array tokens, where each tokens[i] denotes the value of tokeni.
//
// Your goal is to maximize the total score by strategically playing these tokens. In one move, you can play an unplayed token in one of the two ways (but not both for the same token):
//
//
// 	Face-up: If your current power is at least tokens[i], you may play tokeni, losing tokens[i] power and gaining 1 score.
// 	Face-down: If your current score is at least 1, you may play tokeni, gaining tokens[i] power and losing 1 score.
//
//
// Return the maximum possible score you can achieve after playing any number of tokens.
//
// Example:
// Input: tokens = [100], power = 50
//
// Output: 0
//
// Explanation: Since your score is 0 initially, you cannot play the token face-down. You also cannot play it face-up since your power (50) is less than tokens[0] (100).
//
// Constraints:
// 0 <= tokens.length <= 1000
// 	0 <= tokens[i], power < 104
//
// Helpful references (internal KB):
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Flows with demands (graph, binary-search-answer)
//   • When to use: Use when a problem involves finding a flow in a network where edges have both lower and upper capacity bounds, or nodes have supply/demand requirements, and an optimal value needs to be found.
//   • Idea: This technique transforms a network with lower and upper capacity bounds on edges (or node demands) into a standard max-flow problem. It often involves adding a new source and sink to handle demands, and then binary searching on the answer if an optimal value is sought, typically with O(MaxFlow * log(Range)) complexity.
//   • Invariants: The total flow out of the super source equals the total demand that needs to be satisfied.; For any node, the sum of incoming flow minus outgoing flow equals its net demand (0 for internal nodes in a circulation).
//   • Tips: Convert lower bounds to demands by adjusting capacities and adding a super source/sink.; A feasible flow exists if the max flow in the transformed network equals the total demand.
//   • Pitfalls: Incorrectly calculating residual capacities after demand satisfaction.; Forgetting to add a super source/sink for handling demands.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} tokens
 * @param {number} power
 * @return {number}
 */
var bagOfTokensScore = function(tokens, power) {
    tokens.sort((a, b) => a - b);
    let score = 0;
    let maxScore = 0;
    let left = 0;
    let right = tokens.length - 1;
    while (left <= right) {
        if (power >= tokens[left]) {
            power -= tokens[left];
            score++;
            maxScore = Math.max(maxScore, score);
            left++;
        } else if (score > 0) {
            power += tokens[right];
            score--;
            right--;
        } else {
            break;
        }
    }
    return maxScore;
};
