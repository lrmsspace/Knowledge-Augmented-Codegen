// Source: https://leetcode.com/problems/longest-absolute-file-path/   |   Difficulty: Medium
//
// Problem Description:
// Suppose we have a file system that stores both files and directories. An example of one system is represented in the following picture:
//
//
//
// Here, we have dir as the only directory in the root. dir contains two subdirectories, subdir1 and subdir2. subdir1 contains a file file1.ext and subdirectory subsubdir1. subdir2 contains a subdirectory subsubdir2, which contains a file file2.ext.
//
// In text form, it looks like this (with ⟶ representing the tab character):
//
//
// dir
// ⟶ subdir1
// ⟶ ⟶ file1.ext
// ⟶ ⟶ subsubdir1
// ⟶ subdir2
// ⟶ ⟶ subsubdir2
// ⟶ ⟶ ⟶ file2.ext
//
//
// If we were to write this representation in code, it will look like this: "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext". Note that the '\n' and '\t' are the new-line and tab characters.
//
// Every file and directory has a unique absolute path in the file system, which is the order of directories that must be opened to reach the file/directory itself, all concatenated by '/'s. Using the above example, the absolute path to file2.ext is "dir/subdir2/subsubdir2/file2.ext". Each directory name consists of letters, digits, and/or spaces. Each file name is of the form name.extension, where name and extension consist of letters, digits, and/or spaces.
//
// Given a string input representing the file system in the explained format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.
//
// Note that the testcases are generated such that the file system is valid and no file or directory name has length 0.
//
// Example:
// Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
// Output: 20
// Explanation: We have only one file, and the absolute path is "dir/subdir2/file.ext" of length 20.
//
// Constraints:
// 1 <= input.length <= 104
// 	input may contain lowercase or uppercase English letters, a new line character '\n', a tab character '\t', a dot '.', a space ' ', and digits.
// 	All file and directory names have positive length.
//

class Solution {
public:
    int lengthLongestPath(string input) {
        int maxLength = 0;
        unordered_map<int, int> pathLength; // depth -> current path length at this depth
        pathLength[0] = 0; // base case: depth 0 has length 0

        size_t pos = 0;
        while (pos < input.length()) {
            // Determine the depth by counting leading '\t'
            int depth = 0;
            while (pos < input.length() && input[pos] == '\t') {
                depth++;
                pos++;
            }

            // Find the end of the current line
            size_t lineEnd = input.find('\n', pos);
            if (lineEnd == string::npos) {
                lineEnd = input.length();
            }

            // Extract the current name (file or directory)
            string name = input.substr(pos, lineEnd - pos);
            pos = lineEnd + 1; // Move to the start of the next line

            // Check if it's a file
            if (name.find('.') != string::npos) {
                // It's a file, calculate total path length
                int totalLength = pathLength[depth] + name.length();
                maxLength = max(maxLength, totalLength);
            } else {
                // It's a directory, update path length for the next depth
                pathLength[depth + 1] = pathLength[depth] + name.length() + 1; // +1 for '/'
            }
        }

        return maxLength;           
    }
};
