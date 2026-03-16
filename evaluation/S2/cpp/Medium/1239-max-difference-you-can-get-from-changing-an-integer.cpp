// Source: https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. You will apply the following steps to num two separate times:
//
//
// 	Pick a digit x (0 <= x <= 9).
// 	Pick another digit y (0 <= y <= 9). Note y can be equal to x.
// 	Replace all the occurrences of x in the decimal representation of num by y.
//
//
// Let a and b be the two results from applying the operation to num independently.
//
// Return the max difference between a and b.
//
// Note that neither a nor b may have any leading zeros, and must not be 0.
//
// Example:
// Input: num = 555
// Output: 888
// Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
// The second time pick x = 5 and y = 1 and store the new integer in b.
// We have now a = 999 and b = 111 and max difference = 888
//
// Constraints:
// 1 <= num <= 108
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
    int maxDiff(int num) {
        string numStr = to_string(num);
        string a = numStr, b = numStr;

        // For a, we want to maximize the number by replacing the first non-9 digit with 9
        for (char &c : a) {
            if (c != '9') {
                char oldChar = c;
                c = '9';
                break; // Only replace the first occurrence
            }
        }

        // For b, we want to minimize the number by replacing the first non-0 digit with 0
        for (char &c : b) {
            if (c != '0') {
                char oldChar = c;
                c = '0';
                break; // Only replace the first occurrence
            }
        }

        return stoi(a) - stoi(b);           
    }
};
