// Source: https://leetcode.com/problems/flipping-an-image/   |   Difficulty: Easy
//
// Problem Description:
// Given an n x n binary matrix image, flip the image horizontally, then invert it, and return the resulting image.
//
// To flip an image horizontally means that each row of the image is reversed.
//
//
// 	For example, flipping [1,1,0] horizontally results in [0,1,1].
//
//
// To invert an image means that each 0 is replaced by 1, and each 1 is replaced by 0.
//
//
// 	For example, inverting [0,1,1] results in [1,0,0].
//
// Example:
// Input: image = [[1,1,0],[1,0,1],[0,0,0]]
// Output: [[1,0,0],[0,1,0],[1,1,1]]
// Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
// Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]
//
// Constraints:
// n == image.length
// 	n == image[i].length
// 	1 <= n <= 20
// 	images[i][j] is either 0 or 1.
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
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
        int n = image.size();
        for (int i = 0; i < n; ++i) {
            // Flip the row horizontally
            reverse(image[i].begin(), image[i].end());
            // Invert the row
            for (int j = 0; j < n; ++j) {
                image[i][j] = 1 - image[i][j]; // Invert 0 to 1 and 1 to 0
            }
        }
        return image;           
    }
};
