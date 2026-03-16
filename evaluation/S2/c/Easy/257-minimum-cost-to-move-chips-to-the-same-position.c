// Source: https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/   |   Difficulty: Easy
//
// Problem Description:
// We have n chips, where the position of the ith chip is position[i].
//
// We need to move all the chips to the same position. In one step, we can change the position of the ith chip from position[i] to:
//
//
// 	position[i] + 2 or position[i] - 2 with cost = 0.
// 	position[i] + 1 or position[i] - 1 with cost = 1.
//
//
// Return the minimum cost needed to move all the chips to the same position.
//
// Example:
// Input: position = [1,2,3]
// Output: 1
// Explanation: First step: Move the chip at position 3 to position 1 with cost = 0.
// Second step: Move the chip at position 2 to position 1 with cost = 1.
// Total cost is 1.
//
// Constraints:
// 1 <= position.length <= 100
// 	1 <= position[i] <= 10^9
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minCostToMoveChips(int* position, int positionSize) {
    int evenCount = 0;
    int oddCount = 0;

    for (int i = 0; i < positionSize; i++) {
        if (position[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    return evenCount < oddCount ? evenCount : oddCount;     
}
