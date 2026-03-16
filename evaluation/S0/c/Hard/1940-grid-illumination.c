// Source: https://leetcode.com/problems/grid-illumination/   |   Difficulty: Hard
//
// Problem Description:
// There is a 2D grid of size n x n where each cell of this grid has a lamp that is initially turned off.
//
// You are given a 2D array of lamp positions lamps, where lamps[i] = [rowi, coli] indicates that the lamp at grid[rowi][coli] is turned on. Even if the same lamp is listed more than once, it is turned on.
//
// When a lamp is turned on, it illuminates its cell and all other cells in the same row, column, or diagonal.
//
// You are also given another 2D array queries, where queries[j] = [rowj, colj]. For the jth query, determine whether grid[rowj][colj] is illuminated or not. After answering the jth query, turn off the lamp at grid[rowj][colj] and its 8 adjacent lamps if they exist. A lamp is adjacent if its cell shares either a side or corner with grid[rowj][colj].
//
// Return an array of integers ans, where ans[j] should be 1 if the cell in the jth query was illuminated, or 0 if the lamp was not.
//
// Example:
// Input: n = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
// Output: [1,0]
// Explanation: We have the initial grid with all lamps turned off. In the above picture we see the grid after turning on the lamp at grid[0][0] then turning on the lamp at grid[4][4].
// The 0th query asks if the lamp at grid[1][1] is illuminated or not (the blue square). It is illuminated, so set ans[0] = 1. Then, we turn off all lamps in the red square.
//
// The 1st query asks if the lamp at grid[1][0] is illuminated or not (the blue square). It is not illuminated, so set ans[1] = 0. Then, we turn off all lamps in the red rectangle.
//
// Constraints:
// 1 <= n <= 109
// 	0 <= lamps.length <= 20000
// 	0 <= queries.length <= 20000
// 	lamps[i].length == 2
// 	0 <= rowi, coli < n
// 	queries[j].length == 2
// 	0 <= rowj, colj < n
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* gridIllumination(int n, int** lamps, int lampsSize, int* lampsColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;
    *returnSize = queriesSize;
    int *results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) return NULL;

    /* Use hash maps to track counts of lamps in rows, columns, diagonals */
    #define HASH_SIZE 100003
    typedef struct HashNode {
        long long key;
        int count;
        struct HashNode* next;
    } HashNode;

    HashNode** rowMap = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    HashNode** colMap = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    HashNode** diag1Map = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    HashNode** diag2Map = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));

    if (!rowMap || !colMap || !diag1Map || !diag2Map) {
        free(results);
        free(rowMap); free(colMap); free(diag1Map); free(diag2Map);
        return NULL;
    }

    #define HASH_FUNC(key) ((unsigned long long)(key) % HASH_SIZE)

    void addLamp(int r, int c) {
        long long rowKey = r;
        long long colKey = c;
        long long diag1Key = r - c + n; // offset to avoid negative
        long long diag2Key = r + c;

        HashNode **maps[] = {rowMap, colMap, diag1Map, diag2Map};
        long long keys[] = {rowKey, colKey, diag1Key, diag2Key};

        for (int i = 0; i < 4; ++i) {
            long long key = keys[i];
            unsigned long long h = HASH_FUNC(key);
            HashNode *node = maps[i][h];
            while (node) {
                if (node->key == key) {
                    node->count++;
                    break;
                }
                node = node->next;
            }
            if (!node) {
                node = (HashNode*)malloc(sizeof(HashNode));
                if (!node) return; // allocation failure
                node->key = key; node->count = 1; node->next = maps[i][h];
                maps[i][h] = node;
            }
        }
    }   
    void removeLamp(int r, int c) {
        long long rowKey = r;
        long long colKey = c;
        long long diag1Key = r - c + n;
        long long diag2Key = r + c;

        HashNode **maps[] = {rowMap, colMap, diag1Map, diag2Map};
        long long keys[] = {rowKey, colKey, diag1Key, diag2Key};

        for (int i = 0; i < 4; ++i) {
            long long key = keys[i];
            unsigned long long h = HASH_FUNC(key);
            HashNode *node = maps[i][h];
            HashNode *prev = NULL;
            while (node) {
                if (node->key == key) {
                    node->count--;
                    if (node->count == 0) {
                        if (prev) prev->next = node->next;
                        else maps[i][h] = node->next;
                        free(node);
                    }
                    break;
                }
                prev = node;
                node = node->next;
            }
        }
    }
    int isIlluminated(int r, int c) {
        long long rowKey = r;
        long long colKey = c;
        long long diag1Key = r - c + n;
        long long diag2Key = r + c;

        HashNode **maps[] = {rowMap, colMap, diag1Map, diag2Map};
        long long keys[] = {rowKey, colKey, diag1Key, diag2Key};

        for (int i = 0; i < 4; ++i) {
            long long key = keys[i];
            unsigned long long h = HASH_FUNC(key);
            HashNode *node = maps[i][h];
            while (node) {
                if (node->key == key) {
                    if (node->count > 0) return 1;
                    else break;
                }
                node = node->next;
            }
        }
        return 0;
    }
    /* Initialize lamps */
    for (int i = 0; i < lampsSize; ++i) {
        int r = lamps[i][0];
        int c = lamps[i][1];
        addLamp(r, c);
    }
    /* Process queries */
    int directions[9][2] = {
        {0, 0}, {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    for (int i = 0; i < queriesSize; ++i) {
        int r = queries[i][0];
        int c = queries[i][1];
        results[i] = isIlluminated(r, c);
        /* Turn off the lamp at (r, c) and its adjacent lamps */
        for (int d = 0; d < 9; ++d) {
            int nr = r + directions[d][0];
            int nc = c + directions[d][1];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                removeLamp(nr, nc);
            }
        }
    }
    /* Free allocated memory */
    for (int i = 0; i < HASH_SIZE; ++i) {
        HashNode *node;
        // Free rowMap
        node = rowMap[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
        // Free colMap
        node = colMap[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
        // Free diag1Map
        node = diag1Map[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
        // Free diag2Map
        node = diag2Map[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(rowMap);
    free(colMap);
    free(diag1Map);
    free(diag2Map);
    return results;    
}
