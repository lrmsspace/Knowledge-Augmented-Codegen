// Source: https://leetcode.com/problems/remove-comments/   |   Difficulty: Medium
//
// Problem Description:
// Given a C++ program, remove comments from it. The program source is an array of strings source where source[i] is the ith line of the source code. This represents the result of splitting the original source code string by the newline character '\n'.
//
// In C++, there are two types of comments, line comments, and block comments.
//
//
// 	The string "//" denotes a line comment, which represents that it and the rest of the characters to the right of it in the same line should be ignored.
// 	The string "/*" denotes a block comment, which represents that all characters until the next (non-overlapping) occurrence of "*/" should be ignored. (Here, occurrences happen in reading order: line by line from left to right.) To be clear, the string "/*/" does not yet end the block comment, as the ending would be overlapping the beginning.
//
//
// The first effective comment takes precedence over others.
//
//
// 	For example, if the string "//" occurs in a block comment, it is ignored.
// 	Similarly, if the string "/*" occurs in a line or block comment, it is also ignored.
//
//
// If a certain line of code is empty after removing comments, you must not output that line: each string in the answer list will be non-empty.
//
// There will be no control characters, single quote, or double quote characters.
//
//
// 	For example, source = "string s = "/* Not a comment. */";" will not be a test case.
//
//
// Also, nothing else such as defines or macros will interfere with the comments.
//
// It is guaranteed that every open block comment will eventually be closed, so "/*" outside of a line or block comment always starts a new comment.
//
// Finally, implicit newline characters can be deleted by block comments. Please see the examples below for details.
//
// After removing the comments from the source code, return the source code in the same format.
//
// Example:
// Input: source = ["/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}"]
// Output: ["int main()","{ ","  ","int a, b, c;","a = b + c;","}"]
// Explanation: The line by line code is visualized as below:
// /*Test program */
// int main()
// { 
//   // variable declaration 
// int a, b, c;
// /* This is a test
//    multiline  
//    comment for 
//    testing */
// a = b + c;
// }
// The string /* denotes a block comment, including line 1 and lines 6-9. The string // denotes line 4 as comments.
// The line by line output code is visualized as below:
// int main()
// { 
//   
// int a, b, c;
// a = b + c;
// }
//
// Constraints:
// 1 <= source.length <= 100
// 	0 <= source[i].length <= 80
// 	source[i] consists of printable ASCII characters.
// 	Every open block comment is eventually closed.
// 	There are no single-quote or double-quote in the input.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> ans;
        string cur;
        bool block = false;
        for (auto &s : source) {
            for (int i = 0; i < s.size(); ++i) {
                if (!block && i + 1 < s.size() && s[i] == '/' && s[i + 1] == '/') break;
                else if (!block && i + 1 < s.size() && s[i] == '/' && s[i + 1] == '*') block = true, ++i;
                else if (block && i + 1 < s.size() && s[i] == '*' && s[i + 1] == '/') block = false, ++i;
                else if (!block) cur += s[i];
            }
            if (!cur.empty() && !block) ans.push_back(cur), cur.clear();
        }
        return ans;         
    }
};
