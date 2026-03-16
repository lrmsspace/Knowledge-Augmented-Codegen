// Source: https://leetcode.com/problems/maximum-genetic-difference-query/   |   Difficulty: Hard
//
// Problem Description:
// There is a rooted tree consisting of n nodes numbered 0 to n - 1. Each node's number denotes its unique genetic value (i.e. the genetic value of node x is x). The genetic difference between two genetic values is defined as the bitwise-XOR of their values. You are given the integer array parents, where parents[i] is the parent for node i. If node x is the root of the tree, then parents[x] == -1.
//
// You are also given the array queries where queries[i] = [nodei, vali]. For each query i, find the maximum genetic difference between vali and pi, where pi is the genetic value of any node that is on the path between nodei and the root (including nodei and the root). More formally, you want to maximize vali XOR pi.
//
// Return an array ans where ans[i] is the answer to the ith query.
//
// Example:
// Input: parents = [-1,0,1,1], queries = [[0,2],[3,2],[2,5]]
// Output: [2,3,7]
// Explanation: The queries are processed as follows:
// - [0,2]: The node with the maximum genetic difference is 0, with a difference of 2 XOR 0 = 2.
// - [3,2]: The node with the maximum genetic difference is 1, with a difference of 2 XOR 1 = 3.
// - [2,5]: The node with the maximum genetic difference is 2, with a difference of 5 XOR 2 = 7.
//
// Constraints:
// 2 <= parents.length <= 105
// 	0 <= parents[i] <= parents.length - 1 for every node i that is not the root.
// 	parents[root] == -1
// 	1 <= queries.length <= 3 * 104
// 	0 <= nodei <= parents.length - 1
// 	0 <= vali <= 2 * 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxGeneticDifference(int* parents, int parentsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    if (!returnSize) return NULL;

    // Build adjacency list for the tree
    int n = parentsSize;
    int *head = (int*)calloc(n, sizeof(int));
    int *next = (int*)calloc(n - 1, sizeof(int));
    int *to = (int*)calloc(n - 1, sizeof(int));
    if (!head || !next || !to) {
        free(head); free(next); free(to);
        return NULL; // allocation failure
    }
    memset(head, -1, n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        if (parents[i] != -1) {
            to[i - 1] = i;
            next[i - 1] = head[parents[i]];
            head[parents[i]] = i - 1;
        }
    }

    // Prepare queries per node
    typedef struct Query {
        int val;
        int index;
        struct Query* next;
    } Query;

    Query** queryList = (Query**)calloc(n, sizeof(Query*));
    if (!queryList) {
        free(head); free(next); free(to);
        return NULL; // allocation failure
    }
    for (int i = 0; i < queriesSize; ++i) {
        int node = queries[i][0];
        Query* q = (Query*)malloc(sizeof(Query));
        if (!q) {
            // Free previously allocated memory
            for (int j = 0; j < n; ++j) {
                Query* curr = queryList[j];
                while (curr) {
                    Query* temp = curr;
                    curr = curr->next;
                    free(temp);
                }
            }
            free(queryList);
            free(head); free(next); free(to);
            return NULL; // allocation failure
        }
        q->val = queries[i][1];
        q->index = i;
        q->next = queryList[node];
        queryList[node] = q;
    }

    // Trie structure for XOR maximization
    typedef struct TrieNode {
        struct TrieNode* children[2];
        int count;
    } TrieNode;

    TrieNode* createTrieNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        node->children[0] = NULL;
        node->children[1] = NULL;
        node->count = 0;
        return node;
    }
    void insert(TrieNode* root, int num) {
        TrieNode* curr = root;
        for (int i = 17; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!curr->children[bit]) {
                curr->children[bit] = createTrieNode();
            }
            curr = curr->children[bit];
            curr->count++;
        }
    }
    void removeNum(TrieNode* root, int num) {
        TrieNode* curr = root;
        for (int i = 17; i >= 0; --i) {
            int bit = (num >> i) & 1;
            curr = curr->children[bit];
            curr->count--;
        }
    }
    int getMaxXOR(TrieNode* root, int num) {
        TrieNode* curr = root;
        int maxXOR = 0;
        for (int i = 17; i >= 0; --i) {
            int bit = (num >> i) & 1;
            int toggledBit = 1 - bit;
            if (curr->children[toggledBit] && curr->children[toggledBit]->count > 0) {
                maxXOR |= (1 << i);
                curr = curr->children[toggledBit];
            } else {
                curr = curr->children[bit];
            }
        }
        return maxXOR;
    }
    int* results = (int*)malloc(queriesSize * sizeof(int));
    if (!results) {
        // Free previously allocated memory
        for (int j = 0; j < n; ++j) {
            Query* curr = queryList[j];
            while (curr) {
                Query* temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(queryList);
        free(head); free(next); free(to);
        return NULL; // allocation failure
    }
    TrieNode* trieRoot = createTrieNode();
    void dfs(int node) {
        insert(trieRoot, node);
        // Process queries for this node
        Query* q = queryList[node];
        while (q) {
            results[q->index] = getMaxXOR(trieRoot, q->val);
            q = q->next;
        }
        // Traverse children
        for (int i = head[node]; i != -1; i = next[i]) {
            int child = to[i];
            dfs(child);
        }
        removeNum(trieRoot, node);
    }
    // Find root and start DFS
    int root = -1;
    for (int i = 0; i < n; ++i) {
        if (parents[i] == -1) {
            root = i;
            break;
        }
    }
    dfs(root);
    // Cleanup
    for (int j = 0; j < n; ++j) {
        Query* curr = queryList[j];
        while (curr) {
            Query* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(queryList);
    free(head); free(next); free(to);
    // Free trie
    void freeTrie(TrieNode* node) {
        if (!node) return;
        freeTrie(node->children[0]);
        freeTrie(node->children[1]);
        free(node);
    }
    freeTrie(trieRoot);
    *returnSize = queriesSize;
    return results; 
}
