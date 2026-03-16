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
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** findDuplicate(char** paths, int pathsSize, int* returnSize, int** returnColumnSizes) {
    #define HASH_MAP_SIZE 10007

    typedef struct FileNode {
        char* path;
        struct FileNode* next;
    } FileNode;

    typedef struct HashNode {
        char* content;
        FileNode* files;
        struct HashNode* next;
    } HashNode;

    HashNode* hashMap[HASH_MAP_SIZE] = {0};

    unsigned long hashFunction(const char* str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % HASH_MAP_SIZE;
    }

    for (int i = 0; i < pathsSize; i++) {
        char* pathStr = paths[i];
        char* dir = strtok(pathStr, " ");
        char* fileInfo;
        while ((fileInfo = strtok(NULL, " ")) != NULL) {
            char* openParen = strchr(fileInfo, '(');
            char* closeParen = strchr(fileInfo, ')');
            if (!openParen || !closeParen) continue;

            *openParen = '\0';
            char* fileName = fileInfo;
            char* content = openParen + 1;
            *closeParen = '\0';

            unsigned long hashIndex = hashFunction(content);
            HashNode* node = hashMap[hashIndex];
            while (node) {
                if (strcmp(node->content, content) == 0) break;
                node = node->next;
            }
            if (!node) {
                node = (HashNode*)malloc(sizeof(HashNode));
                node->content = strdup(content);
                node->files = NULL;
                node->next = hashMap[hashIndex];
                hashMap[hashIndex] = node;
            }

            FileNode* fileNode = (FileNode*)malloc(sizeof(FileNode));
            int fullPathLen = strlen(dir) + 1 + strlen(fileName) + 1;
            fileNode->path = (char*)malloc(fullPathLen);
            snprintf(fileNode->path, fullPathLen, "%s/%s", dir, fileName);
            fileNode->next = node->files;
            node->files = fileNode;
        }
    }
    char*** result = NULL;
    int resultCap = 0;
    int resultSize = 0;
    int* colSizes = NULL;
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashNode* node = hashMap[i];
        while (node) {
            int fileCount = 0;
            FileNode* fileNode = node->files;
            while (fileNode) {
                fileCount++;
                fileNode = fileNode->next;
            }
            if (fileCount > 1) {
                if (resultSize == resultCap) {
                    resultCap = resultCap == 0 ? 1 : resultCap * 2;
                    result = (char***)realloc(result, resultCap * sizeof(char**));
                    colSizes = (int*)realloc(colSizes, resultCap * sizeof(int));
                }
                result[resultSize] = (char**)malloc(fileCount * sizeof(char*));
                colSizes[resultSize] = fileCount;
                fileNode = node->files;
                for (int j = 0; j < fileCount; j++) {
                    result[resultSize][j] = fileNode->path;
                    fileNode = fileNode->next;
                }
                resultSize++;
            } else {
                // Free single file path
                if (node->files) {
                    free(node->files->path);
                    free(node->files);
                }
            }
            HashNode* temp = node;
            node = node->next;
            free(temp->content);
            free(temp);
        }
    }
    *returnSize = resultSize;
    *returnColumnSizes = colSizes;
    return result;

}
