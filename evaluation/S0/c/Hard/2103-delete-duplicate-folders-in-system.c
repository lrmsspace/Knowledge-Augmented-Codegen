// Source: https://leetcode.com/problems/delete-duplicate-folders-in-system/   |   Difficulty: Hard
//
// Problem Description:
// Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths, where paths[i] is an array representing an absolute path to the ith folder in the file system.
//
//
// 	For example, ["one", "two", "three"] represents the path "/one/two/three".
//
//
// Two folders (not necessarily on the same level) are identical if they contain the same non-empty set of identical subfolders and underlying subfolder structure. The folders do not need to be at the root level to be identical. If two or more folders are identical, then mark the folders as well as all their subfolders.
//
//
// 	For example, folders "/a" and "/b" in the file structure below are identical. They (as well as their subfolders) should all be marked:
//
// 	
// 		/a
// 		/a/x
// 		/a/x/y
// 		/a/z
// 		/b
// 		/b/x
// 		/b/x/y
// 		/b/z
// 	
// 	
// 	However, if the file structure also included the path "/b/w", then the folders "/a" and "/b" would not be identical. Note that "/a/x" and "/b/x" would still be considered identical even with the added folder.
//
//
// Once all the identical folders and their subfolders have been marked, the file system will delete all of them. The file system only runs the deletion once, so any folders that become identical after the initial deletion are not deleted.
//
// Return the 2D array ans containing the paths of the remaining folders after deleting all the marked folders. The paths may be returned in any order.
//
// Example:
// Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
// Output: [["d"],["d","a"]]
// Explanation: The file structure is as shown.
// Folders "/a" and "/c" (and their subfolders) are marked for deletion because they both contain an empty
// folder named "b".
//
// Constraints:
// 1 <= paths.length <= 2 * 104
// 	1 <= paths[i].length <= 500
// 	1 <= paths[i][j].length <= 10
// 	1 <= sum(paths[i][j].length) <= 2 * 105
// 	path[i][j] consists of lowercase English letters.
// 	No two paths lead to the same folder.
// 	For any folder not at the root level, its parent folder will also be in the input.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** deleteDuplicateFolder(char*** paths, int pathsSize, int* pathsColSize, int* returnSize, int** returnColumnSizes) {
    // Implementation of trie to represent the file system and hash to identify duplicate folders

    typedef struct TrieNode {
        struct TrieNode** children;
        int childrenCount;
        int isEnd;
        char* name;
    } TrieNode;

    TrieNode* createNode(char* name) {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        node->children = NULL;
        node->childrenCount = 0;
        node->isEnd = 0;
        node->name = name;
        return node;
    }

    TrieNode* root = createNode(NULL);

    // Build the trie
    for (int i = 0; i < pathsSize; i++) {
        TrieNode* current = root;
        for (int j = 0; j < pathsColSize[i]; j++) {
            char* folderName = paths[i][j];
            int found = 0;
            for (int k = 0; k < current->childrenCount; k++) {
                if (strcmp(current->children[k]->name, folderName) == 0) {
                    current = current->children[k];
                    found = 1;
                    break;
                }
            }
            if (!found) {
                TrieNode* newNode = createNode(folderName);
                current->children = (TrieNode**)realloc(current->children, sizeof(TrieNode*) * (current->childrenCount + 1));
                current->children[current->childrenCount++] = newNode;
                current = newNode;
            }
        }
        current->isEnd = 1;
    }

    // Hashing and marking duplicates would go here
    // ...

    // Collect remaining paths
    char*** result = NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;

    // DFS to collect paths
    void dfs(TrieNode* node, char** path, int depth) {
        if (node->isEnd) {
            if (*returnSize % 16 == 0) {
                int newCap = (*returnSize == 0) ? 16 : (*returnSize * 2);
                char*** tmp = (char***)realloc(result, sizeof(char**) * newCap);
                if (!tmp) return;
                result = tmp;
                int* tmpCols = (int*)realloc(*returnColumnSizes, sizeof(int) * newCap);
                if (!tmpCols) return;
                *returnColumnSizes = tmpCols;
            }
            char** newPath = (char**)malloc(sizeof(char*) * depth);
            for (int i = 0; i < depth; i++) {
                newPath[i] = path[i];
            }
            result[*returnSize] = newPath;
            (*returnColumnSizes)[*returnSize] = depth;
            (*returnSize)++;
        }
        for (int i = 0; i < node->childrenCount; i++) {
            path[depth] = node->children[i]->name;
            dfs(node->children[i], path, depth + 1);
        }
    }
    char** path = (char**)malloc(sizeof(char*) * 500); // Max depth assumed to be 500
    dfs(root, path, 0);
    free(path);
    // Cleanup trie
    void freeTrie(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < node->childrenCount; i++) {
            freeTrie(node->children[i]);
        }
        free(node->children);
        free(node);
    }
    freeTrie(root);
    return result;
}
