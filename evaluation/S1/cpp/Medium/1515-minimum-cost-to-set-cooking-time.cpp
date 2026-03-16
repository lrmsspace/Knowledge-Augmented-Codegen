// Source: https://leetcode.com/problems/minimum-cost-to-set-cooking-time/   |   Difficulty: Medium
//
// Problem Description:
// A generic microwave supports cooking times for:
//
//
// 	at least 1 second.
// 	at most 99 minutes and 99 seconds.
//
//
// To set the cooking time, you push at most four digits. The microwave normalizes what you push as four digits by prepending zeroes. It interprets the first two digits as the minutes and the last two digits as the seconds. It then adds them up as the cooking time. For example,
//
//
// 	You push 9 5 4 (three digits). It is normalized as 0954 and interpreted as 9 minutes and 54 seconds.
// 	You push 0 0 0 8 (four digits). It is interpreted as 0 minutes and 8 seconds.
// 	You push 8 0 9 0. It is interpreted as 80 minutes and 90 seconds.
// 	You push 8 1 3 0. It is interpreted as 81 minutes and 30 seconds.
//
//
// You are given integers startAt, moveCost, pushCost, and targetSeconds. Initially, your finger is on the digit startAt. Moving the finger above any specific digit costs moveCost units of fatigue. Pushing the digit below the finger once costs pushCost units of fatigue.
//
// There can be multiple ways to set the microwave to cook for targetSeconds seconds but you are interested in the way with the minimum cost.
//
// Return the minimum cost to set targetSeconds seconds of cooking time.
//
// Remember that one minute consists of 60 seconds.
//
// Example:
// Input: startAt = 1, moveCost = 2, pushCost = 1, targetSeconds = 600
// Output: 6
// Explanation: The following are the possible ways to set the cooking time.
// - 1 0 0 0, interpreted as 10 minutes and 0 seconds.
//   The finger is already on digit 1, pushes 1 (with cost 1), moves to 0 (with cost 2), pushes 0 (with cost 1), pushes 0 (with cost 1), and pushes 0 (with cost 1).
//   The cost is: 1 + 2 + 1 + 1 + 1 = 6. This is the minimum cost.
// - 0 9 6 0, interpreted as 9 minutes and 60 seconds. That is also 600 seconds.
//   The finger moves to 0 (with cost 2), pushes 0 (with cost 1), moves to 9 (with cost 2), pushes 9 (with cost 1), moves to 6 (with cost 2), pushes 6 (with cost 1), moves to 0 (with cost 2), and pushes 0 (with cost 1).
//   The cost is: 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 = 12.
// - 9 6 0, normalized as 0960 and interpreted as 9 minutes and 60 seconds.
//   The finger moves to 9 (with cost 2), pushes 9 (with cost 1), moves to 6 (with cost 2), pushes 6 (with cost 1), moves to 0 (with cost 2), and pushes 0 (with cost 1).
//   The cost is: 2 + 1 + 2 + 1 + 2 + 1 = 9.
//
// Constraints:
// 0 <= startAt <= 9
// 	1 <= moveCost, pushCost <= 105
// 	1 <= targetSeconds <= 6039
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {
        int minCost = INT32_MAX;

        // Try all possible (minutes, seconds) pairs that sum to targetSeconds
        for (int minutes = 0; minutes <= 99; ++minutes) {
            int seconds = targetSeconds - minutes * 60;
            if (seconds < 0 || seconds > 99) continue;

            // Construct the digit sequence
            int digits[4] = {0, 0, 0, 0};
            if (minutes >= 10) {
                digits[0] = minutes / 10;
                digits[1] = minutes % 10;
                digits[2] = seconds / 10;
                digits[3] = seconds % 10;
            } else {
                digits[0] = 0;
                digits[1] = minutes;
                digits[2] = seconds / 10;
                digits[3] = seconds % 10;
            }

            // Find the first non-zero digit to start pushing from
            int startIdx = 0;
            while (startIdx < 4 && digits[startIdx] == 0) {
                ++startIdx;
            }
            if (startIdx == 4) startIdx = 3; // If all are zero, push the last zero

            // Calculate cost
            int cost = 0;
            int currentPos = startAt;

            for (int i = startIdx; i < 4; ++i) {
                if (digits[i] != currentPos) {
                    cost += moveCost;
                    currentPos = digits[i];
                }
                cost += pushCost;
            }

            minCost = (cost < minCost) ? cost : minCost;
        }

        return minCost;         
    }
};
