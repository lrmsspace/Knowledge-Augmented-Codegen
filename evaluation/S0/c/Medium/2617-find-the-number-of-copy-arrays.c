// Source: https://leetcode.com/problems/find-the-number-of-copy-arrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array original of length n and a 2D array bounds of length n x 2, where bounds[i] = [ui, vi].
//
// You need to find the number of possible arrays copy of length n such that:
//
//
// 	(copy[i] - copy[i - 1]) == (original[i] - original[i - 1]) for 1 <= i <= n - 1.
// 	ui <= copy[i] <= vi for 0 <= i <= n - 1.
//
//
// Return the number of such arrays.
//
// Example:
// Input: original = [1,2,3,4], bounds = [[1,2],[2,3],[3,4],[4,5]]
//
// Output: 2
//
// Explanation:
//
// The possible arrays are:
//
//
// 	[1, 2, 3, 4]
// 	[2, 3, 4, 5]
//
// Constraints:
// 2 <= n == original.length <= 105
// 	1 <= original[i] <= 109
// 	bounds.length == n
// 	bounds[i].length == 2
// 	1 <= bounds[i][0] <= bounds[i][1] <= 109
//

int countArrays(int* original, int originalSize, int** bounds, int boundsSize, int* boundsColSize) {
    long long mod = 1e9 + 7;
    long long offset = 0;
    long long lower = bounds[0][0];
    long long upper = bounds[0][1];

    for (int i = 1; i < originalSize; i++) {
        offset += (long long)(original[i] - original[i - 1]);
        long long new_lower = bounds[i][0] - offset;
        long long new_upper = bounds[i][1] - offset;

        lower = (lower > new_lower) ? lower : new_lower;
        upper = (upper < new_upper) ? upper : new_upper;

        if (lower > upper) {
            return 0;
        }
    }

    return (int)((upper - lower + 1) % mod);        
}
