// Source: https://leetcode.com/problems/shortest-impossible-sequence-of-rolls/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array rolls of length n and an integer k. You roll a k sided dice numbered from 1 to k, n times, where the result of the ith roll is rolls[i].
//
// Return the length of the shortest sequence of rolls so that there's no such subsequence in rolls.
//
// A sequence of rolls of length len is the result of rolling a k sided dice len times.
//
// Example:
// Input: rolls = [4,2,1,2,3,3,2,4,1], k = 4
// Output: 3
// Explanation: Every sequence of rolls of length 1, [1], [2], [3], [4], can be taken from rolls.
// Every sequence of rolls of length 2, [1, 1], [1, 2], ..., [4, 4], can be taken from rolls.
// The sequence [1, 4, 2] cannot be taken from rolls, so we return 3.
// Note that there are other sequences that cannot be taken from rolls.
//
// Constraints:
// n == rolls.length
// 	1 <= n <= 105
// 	1 <= rolls[i] <= k <= 105
//

int shortestSequence(int* rolls, int rollsSize, int k) {
    int count = 0;
    int *seen = (int*)calloc(k + 1, sizeof(int));
    if (!seen) return 0; /* allocation failure */

    for (int i = 0; i < rollsSize; ++i) {
        if (seen[rolls[i]] == 0) {
            seen[rolls[i]] = 1;
            count++;
            if (count == k) {
                count = 0;
                memset(seen, 0, (k + 1) * sizeof(int));
            }
        }
    }

    free(seen);
    return count == 0 ? (rollsSize / k) : (rollsSize / k + 1);      
}
