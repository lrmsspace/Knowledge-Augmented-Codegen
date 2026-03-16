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

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;
        int n = path.size();
        int i = 0;

        while (i < n) {
            // Skip multiple slashes
            while (i < n && path[i] == '/') {
                i++;
            }
            if (i >= n) break;

            // Find the next component
            int start = i;
            while (i < n && path[i] != '/') {
                i++;
            }
            string component = path.substr(start, i - start);

            if (component == ".") {
                // Current directory, do nothing
                continue;
            } else if (component == "..") {
                // Parent directory, pop from stack if possible
                if (!stack.empty()) {
                    stack.pop_back();
                }
            } else {
                // Valid directory name, push to stack
                stack.push_back(component);
            }
        }

        // Construct the simplified path
        string simplifiedPath = "/";
        for (int j = 0; j < stack.size(); j++) {
            simplifiedPath += stack[j];
            if (j != stack.size() - 1) {
                simplifiedPath += "/";
            }
        }

        return simplifiedPath;          
    }
};
