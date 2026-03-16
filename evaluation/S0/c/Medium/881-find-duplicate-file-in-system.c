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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** findDuplicate(char** paths, int pathsSize, int* returnSize, int** returnColumnSizes) {
    #define MAX_FILES 10000
    #define MAX_PATH_LEN 3000
    #define MAX_CONTENT_LEN 1000

    typedef struct FileNode {
        char path[MAX_PATH_LEN];
        struct FileNode* next;
    } FileNode;

    typedef struct ContentMap {
        char content[MAX_CONTENT_LEN];
        FileNode* files;
        struct ContentMap* next;
    } ContentMap;

    ContentMap* contentMapHead = NULL;

    for (int i = 0; i < pathsSize; i++) {
        char* token = strtok(paths[i], " ");
        char* dirPath = token;

        while ((token = strtok(NULL, " ")) != NULL) {
            char* openParen = strchr(token, '(');
            char* closeParen = strchr(token, ')');
            int contentLen = closeParen - openParen - 1;

            char content[MAX_CONTENT_LEN];
            strncpy(content, openParen + 1, contentLen);
            content[contentLen] = '\0';

            char filePath[MAX_PATH_LEN];
            snprintf(filePath, sizeof(filePath), "%s/%.*s", dirPath, (int)(openParen - token), token);

            ContentMap* currMap = contentMapHead;
            ContentMap* prevMap = NULL;
            while (currMap != NULL && strcmp(currMap->content, content) != 0) {
                prevMap = currMap;
                currMap = currMap->next;
            }

            if (currMap == NULL) {
                currMap = (ContentMap*)malloc(sizeof(ContentMap));
                strcpy(currMap->content, content);
                currMap->files = NULL;
                currMap->next = NULL;

                if (prevMap == NULL) {
                    contentMapHead = currMap;
                } else {
                    prevMap->next = currMap;
                }
            }

            FileNode* newFileNode = (FileNode*)malloc(sizeof(FileNode));
            strcpy(newFileNode->path, filePath);
            newFileNode->next = currMap->files;
            currMap->files = newFileNode;
        }
    }

    char*** result = (char***)malloc(MAX_FILES * sizeof(char**));
    *returnColumnSizes = (int*)malloc(MAX_FILES * sizeof(int));
    *returnSize = 0;

    ContentMap* currMap = contentMapHead;
    while (currMap != NULL) {
        int fileCount = 0;
        FileNode* currFile = currMap->files;
        while (currFile != NULL) {
            fileCount++;
            currFile = currFile->next;
        }

        if (fileCount > 1) {
            result[*returnSize] = (char**)malloc(fileCount * sizeof(char*));
            (*returnColumnSizes)[*returnSize] = fileCount;

            currFile = currMap->files;
            for (int j = 0; j < fileCount; j++) {
                result[*returnSize][j] = (char*)malloc(MAX_PATH_LEN * sizeof(char));
                strcpy(result[*returnSize][j], currFile->path);
                currFile = currFile->next;
            }
            (*returnSize)++;
        }

        // Free the file nodes
        currFile = currMap->files;
        while (currFile != NULL) {
            FileNode* temp = currFile;
            currFile = currFile->next;
            free(temp);
        }

        ContentMap* tempMap = currMap;
        currMap = currMap->next;
        free(tempMap);
    }
    return result;
}
