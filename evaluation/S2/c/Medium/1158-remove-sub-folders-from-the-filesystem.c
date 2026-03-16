// Source: https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of folders folder, return the folders after removing all sub-folders in those folders. You may return the answer in any order.
//
// If a folder[i] is located within another folder[j], it is called a sub-folder of it. A sub-folder of folder[j] must start with folder[j], followed by a "/". For example, "/a/b" is a sub-folder of "/a", but "/b" is not a sub-folder of "/a/b/c".
//
// The format of a path is one or more concatenated strings of the form: '/' followed by one or more lowercase English letters.
//
//
// 	For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string and "/" are not.
//
// Example:
// Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
// Output: ["/a","/c/d","/c/f"]
// Explanation: Folders "/a/b" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.
//
// Constraints:
// 1 <= folder.length <= 4 * 104
// 	2 <= folder[i].length <= 100
// 	folder[i] contains only lowercase letters and '/'.
// 	folder[i] always starts with the character '/'.
// 	Each folder name is unique.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeSubfolders(char** folder, int folderSize, int* returnSize) {
    // Sort the folders lexicographically
    qsort(folder, folderSize, sizeof(char*), (int (*)(const void*, const void*))strcmp);

    char** result = (char**)malloc(folderSize * sizeof(char*));
    int count = 0;

    for (int i = 0; i < folderSize; i++) {
        // If the current folder is not a subfolder of the last added folder, add it to the result
        if (count == 0 || strncmp(result[count - 1], folder[i], strlen(result[count - 1])) != 0 || folder[i][strlen(result[count - 1])] != '/') {
            result[count++] = folder[i];
        }
    }

    *returnSize = count;
    return result;      
}
