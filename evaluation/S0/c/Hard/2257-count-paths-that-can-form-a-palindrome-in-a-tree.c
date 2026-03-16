// Source: https://leetcode.com/problems/count-paths-that-can-form-a-palindrome-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted at node 0 consisting of n nodes numbered from 0 to n - 1. The tree is represented by a 0-indexed array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to the edge between i and parent[i]. s[0] can be ignored.
//
// Return the number of pairs of nodes (u, v) such that u < v and the characters assigned to edges on the path from u to v can be rearranged to form a palindrome.
//
// A string is a palindrome when it reads the same backwards as forwards.
//
// Example:
// Input: parent = [-1,0,0,1,1,2], s = "acaabc"
// Output: 8
// Explanation: The valid pairs are:
// - All the pairs (0,1), (0,2), (1,3), (1,4) and (2,5) result in one character which is always a palindrome.
// - The pair (2,3) result in the string "aca" which is a palindrome.
// - The pair (1,5) result in the string "cac" which is a palindrome.
// - The pair (3,5) result in the string "acac" which can be rearranged into the palindrome "acca".
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists of only lowercase English letters.
//

long long countPalindromePaths(int* parent, int parentSize, char* s) {
    int n = parentSize;
    int *childrenCount = (int*)calloc(n, sizeof(int));
    for (int i = 1; i < n; ++i) {
        childrenCount[parent[i]]++;
    }

    int **children = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        if (childrenCount[i] > 0) {
            children[i] = (int*)malloc(childrenCount[i] * sizeof(int));
            childrenCount[i] = 0; /* reuse to track insertion index */
        } else {
            children[i] = NULL;
        }
    }
    for (int i = 1; i < n; ++i) {
        int p = parent[i];
        children[p][childrenCount[p]++] = i;
    }

    long long result = 0;

    /* DFS post-order traversal to calculate masks and count pairs */
    int *stack = (int*)malloc(n * sizeof(int));
    int *mask = (int*)calloc(n, sizeof(int));
    int *state = (int*)calloc(n, sizeof(int)); /* 0: to visit, 1: visiting, 2: visited */
    int top = 0;
    stack[top++] = 0;

    /* Hash map to count masks */
    #define HASH_SIZE 131071
    typedef struct HashNode {
        int key;
        long long count;
        struct HashNode* next;
    } HashNode;

    HashNode** hashTable = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));

    auto hashFunc = [](int key) {
        return ((unsigned int)key) % HASH_SIZE;
    };

    auto hashInsert = [&](int key) {
        int h = hashFunc(key);
        HashNode* node = hashTable[h];
        while (node) {
            if (node->key == key) {
                node->count++;
                return;
            }
            node = node->next;
        }
        node = (HashNode*)malloc(sizeof(HashNode));
        node->key = key;
        node->count = 1;
        node->next = hashTable[h];
        hashTable[h] = node;
    };

    auto hashGetCount = [&](int key) {
        int h = hashFunc(key);
        HashNode* node = hashTable[h];
        while (node) {
            if (node->key == key) {
                return node->count;
            }
            node = node->next;
        }
        return 0LL;
    };
    while (top > 0) {
        int node = stack[top - 1];
        if (state[node] == 0) {
            state[node] = 1; /* visiting */
            for (int i = 0; i < childrenCount[node]; ++i) {
                stack[top++] = children[node][i];
            }
        } else if (state[node] == 1) {
            state[node] = 2; /* visited */
            top--;

            /* Calculate mask for current node */
            int currMask = 0;
            for (int i = 0; i < childrenCount[node]; ++i) {
                int child = children[node][i];
                currMask ^= mask[child];
            }
            currMask ^= (1 << (s[node] - 'a'));
            mask[node] = currMask;

            /* Count pairs */
            result += hashGetCount(currMask);
            for (int b = 0; b < 26; ++b) {
                result += hashGetCount(currMask ^ (1 << b));
            }

            /* Insert current mask into hash map */
            hashInsert(currMask);
        } else {
            top--;
        }
    }
    /* Free memory */
    for (int i = 0; i < n; ++i) {
        if (children[i]) free(children[i]);
    }
    free(children);
    free(childrenCount);
    free(stack);
    free(mask);
    free(state);
    for (int i = 0; i < HASH_SIZE; ++i) {
        HashNode* node = hashTable[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(hashTable);
    return result; 
}
