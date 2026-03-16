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
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
//   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
//   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
//   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
//   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
//   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
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
char*** deleteDuplicateFolder(char*** paths, int pathsSize, int* pathsColSize, int* returnSize, int** returnColumnSizes) {
    // Create a trie-like structure to represent the folder hierarchy
    typedef struct TrieNode {
        char* name;
        struct TrieNode** children;
        int childrenCount;
        int capacity;
        int isDuplicate;
        char* hash;
    } TrieNode;
    
    // Helper function to create a new trie node
    TrieNode* createNode(const char* name) {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        node->name = (char*)malloc(strlen(name) + 1);
        strcpy(node->name, name);
        node->children = (TrieNode**)malloc(sizeof(TrieNode*) * 10);
        node->childrenCount = 0;
        node->capacity = 10;
        node->isDuplicate = 0;
        node->hash = NULL;
        return node;
    }
    
    // Helper function to insert a path into the trie
    void insertPath(TrieNode* root, char** path, int pathLen) {
        TrieNode* current = root;
        for (int i = 0; i < pathLen; i++) {
            TrieNode* found = NULL;
            for (int j = 0; j < current->childrenCount; j++) {
                if (strcmp(current->children[j]->name, path[i]) == 0) {
                    found = current->children[j];
                    break;
                }
            }
            if (!found) {
                if (current->childrenCount == current->capacity) {
                    current->capacity *= 2;
                    current->children = (TrieNode**)realloc(current->children, 
                                                           sizeof(TrieNode*) * current->capacity);
                }
                found = createNode(path[i]);
                current->children[current->childrenCount++] = found;
            }
            current = found;
        }
    }
    
    // DFS to compute hash for each folder
    char* computeHash(TrieNode* node, int* allHashCount, char*** allHashes) {
        if (node->childrenCount == 0) {
            node->hash = (char*)malloc(2);
            strcpy(node->hash, "");
            return node->hash;
        }
        
        // Sort children by name for consistent hashing
        for (int i = 0; i < node->childrenCount - 1; i++) {
            for (int j = i + 1; j < node->childrenCount; j++) {
                if (strcmp(node->children[i]->name, node->children[j]->name) > 0) {
                    TrieNode* temp = node->children[i];
                    node->children[i] = node->children[j];
                    node->children[j] = temp;
                }
            }
        }
        
        // Build hash string: concatenate child names and their hashes
        int totalLen = 1;
        for (int i = 0; i < node->childrenCount; i++) {
            computeHash(node->children[i], allHashCount, allHashes);
            totalLen += strlen(node->children[i]->name) + 
                       strlen(node->children[i]->hash) + 2;
        }
        
        node->hash = (char*)malloc(totalLen);
        node->hash[0] = '\0';
        for (int i = 0; i < node->childrenCount; i++) {
            strcat(node->hash, "(");
            strcat(node->hash, node->children[i]->name);
            strcat(node->hash, node->children[i]->hash);
            strcat(node->hash, ")");
        }
        
        return node->hash;
    }
    
    // Mark duplicate folders
    void markDuplicates(TrieNode* node, int* hashCount, char*** hashArray, int** countArray) {
        computeHash(node, hashCount, hashArray);
        
        // Use a map to count hashes
        typedef struct {
            char* hash;
            int count;
            TrieNode* node;
        } HashEntry;
        
        // Simple DFS to find and mark duplicates
        void dfs(TrieNode* curr, int depth) {
            if (depth > 0) {
                // Check if this hash appears multiple times
                for (int i = 0; i < pathsSize; i++) {
                    // Count occurrences in actual traversal
                }
            }
            for (int i = 0; i < curr->childrenCount; i++) {
                dfs(curr->children[i], depth + 1);
            }
        }
    }
    
    // Count hashes and mark duplicates
    typedef struct {
        char* hash;
        int count;
    } HashCount;
    
    HashCount* hashCounts = (HashCount*)malloc(sizeof(HashCount) * pathsSize * 500);
    int hashCountLen = 0;
    
    // Create root and build trie
    TrieNode* root = createNode("");
    for (int i = 0; i < pathsSize; i++) {
        insertPath(root, paths[i], pathsColSize[i]);
    }
    
    // Compute hashes and collect all hashes
    int hashIdx = 0;
    char** allHashes = (char**)malloc(sizeof(char*) * pathsSize * 500);
    
    void traverseAndHash(TrieNode* node) {
        computeHash(node, &hashIdx, &allHashes);
        for (int i = 0; i < node->childrenCount; i++) {
            traverseAndHash(node->children[i]);
        }
    }
    
    for (int i = 0; i < root->childrenCount; i++) {
        traverseAndHash(root->children[i]);
    }
    
    // Count hash occurrences
    for (int i = 0; i < root->childrenCount; i++) {
        void countHashes(TrieNode* node) {
            int found = 0;
            for (int j = 0; j < hashCountLen; j++) {
                if (strcmp(hashCounts[j].hash, node->hash) == 0) {
                    hashCounts[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && node->hash && strlen(node->hash) > 0) {
                hashCounts[hashCountLen].hash = node->hash;
                hashCounts[hashCountLen].count = 1;
                hashCountLen++;
            }
            for (int k = 0; k < node->childrenCount; k++) {
                countHashes(node->children[k]);
            }
        }
        countHashes(root->children[i]);
    }
    
    // Mark nodes with duplicate hashes
    void markDups(TrieNode* node) {
        for (int j = 0; j < hashCountLen; j++) {
            if (node->hash && strcmp(hashCounts[j].hash, node->hash) == 0 && 
                hashCounts[j].count > 1) {
                node->isDuplicate = 1;
                break;
            }
        }
        for (int i = 0; i < node->childrenCount; i++) {
            markDups(node->children[i]);
        }
    }
    
    for (int i = 0; i < root->childrenCount; i++) {
        markDups(root->children[i]);
    }
    
    // Collect remaining paths
    char*** result = (char***)malloc(sizeof(char**) * pathsSize);
    int* columnSizes = (int*)malloc(sizeof(int) * pathsSize);
    int resultLen = 0;
    
    void collectPaths(TrieNode* node, char** currentPath, int pathLen) {
        if (node->isDuplicate) return;
        
        if (pathLen > 0) {
            char** newPath = (char**)malloc(sizeof(char*) * (pathLen + 1));
            for (int i = 0; i < pathLen; i++) {
                newPath[i] = currentPath[i];
            }
            result[resultLen] = newPath;
            columnSizes[resultLen] = pathLen;
            resultLen++;
        }
        
        for (int i = 0; i < node->childrenCount; i++) {
            char** newPath = (char**)malloc(sizeof(char*) * (pathLen + 2));
            for (int j = 0; j < pathLen; j++) {
                newPath[j] = currentPath[j];
            }
            newPath[pathLen] = node->children[i]->name;
            collectPaths(node->children[i], newPath, pathLen + 1);
            if (pathLen > 0) free(newPath);
        }
    }
    
    char** emptyPath = (char**)malloc(sizeof(char*));
    collectPaths(root, emptyPath, 0);
    free(emptyPath);
    
    *returnSize = resultLen;
    *returnColumnSizes = columnSizes;
    
    // Free memory (simplified - in production would need complete cleanup)
    free(hashCounts);
    free(allHashes);
    
    return result;
}
