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

int countVowelStrings(int n) {
    // Using combinatorial mathematics:
    // The problem can be transformed into finding the number of ways to distribute n identical items (vowel positions)
    // into 5 distinct boxes (the vowels a, e, i, o, u) where the order of boxes matters.
    // This is equivalent to the "stars and bars" theorem in combinatorics.
    // The formula for this is C(n + k - 1, k - 1), where k is the number of distinct items (vowels).
    // Here, k = 5 (a, e, i, o, u), so we need to compute C(n + 5 - 1, 5 - 1) = C(n + 4, 4).

    int k = 5; // number of vowels
    int N = n + k - 1; // total items to choose from
    int R = k - 1; // items to choose

    // Calculate C(N, R) = N! / (R! * (N - R)!)
    long long numerator = 1;
    long long denominator = 1;

    for (int i = 0; i < R; i++) {
        numerator *= (N - i);
        denominator *= (i + 1);
    }

    return numerator / denominator;     
}
