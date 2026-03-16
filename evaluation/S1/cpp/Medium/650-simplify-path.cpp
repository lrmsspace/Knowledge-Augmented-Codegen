// Source: https://leetcode.com/problems/simplify-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given an absolute path for a Unix-style file system, which always begins with a slash '/'. Your task is to transform this absolute path into its simplified canonical path.
//
// The rules of a Unix-style file system are as follows:
//
//
// 	A single period '.' represents the current directory.
// 	A double period '..' represents the previous/parent directory.
// 	Multiple consecutive slashes such as '//' and '///' are treated as a single slash '/'.
// 	Any sequence of periods that does not match the rules above should be treated as a valid directory or file name. For example, '...' and '....' are valid directory or file names.
//
//
// The simplified canonical path should follow these rules:
//
//
// 	The path must start with a single slash '/'.
// 	Directories within the path must be separated by exactly one slash '/'.
// 	The path must not end with a slash '/', unless it is the root directory.
// 	The path must not have any single or double periods ('.' and '..') used to denote current or parent directories.
//
//
// Return the simplified canonical path.
//
// Example:
// Input: path = "/home/"
//
// Output: "/home"
//
// Explanation:
//
// The trailing slash should be removed.
//
// Constraints:
// 1 <= path.length <= 3000
// 	path consists of English letters, digits, period '.', slash '/' or '_'.
// 	path is a valid absolute Unix path.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;
        int i = 0, n = path.size();
        while (i < n) {
            // Skip consecutive slashes
            while (i < n && path[i] == '/') i++;
            if (i >= n) break;
            // Extract the next component
            int start = i;
            while (i < n && path[i] != '/') i++;
            string component = path.substr(start, i - start);
            if (component == ".") {
                // Current directory, do nothing
                continue;
            } else if (component == "..") {
                // Parent directory, pop if possible
                if (!stack.empty()) stack.pop_back();
            } else {
                // Valid directory name, push onto stack
                stack.push_back(component);
            }
        }
        // Construct the simplified path
        if (stack.empty()) return "/";
        string result;
        for (const string& dir : stack) {
            result += "/" + dir;
        }
        return result;          
    }
};
