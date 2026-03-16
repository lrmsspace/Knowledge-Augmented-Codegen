// Source: https://leetcode.com/problems/reducing-dishes/   |   Difficulty: Hard
//
// Problem Description:
// A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.
//
// Like-time coefficient of a dish is defined as the time taken to cook that dish including previous dishes multiplied by its satisfaction level i.e. time[i] * satisfaction[i].
//
// Return the maximum sum of like-time coefficient that the chef can obtain after preparing some amount of dishes.
//
// Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.
//
// Example:
// Input: satisfaction = [-1,-8,0,5,-9]
// Output: 14
// Explanation: After Removing the second and last dish, the maximum total like-time coefficient will be equal to (-1*1 + 0*2 + 5*3 = 14).
// Each dish is prepared in one unit of time.
//
// Constraints:
// n == satisfaction.length
// 	1 <= n <= 500
// 	-1000 <= satisfaction[i] <= 1000
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

int maxSatisfaction(int* satisfaction, int satisfactionSize) {
    // Sort the satisfaction array in non-decreasing order
    for (int i = 0; i < satisfactionSize - 1; i++) {
        for (int j = 0; j < satisfactionSize - i - 1; j++) {
            if (satisfaction[j] > satisfaction[j + 1]) {
                int temp = satisfaction[j];
                satisfaction[j] = satisfaction[j + 1];
                satisfaction[j + 1] = temp;
            }
        }
    }

    int maxCoefficient = 0;
    int currentCoefficient = 0;

    // Calculate the like-time coefficient by iterating from the end of the sorted array
    for (int i = satisfactionSize - 1; i >= 0; i--) {
        currentCoefficient += satisfaction[i];
        if (currentCoefficient > maxCoefficient) {
            maxCoefficient = currentCoefficient;
        }
    }

    return maxCoefficient;      
}
