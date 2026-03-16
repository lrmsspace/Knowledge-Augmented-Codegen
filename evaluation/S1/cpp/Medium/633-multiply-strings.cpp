// Source: https://leetcode.com/problems/multiply-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.
//
// Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
//
// Example:
// Input: num1 = "2", num2 = "3"
// Output: "6"
//
// Constraints:
// 1 <= num1.length, num2.length <= 200
// 	num1 and num2 consist of digits only.
// 	Both num1 and num2 do not contain any leading zero, except the number 0 itself.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Operations on polynomials and series (array, recursion)
//   • When to use: When you need to compute the product of two polynomials or formal power series, often represented by their coefficient arrays. This is useful for combining algebraic expressions or solving recurrence relations.
//   • Idea: This involves computing the coefficients of the product polynomial by convolving the coefficients of the input polynomials. Algorithms like Karatsuba's use a divide-and-conquer recursive approach to achieve better than naive quadratic time complexity.
//   • Invariants: Each recursive call correctly computes the product of its two input sub-polynomials; The base case for recursion (e.g., constant polynomials) is handled correctly
//   • Tips: Represent polynomials as arrays of coefficients; Pad shorter polynomials with zeros to match degrees
//   • Pitfalls: Forgetting to handle zero coefficients or different polynomial degrees; Naive O(N^2) multiplication can be too slow for large inputs
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string multiply(string num1, string num2) {
        int n = num1.size();
        int m = num2.size();
        vector<int> result(n + m, 0);

        // Multiply each digit of num1 with each digit of num2
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + result[i + j + 1];

                result[i + j + 1] = sum % 10; // Store the unit place
                result[i + j] += sum / 10;    // Carry over to the next position
            }
        }

        // Convert result vector to string, skipping leading zeros
        string product;
        for (int digit : result) {
            if (!(product.empty() && digit == 0)) { // Skip leading zeros
                product.push_back(digit + '0');
            }
        }

        return product.empty() ? "0" : product; // If product is empty, return "0"          
    }
};
