// Source: https://leetcode.com/problems/check-if-n-and-its-double-exist/   |   Difficulty: Easy
//
// Problem Description:
// Given an array arr of integers, check if there exist two indices i and j such that :
//
//
// 	i != j
// 	0 <= i, j < arr.length
// 	arr[i] == 2 * arr[j]
//
// Example:
// Input: arr = [10,2,5,3]
// Output: true
// Explanation: For i = 0 and j = 2, arr[i] == 10 == 2 * 5 == 2 * arr[j]
//
// Constraints:
// 2 <= arr.length <= 500
// 	-103 <= arr[i] <= 103
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
    bool checkIfExist(vector<int>& arr) {
        unordered_set<int> seen;
        for (int num : arr) {
            if (seen.count(num * 2) || (num % 2 == 0 && seen.count(num / 2))) {
                return true;
            }
            seen.insert(num);
        }
        return false;           
    }
};
