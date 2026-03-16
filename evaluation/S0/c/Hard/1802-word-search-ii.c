// Source: https://leetcode.com/problems/word-search-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n board of characters and a list of strings words, return all words on the board.
//
// Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
//
// Example:
// Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
// Output: ["eat","oath"]
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m, n <= 12
// 	board[i][j] is a lowercase English letter.
// 	1 <= words.length <= 3 * 104
// 	1 <= words[i].length <= 10
// 	words[i] consists of lowercase English letters.
// 	All the strings of words are unique.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** board, int boardSize, int* boardColSize, char** words, int wordsSize, int* returnSize) {
    
    *returnSize = 0;
    int wordLen = strlen(words[0]);
    
    // Check if endWord exists in wordList
    int endIdx = -1;
    for (int i = 0; i < wordsSize; i++) {
        if (strcmp(words[i], endWord) == 0) {
            endIdx = i;
            break;
        }
    }
    
    if (endIdx == -1) {
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    // Build adjacency graph
    int** adj = (int**)malloc((wordsSize + 1) * sizeof(int*));
    int* adjSize = (int*)calloc(wordsSize + 1, sizeof(int));
    
    for (int i = 0; i < wordsSize + 1; i++) {
        adj[i] = (int*)malloc(wordsSize * sizeof(int));
    }
    
    // Helper: check if two words differ by exactly one character
    int isAdjacent(char* a, char* b) {
        int diff = 0;
        for (int i = 0; i < wordLen; i++) {
            if (a[i] != b[i]) diff++;
            if (diff > 1) return 0;
        }
        return diff == 1;
    }
    
    // Node 0 = beginWord, nodes 1..wordsSize = words
    for (int i = 0; i < wordsSize; i++) {
        if (isAdjacent(beginWord, words[i])) {
            adj[0][adjSize[0]++] = i + 1;
        }
        for (int j = i + 1; j < wordsSize; j++) {
            if (isAdjacent(words[i], words[j])) {
                adj[i + 1][adjSize[i + 1]++] = j + 1;
                adj[j + 1][adjSize[j + 1]++] = i + 1;
            }
        }
    }
    
    endIdx++;  // Adjust for 1-indexed graph
    
    // BFS to find shortest paths
    int* dist = (int*)malloc((wordsSize + 1) * sizeof(int));
    int** parents = (int**)malloc((wordsSize + 1) * sizeof(int*));
    int* parentCnt = (int*)calloc(wordsSize + 1, sizeof(int));

    for (int i = 0; i < wordsSize + 1; i++) {
        dist[i] = -1;
        parents[i] = (int*)malloc((wordsSize + 1) * sizeof(int));
    }

    // BFS initialization
    int* queue = (int*)malloc((wordsSize + 1) * sizeof(int));
    int front = 0, back = 0;
    queue[back++] = 0;
    dist[0] = 0;

    while (front < back) {
        int u = queue[front++];
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[back++] = v;
            }
            if (dist[v] == dist[u] + 1) {
                parents[v][parentCnt[v]++] = u;
            }
        }
    }
    
    if (dist[endIdx] == -1) {
        // Cleanup
        for (int i = 0; i < wordsSize + 1; i++) {
            free(adj[i]);
            free(parents[i]);
        }
        free(adj);
        free(adjSize);
        free(dist);
        free(parents);
        free(parentCnt);
        free(queue);
        *returnColumnSizes = NULL;
        return NULL;
    }

    // Backtrack to find all paths
    char** result = (char**)malloc(sizeof(char*) * 500); // Allocate space for up to 500 results
    *returnSize = 0;
    int* path = (int*)malloc((dist[endIdx] + 1) * sizeof(int));
    void backtrack(int node, int depth) {
        path[depth] = node;
        if (node == 0) {
            // Found a path, construct the word list
            char* sequence = (char*)malloc((dist[endIdx] * (wordLen + 1)) * sizeof(char));
            sequence[0] = '\0';
            for (int i = depth; i > 0; i--) {
                strcat(sequence, words[path[i] - 1]);
                if (i > 1) strcat(sequence, " ");
            }
            result[*returnSize] = sequence;
            (*returnSize)++;
            return;
        }
        for (int i = 0; i < parentCnt[node]; i++) {
            backtrack(parents[node][i], depth + 1);
        }
    }
    backtrack(endIdx, 0);
    
    // Cleanup
    for (int i = 0; i < wordsSize + 1; i++) {
        free(adj[i]);
        free(parents[i]);
    }
    free(adj);
    free(adjSize);
    free(dist);
    free(parents);
    free(parentCnt);
    free(queue);
    free(path);

    *returnColumnSizes = NULL; // Adjust as needed for your return type
    return result;
}
