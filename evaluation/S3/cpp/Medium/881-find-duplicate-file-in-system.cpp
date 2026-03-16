// Source: https://leetcode.com/problems/find-duplicate-file-in-system/   |   Difficulty: Medium
//
// Problem Description:
// Given a list paths of directory info, including the directory path, and all the files with contents in this directory, return all the duplicate files in the file system in terms of their paths. You may return the answer in any order.
//
// A group of duplicate files consists of at least two files that have the same content.
//
// A single directory info string in the input list has the following format:
//
//
// 	"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"
//
//
// It means there are n files (f1.txt, f2.txt ... fn.txt) with content (f1_content, f2_content ... fn_content) respectively in the directory "root/d1/d2/.../dm". Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the root directory.
//
// The output is a list of groups of duplicate file paths. For each group, it contains all the file paths of the files that have the same content. A file path is a string that has the following format:
//
//
// 	"directory_path/file_name.txt"
//
// Example:
// Input: paths = ["root/a 1.txt(abcd) 2.txt(efgh)","root/c 3.txt(abcd)","root/c/d 4.txt(efgh)","root 4.txt(efgh)"]
// Output: [["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]
//
// Constraints:
// 1 <= paths.length <= 2 * 104
// 	1 <= paths[i].length <= 3000
// 	1 <= sum(paths[i].length) <= 5 * 105
// 	paths[i] consist of English letters, digits, '/', '.', '(', ')', and ' '.
// 	You may assume no files or directories share the same name in the same directory.
// 	You may assume each given directory info represents a unique directory. A single blank space separates the directory path and file info.
//
//
//  
// Follow up:
//
//
// 	Imagine you are given a real file system, how will you search files? DFS or BFS?
// 	If the file content is very large (GB level), how will you modify your solution?
// 	If you can only read the file by 1kb each time, how will you modify your solution?
// 	What is the time complexity of your modified solution? What is the most time-consuming part and memory-consuming part of it? How to optimize?
// 	How to make sure the duplicated files you find are not false positive?
//
// Helpful references (internal KB):
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Expression parsing (stack, simulation)
//   • When to use: This algorithm is used to evaluate expressions given in Reverse Polish Notation (postfix notation) to compute their final numerical value.
//   • Idea: This algorithm evaluates an expression in Reverse Polish Notation by processing elements sequentially. Numbers are pushed onto a stack, and operators pop two operands, compute, and push the result.
//   • Invariants: The stack always contains only numbers (operands or intermediate results).; For a valid RPN expression, the stack will have at least two elements when an operator is processed.
//   • Tips: Process the RPN expression from left to right, token by token.; Push numerical operands directly onto the stack.
//   • Pitfalls: Attempting to pop from an empty stack when an operator is encountered, indicating an invalid RPN expression.; Incorrect order of operands for non-commutative operations like subtraction or division.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> contentToPaths;
        for (const string& path : paths) {
            istringstream iss(path);
            string dir;
            iss >> dir; // Extract the directory path
            string fileInfo;
            while (iss >> fileInfo) { // Extract each file info
                size_t openParen = fileInfo.find('(');
                size_t closeParen = fileInfo.find(')');
                string fileName = fileInfo.substr(0, openParen); // Get the file name
                string content = fileInfo.substr(openParen + 1, closeParen - openParen - 1); // Get the content
                contentToPaths[content].push_back(dir + "/" + fileName); // Map content to full file path
            }
        }

        vector<vector<string>> duplicates;
        for (const auto& entry : contentToPaths) {
            if (entry.second.size() > 1) { // Only consider contents that have duplicates
                duplicates.push_back(entry.second);
            }
        }
        return duplicates;          
    }
};
