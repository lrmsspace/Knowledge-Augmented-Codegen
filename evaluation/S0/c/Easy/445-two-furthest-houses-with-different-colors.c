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

int maxDistance(int* colors, int colorsSize) {
    int max_dist = 0;
    for (int i = 0; i < colorsSize; i++) {
        for (int j = colorsSize - 1; j > i; j--) {
            if (colors[i] != colors[j]) {
                int dist = j - i;
                if (dist > max_dist) {
                    max_dist = dist;
                }
                break; // No need to check smaller j for this i
            }
        }
    }
    return max_dist;        
}
