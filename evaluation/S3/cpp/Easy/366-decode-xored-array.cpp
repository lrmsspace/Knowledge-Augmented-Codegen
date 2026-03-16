// Source: https://leetcode.com/problems/decode-xored-array/   |   Difficulty: Easy
//
// Problem Description:
// There is a hidden integer array arr that consists of n non-negative integers.
//
// It was encoded into another integer array encoded of length n - 1, such that encoded[i] = arr[i] XOR arr[i + 1]. For example, if arr = [1,0,2,1], then encoded = [1,2,3].
//
// You are given the encoded array. You are also given an integer first, that is the first element of arr, i.e. arr[0].
//
// Return the original array arr. It can be proved that the answer exists and is unique.
//
// Example:
// Input: encoded = [1,2,3], first = 1
// Output: [1,0,2,1]
// Explanation: If arr = [1,0,2,1], then first = 1 and encoded = [1 XOR 0, 0 XOR 2, 2 XOR 1] = [1,2,3]
//
// Constraints:
// 2 <= n <= 104
// 	encoded.length == n - 1
// 	0 <= encoded[i] <= 105
// 	0 <= first <= 105
//
// Helpful references (internal KB):
// - Gray code (number, simulation)
//   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
//   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
//   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
//   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
//   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
// - Gray code (number, prefix-xor)
//   • When to use: Use when a sequence of binary numbers is needed where successive values differ by only one bit. This is useful for error detection in digital systems or position encoders.
//   • Idea: Gray code is a binary numeral system where two successive values differ in only one bit position. Conversion from a binary number `n` to its Gray code `G(n)` is `n ^ (n >> 1)`, and the inverse operation can also be performed efficiently in O(log N) time.
//   • Invariants: For binary to Gray: The resulting Gray code `G(n)` differs from `n` by exactly one bit for each `n`.; For inverse Gray to binary: The variable `n` accumulates the correct binary value from MSB to LSB.
//   • Tips: Understand the core `n ^ (n >> 1)` transformation for binary to Gray.; The inverse Gray code conversion involves iteratively XORing with right-shifted values.
//   • Pitfalls: Confusing Gray code with standard binary representation.; Incorrectly implementing the iterative inverse transformation logic.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        int n = encoded.size() + 1;
        vector<int> arr(n);
        arr[0] = first;
        for (int i = 1; i < n; ++i) {
            arr[i] = arr[i - 1] ^ encoded[i - 1];
        }
        return arr;         
    }
};
