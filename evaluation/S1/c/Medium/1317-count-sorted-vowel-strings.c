// Source: https://leetcode.com/problems/count-sorted-vowel-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
//
// A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
//
// Constraints:
// 1 <= n <= 50
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countVowelStrings(int n) {
    // Using combinatorial mathematics:
    // The problem can be transformed into finding the number of ways to distribute n identical items (vowel positions)
    // into 5 distinct boxes (the vowels a, e, i, o, u) where boxes can be empty.
    // This is equivalent to the "stars and bars" theorem in combinatorics.
    // The formula for this is C(n + k - 1, k - 1), where n is the number of items and k is the number of boxes.
    // Here, n is the length of the string and k is 5 (the number of vowels).
    
    int k = 5; // Number of vowels
    int N = n + k - 1; // Total items to choose from
    int R = k - 1; // Items to choose
    
    // Calculate C(N, R) = N! / (R! * (N - R)!)
    long long numerator = 1;
    long long denominator = 1;
    
    for (int i = 0; i < R; i++) {
        numerator *= (N - i);
        denominator *= (i + 1);
    }
    
    return (int)(numerator / denominator);      
}
