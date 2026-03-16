// Source: https://leetcode.com/problems/word-ladder-ii/   |   Difficulty: Hard
//
// Problem Description:
// A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:
//
//
// 	Every adjacent pair of words differs by a single letter.
// 	Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
// 	sk == endWord
//
//
// Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].
//
// Example:
// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
// Explanation: There are 2 shortest transformation sequences:
// "hit" -> "hot" -> "dot" -> "dog" -> "cog"
// "hit" -> "hot" -> "lot" -> "log" -> "cog"
//
// Constraints:
// 1 <= beginWord.length <= 5
// 	endWord.length == beginWord.length
// 	1 <= wordList.length <= 500
// 	wordList[i].length == beginWord.length
// 	beginWord, endWord, and wordList[i] consist of lowercase English letters.
// 	beginWord != endWord
// 	All the words in wordList are unique.
// 	The sum of all shortest transformation sequences does not exceed 105.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** findLadders(char* beginWord, char* endWord, char** wordList, int wordListSize, int* returnSize, int** returnColumnSizes) {

     *returnSize = 0;
    int wordLen = strlen(beginWord);
    
    // Check if endWord exists in wordList
    int endIdx = -1;
    for (int i = 0; i < wordListSize; i++) {
        if (strcmp(wordList[i], endWord) == 0) {
            endIdx = i;
            break;
        }
    }
    
    if (endIdx == -1) {
        *returnColumnSizes = NULL;
        return NULL;
    }
    
    // Build adjacency graph
    int** adj = (int**)malloc((wordListSize + 1) * sizeof(int*));
    int* adjSize = (int*)calloc(wordListSize + 1, sizeof(int));
    
    for (int i = 0; i < wordListSize + 1; i++) {
        adj[i] = (int*)malloc(wordListSize * sizeof(int));
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
    
    // Node 0 = beginWord, nodes 1..wordListSize = wordList
    for (int i = 0; i < wordListSize; i++) {
        if (isAdjacent(beginWord, wordList[i])) {
            adj[0][adjSize[0]++] = i + 1;
        }
        for (int j = i + 1; j < wordListSize; j++) {
            if (isAdjacent(wordList[i], wordList[j])) {
                adj[i + 1][adjSize[i + 1]++] = j + 1;
                adj[j + 1][adjSize[j + 1]++] = i + 1;
            }
        }
    }
    
    endIdx++;  // Adjust for 1-indexed graph
    
    // BFS to find shortest paths
    int* dist = (int*)malloc((wordListSize + 1) * sizeof(int));
    int** parents = (int**)malloc((wordListSize + 1) * sizeof(int*));
    int* parentCnt = (int*)calloc(wordListSize + 1, sizeof(int));
    
    for (int i = 0; i < wordListSize + 1; i++) {
        dist[i] = -1;
        parents[i] = (int*)malloc(wordListSize * sizeof(int));
    }
    
    int* queue = (int*)malloc((wordListSize + 1) * sizeof(int));
    int head = 0, tail = 0;
    queue[tail++] = 0;
    dist[0] = 0;
    
    while (head < tail) {
        int u = queue[head++];
        for (int i = 0; i < adjSize[u]; i++) {
            int v = adj[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parents[v][parentCnt[v]++] = u;
                queue[tail++] = v;
            } else if (dist[v] == dist[u] + 1) {
                parents[v][parentCnt[v]++] = u;
            }
        }
    }
    
    if (dist[endIdx] == -1) {
        // No path found
        for (int i = 0; i < wordListSize + 1; i++) {
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
    
    // Backtrack to collect all shortest paths
    char**** tempPaths = (char****)malloc(10000 * sizeof(char***));
    int* tempLens = (int*)malloc(10000 * sizeof(int));
    int pathCnt = 0;
    
    void dfs(int node, char** curPath, int len) {
        if (node == 0) {
            tempPaths[pathCnt] = (char**)malloc(len * sizeof(char*));
            for (int i = 0; i < len; i++) {
                tempPaths[pathCnt][i] = curPath[len - 1 - i];
            }
            tempLens[pathCnt] = len;
            pathCnt++;
            return;
        }
        
        for (int i = 0; i < parentCnt[node]; i++) {
            int p = parents[node][i];
            curPath[len] = (node == 0) ? beginWord : wordList[node - 1];
            dfs(p, curPath, len + 1);
        }
    }
    
    char** curPath = (char**)malloc((dist[endIdx] + 1) * sizeof(char*));
    curPath[0] = endWord;
    dfs(endIdx, curPath, 1);
    
    // Build result
    *returnSize = pathCnt;
    *returnColumnSizes = (int*)malloc(pathCnt * sizeof(int));
    char*** result = (char***)malloc(pathCnt * sizeof(char**));
    
    for (int i = 0; i < pathCnt; i++) {
        (*returnColumnSizes)[i] = tempLens[i];
        result[i] = tempPaths[i];
    }
    
    // Cleanup
    for (int i = 0; i < wordListSize + 1; i++) {
        free(adj[i]);
        free(parents[i]);
    }
    free(adj);
    free(adjSize);
    free(dist);
    free(parents);
    free(parentCnt);
    free(queue);
    free(curPath);
    free(tempPaths);
    free(tempLens);
    
    return result;
}
