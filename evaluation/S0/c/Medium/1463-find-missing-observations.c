// Source: https://leetcode.com/problems/find-missing-observations/   |   Difficulty: Medium
//
// Problem Description:
// You have observations of n + m 6-sided dice rolls with each face numbered from 1 to 6. n of the observations went missing, and you only have the observations of m rolls. Fortunately, you have also calculated the average value of the n + m rolls.
//
// You are given an integer array rolls of length m where rolls[i] is the value of the ith observation. You are also given the two integers mean and n.
//
// Return an array of length n containing the missing observations such that the average value of the n + m rolls is exactly mean. If there are multiple valid answers, return any of them. If no such array exists, return an empty array.
//
// The average value of a set of k numbers is the sum of the numbers divided by k.
//
// Note that mean is an integer, so the sum of the n + m rolls should be divisible by n + m.
//
// Example:
// Input: rolls = [3,2,4,3], mean = 4, n = 2
// Output: [6,6]
// Explanation: The mean of all n + m rolls is (3 + 2 + 4 + 3 + 6 + 6) / 6 = 4.
//
// Constraints:
// m == rolls.length
// 	1 <= n, m <= 105
// 	1 <= rolls[i], mean <= 6
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* missingRolls(int* rolls, int rollsSize, int mean, int n, int* returnSize) {
    int total = mean * (rollsSize + n);
    int sum_rolls = 0;
    for (int i = 0; i < rollsSize; i++) {
        sum_rolls += rolls[i];
    }
    int missing_sum = total - sum_rolls;

    if (missing_sum < n || missing_sum > 6 * n) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc(n * sizeof(int));
    *returnSize = n;

    int base_value = missing_sum / n;
    int remainder = missing_sum % n;

    for (int i = 0; i < n; i++) {
        result[i] = base_value + (i < remainder ? 1 : 0);
    }

    return result;      
}
