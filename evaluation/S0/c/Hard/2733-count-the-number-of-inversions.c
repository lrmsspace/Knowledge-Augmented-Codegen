// Source: https://leetcode.com/problems/count-the-number-of-inversions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and a 2D array requirements, where requirements[i] = [endi, cnti] represents the end index and the inversion count of each requirement.
//
// A pair of indices (i, j) from an integer array nums is called an inversion if:
//
//
// 	i < j and nums[i] > nums[j]
//
//
// Return the number of permutations perm of [0, 1, 2, ..., n - 1] such that for all requirements[i], perm[0..endi] has exactly cnti inversions.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, requirements = [[2,2],[0,0]]
//
// Output: 2
//
// Explanation:
//
// The two permutations are:
//
//
// 	[2, 0, 1]
//
// 	
// 		Prefix [2, 0, 1] has inversions (0, 1) and (0, 2).
// 		Prefix [2] has 0 inversions.
// 	
// 	
// 	[1, 2, 0]
// 	
// 		Prefix [1, 2, 0] has inversions (0, 2) and (1, 2).
// 		Prefix [1] has 0 inversions.
//
// Constraints:
// 2 <= n <= 300
// 	1 <= requirements.length <= n
// 	requirements[i] = [endi, cnti]
// 	0 <= endi <= n - 1
// 	0 <= cnti <= 400
// 	The input is generated such that there is at least one i such that endi == n - 1.
// 	The input is generated such that all endi are unique.
//

int numberOfPermutations(int n, int** requirements, int requirementsSize, int* requirementsColSize) {
    const int MOD = 1000000007;

    // Sort requirements by endi
    int compare(const void* a, const void* b) {
        return ((int*)a)[0] - ((int*)b)[0];
    }
    qsort(requirements, requirementsSize, sizeof(int*), compare);

    // DP array
    int dp[n + 1][401];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    int reqIndex = 0;
    for (int i = 1; i <= n; ++i) {
        int endi = requirements[reqIndex][0];
        int cnti = requirements[reqIndex][1];

        for (int j = 0; j <= 400; ++j) {
            dp[i][j] = dp[i - 1][j]; // Not placing new number

            if (j >= i - 1) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - (i - 1)]) % MOD; // Placing new number at the beginning
            }

            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD; // Cumulative sum
            }
        }

        if (i - 1 == endi) {
            // Filter dp for current requirement
            for (int j = 0; j <= 400; ++j) {
                if (j != cnti) {
                    dp[i][j] = 0;
                }
            }
            reqIndex++;
        }
    }

    return dp[n][requirements[requirementsSize - 1][1]];
}
