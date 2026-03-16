// Source: https://leetcode.com/problems/minimum-cost-to-cut-a-stick/   |   Difficulty: Hard
//
// Problem Description:
// Given a wooden stick of length n units. The stick is labelled from 0 to n. For example, a stick of length 6 is labelled as follows:
//
// Given an integer array cuts where cuts[i] denotes a position you should perform a cut at.
//
// You should perform the cuts in order, you can change the order of the cuts as you wish.
//
// The cost of one cut is the length of the stick to be cut, the total cost is the sum of costs of all cuts. When you cut a stick, it will be split into two smaller sticks (i.e. the sum of their lengths is the length of the stick before the cut). Please refer to the first example for a better explanation.
//
// Return the minimum total cost of the cuts.
//
// Example:
// Input: n = 7, cuts = [1,3,4,5]
// Output: 16
// Explanation: Using cuts order = [1, 3, 4, 5] as in the input leads to the following scenario:
//
// The first cut is done to a rod of length 7 so the cost is 7. The second cut is done to a rod of length 6 (i.e. the second part of the first cut), the third is done to a rod of length 4 and the last cut is to a rod of length 3. The total cost is 7 + 6 + 4 + 3 = 20.
// Rearranging the cuts to be [3, 5, 1, 4] for example will lead to a scenario with total cost = 16 (as shown in the example photo 7 + 4 + 3 + 2 = 16).
//
// Constraints:
// 2 <= n <= 106
// 	1 <= cuts.length <= min(n - 1, 100)
// 	1 <= cuts[i] <= n - 1
// 	All the integers in cuts array are distinct.
//

int minCost(int n, int* cuts, int cutsSize) {
    int m = cutsSize + 2;
    int *allCuts = (int*)malloc(m * sizeof(int));
    if (!allCuts) return 0; /* allocation failure */
    allCuts[0] = 0;
    memcpy(&allCuts[1], cuts, cutsSize * sizeof(int));
    allCuts[m - 1] = n;
    qsort(allCuts, m, sizeof(int), cmpInt);

    int **dp = (int**)malloc(m * sizeof(int*));
    if (!dp) { free(allCuts); return 0; } /* allocation failure */
    for (int i = 0; i < m; ++i) {
        dp[i] = (int*)calloc(m, sizeof(int));
        if (!dp[i]) {
            for (int j = 0; j < i; ++j) free(dp[j]);
            free(dp); free(allCuts); return 0; /* allocation failure */
        }
    }

    for (int length = 2; length < m; ++length) {
        for (int i = 0; i + length < m; ++i) {
            int j = i + length;
            dp[i][j] = 1e9;
            for (int k = i + 1; k < j; ++k) {
                int cost = allCuts[j] - allCuts[i] + dp[i][k] + dp[k][j];
                if (cost < dp[i][j]) dp[i][j] = cost;
            }
        }
    }

    int result = dp[0][m - 1];
    for (int i = 0; i < m; ++i) free(dp[i]);
    free(dp);
    free(allCuts);
    return result;      
}
