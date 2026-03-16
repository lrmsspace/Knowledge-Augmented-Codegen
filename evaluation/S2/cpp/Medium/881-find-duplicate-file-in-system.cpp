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
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
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
        for (const auto& path : paths) {
            stringstream ss(path);
            string dir;
            ss >> dir; // Extract the directory path

            string fileInfo;
            while (ss >> fileInfo) { // Extract each file info
                size_t openParen = fileInfo.find('(');
                size_t closeParen = fileInfo.find(')');

                string fileName = fileInfo.substr(0, openParen); // Extract the file name
                string content = fileInfo.substr(openParen + 1, closeParen - openParen - 1); // Extract the content

                contentToPaths[content].push_back(dir + "/" + fileName); // Map content to its full path
            }
        }

        vector<vector<string>> duplicates;
        for (const auto& entry : contentToPaths) {
            if (entry.second.size() > 1) { // Only consider contents with duplicates
                duplicates.push_back(entry.second);
            }
        }

        return duplicates;          
    }
};
