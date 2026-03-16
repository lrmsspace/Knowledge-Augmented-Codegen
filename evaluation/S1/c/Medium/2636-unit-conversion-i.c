// Source: https://leetcode.com/problems/unit-conversion-i/   |   Difficulty: Medium
//
// Problem Description:
// There are n types of units indexed from 0 to n - 1. You are given a 2D integer array conversions of length n - 1, where conversions[i] = [sourceUniti, targetUniti, conversionFactori]. This indicates that a single unit of type sourceUniti is equivalent to conversionFactori units of type targetUniti.
//
// Return an array baseUnitConversion of length n, where baseUnitConversion[i] is the number of units of type i equivalent to a single unit of type 0. Since the answer may be large, return each baseUnitConversion[i] modulo 109 + 7.
//
// Example:
// Input: conversions = [[0,1,2],[1,2,3]]
//
// Output: [1,2,6]
//
// Explanation:
//
//
// 	Convert a single unit of type 0 into 2 units of type 1 using conversions[0].
// 	Convert a single unit of type 0 into 6 units of type 2 using conversions[0], then conversions[1].
//
// Constraints:
// 2 <= n <= 105
// 	conversions.length == n - 1
// 	0 <= sourceUniti, targetUniti < n
// 	1 <= conversionFactori <= 109
// 	It is guaranteed that unit 0 can be converted into any other unit through a unique combination of conversions without using any conversions in the opposite direction.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* baseUnitConversions(int** conversions, int conversionsSize, int* conversionsColSize, int* returnSize) {
    int n = conversionsSize + 1;
    const int MOD = 1000000007;

    // Build adjacency list
    typedef struct Node {
        int target;
        long long factor;
        struct Node* next;
    } Node;

    Node** graph = (Node**)calloc(n, sizeof(Node*));
    for (int i = 0; i < conversionsSize; i++) {
        int src = conversions[i][0];
        int tgt = conversions[i][1];
        long long factor = conversions[i][2];

        Node* newNode1 = (Node*)malloc(sizeof(Node));
        newNode1->target = tgt;
        newNode1->factor = factor;
        newNode1->next = graph[src];
        graph[src] = newNode1;

        Node* newNode2 = (Node*)malloc(sizeof(Node));
        newNode2->target = src;
        newNode2->factor = 1; // Inverse conversion
        newNode2->next = graph[tgt];
        graph[tgt] = newNode2;
    }

    // BFS to calculate conversions
    int* result = (int*)calloc(n, sizeof(int));
    result[0] = 1;

    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, back = 0;
    queue[back++] = 0;

    while (front < back) {
        int curr = queue[front++];
        Node* neighbor = graph[curr];
        while (neighbor) {
            int tgt = neighbor->target;
            if (result[tgt] == 0) {
                result[tgt] = (result[curr] * neighbor->factor) % MOD;
                queue[back++] = tgt;
            }
            neighbor = neighbor->next;
        }
    }

    // Free graph memory
    for (int i = 0; i < n; i++) {
        Node* curr = graph[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph);
    free(queue);

    *returnSize = n;
    return result;      
}
