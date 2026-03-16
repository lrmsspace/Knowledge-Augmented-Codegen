// Source: https://leetcode.com/problems/two-furthest-houses-with-different-colors/   |   Difficulty: Easy
//
// Problem Description:
// There are n houses evenly lined up on the street, and each house is beautifully painted. You are given a 0-indexed integer array colors of length n, where colors[i] represents the color of the ith house.
//
// Return the maximum distance between two houses with different colors.
//
// The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute value of x.
//
// Example:
// Input: colors = [1,1,1,6,1,1,1]
// Output: 3
// Explanation: In the above image, color 1 is blue, and color 6 is red.
// The furthest two houses with different colors are house 0 and house 3.
// House 0 has color 1, and house 3 has color 6. The distance between them is abs(0 - 3) = 3.
// Note that houses 3 and 6 can also produce the optimal answer.
//
// Constraints:
// n == colors.length
// 	2 <= n <= 100
// 	0 <= colors[i] <= 100
// 	Test data are generated such that at least two houses have different colors.
//

class Solution {
    public int maxDistance(int[] colors) {
        int maxDist = 0;
        int n = colors.length;

        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j > i; j--) {
                if (colors[i] != colors[j]) {
                    maxDist = Math.max(maxDist, j - i);
                    break; // No need to check further j's for this i
                }
            }
        }

        return maxDist;         
    }
}
