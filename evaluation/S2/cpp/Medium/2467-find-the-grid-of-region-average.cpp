// Source: https://leetcode.com/problems/find-the-grid-of-region-average/   |   Difficulty: Medium
//
// Problem Description:
// You are given m x n grid image which represents a grayscale image, where image[i][j] represents a pixel with intensity in the range [0..255]. You are also given a non-negative integer threshold.
//
// Two pixels are adjacent if they share an edge.
//
// A region is a 3 x 3 subgrid where the absolute difference in intensity between any two adjacent pixels is less than or equal to threshold.
//
// All pixels in a region belong to that region, note that a pixel can belong to multiple regions.
//
// You need to calculate a m x n grid result, where result[i][j] is the average intensity of the regions to which image[i][j] belongs, rounded down to the nearest integer. If image[i][j] belongs to multiple regions, result[i][j] is the average of the rounded-down average intensities of these regions, rounded down to the nearest integer. If image[i][j] does not belong to any region, result[i][j] is equal to image[i][j].
//
// Return the grid result.
//
// Example:
// Input: image = [[5,6,7,10],[8,9,10,10],[11,12,13,10]], threshold = 3
//
// Output: [[9,9,9,9],[9,9,9,9],[9,9,9,9]]
//
// Explanation:
//
//
//
// There are two regions as illustrated above. The average intensity of the first region is 9, while the average intensity of the second region is 9.67 which is rounded down to 9. The average intensity of both of the regions is (9 + 9) / 2 = 9. As all the pixels belong to either region 1, region 2, or both of them, the intensity of every pixel in the result is 9.
//
// Please note that the rounded-down values are used when calculating the average of multiple regions, hence the calculation is done using 9 as the average intensity of region 2, not 9.67.
//
// Constraints:
// 3 <= n, m <= 500
// 	0 <= image[i][j] <= 255
// 	0 <= threshold <= 255
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        int m = image.size();
        int n = image[0].size();
        vector<vector<int>> result(m, vector<int>(n, 0));
        
        for (int i = 0; i < m - 2; ++i) {
            for (int j = 0; j < n - 2; ++j) {
                bool isRegion = true;
                for (int x = 0; x < 3 && isRegion; ++x) {
                    for (int y = 0; y < 3 && isRegion; ++y) {
                        if (x > 0 && abs(image[i + x][j + y] - image[i + x - 1][j + y]) > threshold) {
                            isRegion = false;
                        }
                        if (y > 0 && abs(image[i + x][j + y] - image[i + x][j + y - 1]) > threshold) {
                            isRegion = false;
                        }
                    }
                }
                if (isRegion) {
                    int sum = 0;
                    for (int x = 0; x < 3; ++x) {
                        for (int y = 0; y < 3; ++y) {
                            sum += image[i + x][j + y];
                        }
                    }
                    int avg = sum / 9;
                    for (int x = 0; x < 3; ++x) {
                        for (int y = 0; y < 3; ++y) {
                            result[i + x][j + y] += avg;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (result[i][j] == 0) {
                    result[i][j] = image[i][j];
                } else {
                    result[i][j] /= countRegions(image, threshold, i, j);
                }
            }
        }

        return result;          
    }
};
