// Source: https://leetcode.com/problems/closest-divisors/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.
//
// Return the two integers in any order.
//
// Example:
// Input: num = 8
// Output: [3,3]
// Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.
//
// Constraints:
// 1 <= num <= 10^9
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* closestDivisors(int num, int* returnSize) {
    int target1 = num + 1;
    int target2 = num + 2;
    int *result = (int *)malloc(2 * sizeof(int));
    *returnSize = 2;

    int bestDiff = __INT_MAX__;
    int bestA = 0, bestB = 0;

    for (int target : (int[]){target1, target2}) {
        for (int i = (int)sqrt(target); i >= 1; --i) {
            if (target % i == 0) {
                int a = i;
                int b = target / i;
                int diff = b - a;
                if (diff < bestDiff) {
                    bestDiff = diff;
                    bestA = a;
                    bestB = b;
                }
                break; // No need to check smaller divisors
            }
        }
    }

    result[0] = bestA;
    result[1] = bestB;
    return result;      
}
