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
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
//   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
//   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
//   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
//   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
//   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
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
        string currentLine;
        bool inBlockComment = false;

        for (const string& line : source) {
            int i = 0;
            while (i < line.size()) {
                if (!inBlockComment && i + 1 < line.size() && line[i] == '/' && line[i + 1] == '/') {
                    // Line comment found, ignore the rest of the line
                    break;
                } else if (!inBlockComment && i + 1 < line.size() && line[i] == '/' && line[i + 1] == '*') {
                    // Block comment start found
                    inBlockComment = true;
                    i += 2; // Skip "/*"
                } else if (inBlockComment && i + 1 < line.size() && line[i] == '*' && line[i + 1] == '/') {
                    // Block comment end found
                    inBlockComment = false;
                    i += 2; // Skip "*/"
                } else if (!inBlockComment) {
                    // Normal character, add to currentLine
                    currentLine += line[i];
                    i++;
                } else {
                    // Inside block comment, skip characters
                    i++;
                }
            }

            // If we're not in a block comment and currentLine is not empty, add it to the answer
            if (!inBlockComment && !currentLine.empty()) {
                ans.push_back(currentLine);
                currentLine.clear(); // Reset for the next line
            }
        }

        return ans;         
    }
};
