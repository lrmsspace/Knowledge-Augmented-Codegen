// Source: https://leetcode.com/problems/tallest-billboard/   |   Difficulty: Hard
//
// Problem Description:
// You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.
//
// You are given a collection of rods that can be welded together. For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.
//
// Return the largest possible height of your billboard installation. If you cannot support the billboard, return 0.
//
// Example:
// Input: rods = [1,2,3,6]
// Output: 6
// Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
//
// Constraints:
// 1 <= rods.length <= 20
// 	1 <= rods[i] <= 1000
// 	sum(rods[i]) <= 5000
//

int tallestBillboard(int* rods, int rodsSize) {
    int offset = 5000;
    int dpSize = 10001; /* -5000 to 5000 */
    int *dp = (int*)malloc(dpSize * sizeof(int));
    if (!dp) return 0;
    for (int i = 0; i < dpSize; i++) dp[i] = -1;
    dp[offset] = 0; /* base case: diff=0, height=0 */

    for (int i = 0; i < rodsSize; i++) {
        int rod = rods[i];
        int *newDp = (int*)malloc(dpSize * sizeof(int));
        if (!newDp) {
            free(dp);
            return 0;
        }
        memcpy(newDp, dp, dpSize * sizeof(int));
        for (int diff = -5000; diff <= 5000; diff++) {
            if (dp[diff + offset] < 0) continue;
            int height = dp[diff + offset];

            /* Option 1: Add rod to the left side */
            int newDiff1 = diff + rod;
            if (newDiff1 >= -5000 && newDiff1 <= 5000) {
                if (newDp[newDiff1 + offset] < height) {
                    newDp[newDiff1 + offset] = height;
                }
            }

            /* Option 2: Add rod to the right side */
            int newDiff2 = diff - rod;
            if (newDiff2 >= -5000 && newDiff2 <= 5000) {
                int newHeight = height + rod;
                if (newDp[newDiff2 + offset] < newHeight) {
                    newDp[newDiff2 + offset] = newHeight;
                }
            }
        }
        free(dp);
        dp = newDp;
    }

    int result = dp[offset] < 0 ? 0 : dp[offset];
    free(dp);
    return result;      
}
