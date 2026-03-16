// Source: https://leetcode.com/problems/reverse-degree-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, calculate its reverse degree.
//
// The reverse degree is calculated as follows:
//
//
// 	For each character, multiply its position in the reversed alphabet ('a' = 26, 'b' = 25, ..., 'z' = 1) with its position in the string (1-indexed).
// 	Sum these products for all characters in the string.
//
//
// Return the reverse degree of s.
//
// Example:
// Input: s = "abc"
//
// Output: 148
//
// Explanation:
//
//
// 	
// 		
// 			Letter
// 			Index in Reversed Alphabet
// 			Index in String
// 			Product
// 		
// 		
// 			'a'
// 			26
// 			1
// 			26
// 		
// 		
// 			'b'
// 			25
// 			2
// 			50
// 		
// 		
// 			'c'
// 			24
// 			3
// 			72
// 		
// 	
//
//
// The reversed degree is 26 + 50 + 72 = 148.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to efficiently compare strings or substrings, especially in scenarios involving large texts or numerous comparisons. It's also useful for pattern matching and detecting duplicates in collections of strings.
//   • Idea: String hashing converts a string into a numerical value (hash) to enable fast comparisons and lookups. This technique typically uses polynomial hashing with a base and a modulus, offering O(L) for initial hash computation and O(1) for substring hashes after O(N) precomputation.
//   • Invariants: The hash of a string S of length L is (S[0]*P^(L-1) + S[1]*P^(L-2) + ... + S[L-1]*P^0) % M.; For any substring S[i...j], its hash can be derived from precomputed prefix hashes in O(1) time.
//   • Tips: Use multiple hash functions with different bases and moduli to reduce collision probability.; Choose a large prime modulus (e.g., 10^9 + 7) and a random base for robustness.
//   • Pitfalls: Hash collisions are possible; always verify equality for critical applications or use multiple hashes.; Choosing a small or non-prime modulus significantly increases the risk of collisions.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int reverseDegree(String s) {
        int reverseDegree = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            int positionInReversedAlphabet = 'z' - c + 1; // 'a' = 26, 'b' = 25, ..., 'z' = 1
            int positionInString = i + 1; // 1-indexed
            reverseDegree += positionInReversedAlphabet * positionInString;
        }
        return reverseDegree;           
    }
}
