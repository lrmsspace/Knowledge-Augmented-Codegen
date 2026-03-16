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

char* simplifyPath(char* path) {
    char** stack = (char**)malloc(sizeof(char*) * 3000);
    int top = -1;
    char* token = strtok(path, "/");
    
    while (token != NULL) {
        if (strcmp(token, "..") == 0) {
            if (top >= 0) {
                top--;
            }
        } else if (strcmp(token, ".") != 0 && strlen(token) > 0) {
            stack[++top] = token;
        }
        token = strtok(NULL, "/");
    }
    
    if (top == -1) {
        return "/";
    }
    
    int totalLength = 0;
    for (int i = 0; i <= top; i++) {
        totalLength += strlen(stack[i]) + 1; // +1 for '/'
    }
    
    char* result = (char*)malloc(sizeof(char) * (totalLength + 1));
    result[0] = '\0';
    
    for (int i = 0; i <= top; i++) {
        strcat(result, "/");
        strcat(result, stack[i]);
    }
    
    free(stack);
    return result;      
}
