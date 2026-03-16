// Source: https://leetcode.com/problems/pascals-triangle-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.
//
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
//
// Example:
// Input: rowIndex = 3
// Output: [1,3,3,1]
//
// Constraints:
// 0 <= rowIndex <= 33
//
//
//  
// Follow up: Could you optimize your algorithm to use only O(rowIndex) extra space?
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
    vector<int> getRow(int rowIndex) {
        vector<int> row(rowIndex + 1, 1);
        for (int i = 2; i <= rowIndex; ++i) {
            for (int j = i - 1; j > 0; --j) {
                row[j] += row[j - 1];
            }
        }
        return row;         
    }
};
