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
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Bit manipulation (number, simulation)
//   • When to use: Use when operations on individual bits of an integer are required, for optimizing arithmetic with powers of two, or for efficient management of boolean flags.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators and shifts. These operations typically have O(1) time complexity as they are hardware-level instructions.
//   • Invariants: The total number of bits representing the integer remains constant for fixed-width types.; Applying `n & (1 << k)` isolates the k-th bit, setting all other bits to zero.
//   • Tips: Use `&` with `(1 << k)` to check if the k-th bit is set.; Use `|` with `(1 << k)` to set the k-th bit.
//   • Pitfalls: Be aware of integer overflow when performing large left shifts.; Understand the difference between arithmetic and logical right shifts, especially for signed numbers.
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
        auto changeNum = [](int num, int x, int y) -> int {
            string s = to_string(num);
            for (char &ch : s) {
                if (ch - '0' == x) {
                    ch = '0' + y;
                }
            }
            // Remove leading zeros if any
            size_t pos = s.find_first_not_of('0');
            if (pos != string::npos) {
                s = s.substr(pos);
            } else {
                s = "0"; // If all were zeros
            }
            return stoi(s);
        };

        // For maximum number, replace first non-9 digit with 9
        string s = to_string(num);
        int x_max = -1;
        for (char ch : s) {
            if (ch != '9') {
                x_max = ch - '0';
                break;
            }
        }
        int max_num = (x_max == -1) ? num : changeNum(num, x_max, 9);

        // For minimum number, replace first digit (if not 1) with 1, else replace first non-0, non-1 digit with 0
        int x_min = -1;
        if (s[0] != '1') {
            x_min = s[0] - '0';
        } else {
            for (size_t i = 1; i < s.size(); ++i) {
                if (s[i] != '0' && s[i] != '1') {
                    x_min = s[i] - '0';
                    break;
                }
            }
        }
        int min_num = (x_min == -1) ? num : changeNum(num, x_min, (s[0] != '1') ? 1 : 0);

        return max_num - min_num;           
    }
};
