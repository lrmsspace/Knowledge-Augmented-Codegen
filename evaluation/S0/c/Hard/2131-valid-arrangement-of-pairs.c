// Source: https://leetcode.com/problems/valid-arrangement-of-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.
//
// Return any valid arrangement of pairs.
//
// Note: The inputs will be generated such that there exists a valid arrangement of pairs.
//
// Example:
// Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
// Output: [[11,9],[9,4],[4,5],[5,1]]
// Explanation:
// This is a valid arrangement since endi-1 always equals starti.
// end0 = 9 == 9 = start1 
// end1 = 4 == 4 = start2
// end2 = 5 == 5 = start3
//
// Constraints:
// 1 <= pairs.length <= 105
// 	pairs[i].length == 2
// 	0 <= starti, endi <= 109
// 	starti != endi
// 	No two pairs are exactly the same.
// 	There exists a valid arrangement of pairs.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** validArrangement(int** pairs, int pairsSize, int* pairsColSize, int* returnSize, int** returnColumnSizes) {
    if (!returnSize || !returnColumnSizes || pairsSize <= 0 || !pairsColSize || pairsColSize[0] != 2) {
        return NULL;
    }

    /* Build graph and in/out degree maps */
    #define MAX_NODES 200000
    typedef struct Node {
        int to;
        struct Node* next;
    } Node;

    Node* graph[MAX_NODES] = {0};
    int outDegree[MAX_NODES] = {0};
    int inDegree[MAX_NODES] = {0};
    int offset = 1000000000; /* to handle negative indices */

    for (int i = 0; i < pairsSize; ++i) {
        int u = pairs[i][0] + offset;
        int v = pairs[i][1] + offset;

        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) return NULL; /* allocation failure */
        newNode->to = v;
        newNode->next = graph[u];
        graph[u] = newNode;

        outDegree[u]++;
        inDegree[v]++;
    }

    /* Find starting node for Eulerian path */
    int startNode = -1;
    for (int i = 0; i < MAX_NODES; ++i) {
        if (outDegree[i] - inDegree[i] == 1) {
            startNode = i;
            break;
        }
    }
    if (startNode == -1) {
        for (int i = 0; i < MAX_NODES; ++i) {
            if (outDegree[i] > 0) {
                startNode = i;
                break;
            }
        }
    }

    /* Hierholzer's algorithm for Eulerian path */
    int* stack = (int*)malloc((pairsSize + 1) * sizeof(int));
    int stackSize = 0;
    int* result = (int*)malloc(pairsSize * 2 * sizeof(int));
    int resultSize = 0;

    if (!stack || !result) return NULL; /* allocation failure */

    stack[stackSize++] = startNode;

    while (stackSize > 0) {
        int u = stack[--stackSize];
        while (graph[u]) {
            Node* nextNode = graph[u];
            graph[u] = graph[u]->next;
            stack[stackSize++] = nextNode->to;
            free(nextNode);
            u = stack[--stackSize];
        }
        if (stackSize < pairsSize + 1) {
            result[resultSize++] = u - offset;
        }
    }
    /* Prepare return values */
    *returnSize = pairsSize;
    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));
    int** arrangedPairs = (int**)malloc((*returnSize) * sizeof(int*));
    for (int i = 0; i < *returnSize; ++i) {
        arrangedPairs[i] = (int*)malloc(2 * sizeof(int));
        arrangedPairs[i][0] = result[(*returnSize - 1 - i) * 2];
        arrangedPairs[i][1] = result[(*returnSize - 1 - i) * 2 + 1];
        (*returnColumnSizes)[i] = 2;
    }
    free(stack);
    free(result);
    return arrangedPairs;
}
