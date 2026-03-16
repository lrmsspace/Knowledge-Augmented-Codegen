// Source: https://leetcode.com/problems/painting-a-grid-with-three-different-colors/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.
//
// Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: m = 1, n = 1
// Output: 3
// Explanation: The three possible colorings are shown in the image above.
//
// Constraints:
// 1 <= m <= 5
// 	1 <= n <= 1000
//

int colorTheGrid(int m, int n) {
    const int MOD = 1000000007;
    int maxState = 1;
    for (int i = 0; i < m; i++) maxState *= 3;

    int *validStates = (int*)malloc(maxState * sizeof(int));
    int validCount = 0;
    for (int state = 0; state < maxState; state++) {
        int prevColor = -1;
        int temp = state;
        int isValid = 1;
        for (int i = 0; i < m; i++) {
            int color = temp % 3;
            if (color == prevColor) {
                isValid = 0;
                break;
            }
            prevColor = color;
            temp /= 3;
        }
        if (isValid) {
            validStates[validCount++] = state;
        }
    }

    long *dpPrev = (long*)calloc(validCount, sizeof(long));
    long *dpCurr = (long*)calloc(validCount, sizeof(long));
    for (int i = 0; i < validCount; i++) {
        dpPrev[i] = 1;
    }

    for (int col = 1; col < n; col++) {
        for (int i = 0; i < validCount; i++) {
            dpCurr[i] = 0;
            for (int j = 0; j < validCount; j++) {
                int stateA = validStates[i];
                int stateB = validStates[j];
                int tempA = stateA;
                int tempB = stateB;
                int isCompatible = 1;
                for (int k = 0; k < m; k++) {
                    int colorA = tempA % 3;
                    int colorB = tempB % 3;
                    if (colorA == colorB) {
                        isCompatible = 0;
                        break;
                    }
                    tempA /= 3;
                    tempB /= 3;
                }
                if (isCompatible) {
                    dpCurr[i] = (dpCurr[i] + dpPrev[j]) % MOD;
                }
            }
        }
        long *temp = dpPrev;
        dpPrev = dpCurr;
        dpCurr = temp;
    }

    long result = 0;
    for (int i = 0; i < validCount; i++) {    
        result = (result + dpPrev[i]) % MOD;
    }
    free(validStates);
    free(dpPrev);
    free(dpCurr);
    return (int)result;  
}
