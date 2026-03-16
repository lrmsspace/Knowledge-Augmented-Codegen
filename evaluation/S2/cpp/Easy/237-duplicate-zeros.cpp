// Source: https://leetcode.com/problems/duplicate-zeros/   |   Difficulty: Easy
//
// Problem Description:
// Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.
//
// Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.
//
// Example:
// Input: arr = [1,0,2,3,0,4,5,0]
// Output: [1,0,0,2,3,0,0,4]
// Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 9
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
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int countZero = 0;

        // Count the number of zeros in the array
        for (int i = 0; i < n; ++i) {
            if (arr[i] == 0) {
                countZero++;
            }
        }

        // Start from the end of the array and shift elements to the right
        for (int i = n - 1; i >= 0; --i) {
            if (arr[i] == 0) {
                if (i + countZero < n) {
                    arr[i + countZero] = 0; // Duplicate zero
                }
                countZero--; // Decrease the count of zeros to duplicate
            }
            if (i + countZero < n) {
                arr[i + countZero] = arr[i]; // Shift element to the right
            }
        }           
    }
};
