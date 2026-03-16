// Source: https://leetcode.com/problems/make-array-strictly-increasing/   |   Difficulty: Hard
//
// Problem Description:
// Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero) needed to make arr1 strictly increasing.
//
// In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do the assignment arr1[i] = arr2[j].
//
// If there is no way to make arr1 strictly increasing, return -1.
//
// Example:
// Input: arr1 = [1,5,3,6,7], arr2 = [1,3,2,4]
// Output: 1
// Explanation: Replace 5 with 2, then arr1 = [1, 2, 3, 6, 7].
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 2000
// 	0 <= arr1[i], arr2[i] <= 10^9
//

class Solution {
    public int makeArrayIncreasing(int[] arr1, int[] arr2) {
        TreeSet<Integer> set = new TreeSet<>();
        for (int num : arr2) {
            set.add(num);
        }

        int n = arr1.length;
        int m = set.size();
        Integer[] sortedArr2 = set.toArray(new Integer[m]);

        int[][] dp = new int[n][m + 1];
        for (int i = 0; i < n; i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE);
        }

        dp[0][m] = 0; // No replacement
        for (int j = 0; j < m; j++) { // Replacement
            dp[0][j] = 1;
        }

        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                // No replacement
                if (dp[i - 1][j] != Integer.MAX_VALUE && (j == m || arr1[i] > (j == m ? arr1[i - 1] : sortedArr2[j]))) {
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][j]);
                }

                // Replacement
                for (int k = 0; k < m; k++) {
                    if (dp[i - 1][k] != Integer.MAX_VALUE && sortedArr2[k] < sortedArr2[j]) {
                        dp[i][j] = Math.min(dp[i][j], dp[i - 1][k] + 1);
                    }
                }
            }
        }

        int result = Integer.MAX_VALUE;
        for (int j = 0; j <= m; j++) {
            result = Math.min(result, dp[n - 1][j]);
        }

        return result == Integer.MAX_VALUE ? -1 : result;                   
    }
}
