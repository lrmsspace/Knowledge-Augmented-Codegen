// Source: https://leetcode.com/problems/maximum-number-of-robots-within-budget/   |   Difficulty: Hard
//
// Problem Description:
// You have n robots. You are given two 0-indexed integer arrays, chargeTimes and runningCosts, both of length n. The ith robot costs chargeTimes[i] units to charge and costs runningCosts[i] units to run. You are also given an integer budget.
//
// The total cost of running k chosen robots is equal to max(chargeTimes) + k * sum(runningCosts), where max(chargeTimes) is the largest charge cost among the k robots and sum(runningCosts) is the sum of running costs among the k robots.
//
// Return the maximum number of consecutive robots you can run such that the total cost does not exceed budget.
//
// Example:
// Input: chargeTimes = [3,6,1,3,4], runningCosts = [2,1,3,4,5], budget = 25
// Output: 3
// Explanation: 
// It is possible to run all individual and consecutive pairs of robots within budget.
// To obtain answer 3, consider the first 3 robots. The total cost will be max(3,6,1) + 3 * sum(2,1,3) = 6 + 3 * 6 = 24 which is less than 25.
// It can be shown that it is not possible to run more than 3 consecutive robots within budget, so we return 3.
//
// Constraints:
// chargeTimes.length == runningCosts.length == n
// 	1 <= n <= 5 * 104
// 	1 <= chargeTimes[i], runningCosts[i] <= 105
// 	1 <= budget <= 1015
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

int maximumRobots(int* chargeTimes, int chargeTimesSize, int* runningCosts, int runningCostsSize, long long budget) {
    int left = 0, right = 0;
    long long runningCostSum = 0;
    int maxChargeTime = 0;
    int maxRobots = 0;

    while (right < chargeTimesSize) {
        // Update the running cost sum and max charge time for the current window
        runningCostSum += runningCosts[right];
        if (chargeTimes[right] > maxChargeTime) {
            maxChargeTime = chargeTimes[right];
        }

        // Calculate the total cost for the current window
        long long totalCost = maxChargeTime + (long long)(right - left + 1) * runningCostSum;

        // If the total cost exceeds the budget, shrink the window from the left
        while (totalCost > budget && left <= right) {
            runningCostSum -= runningCosts[left];
            if (chargeTimes[left] == maxChargeTime) {
                // Recalculate max charge time in the new window
                maxChargeTime = 0;
                for (int i = left + 1; i <= right; i++) {
                    if (chargeTimes[i] > maxChargeTime) {
                        maxChargeTime = chargeTimes[i];
                    }
                }
            }
            left++;
            totalCost = maxChargeTime + (long long)(right - left + 1) * runningCostSum;
        }

        // Update the maximum number of robots that can be run within budget
        if (totalCost <= budget) {
            int currentRobots = right - left + 1;
            if (currentRobots > maxRobots) {
                maxRobots = currentRobots;
            }
        }

        right++;
    }

    return maxRobots;       
}
