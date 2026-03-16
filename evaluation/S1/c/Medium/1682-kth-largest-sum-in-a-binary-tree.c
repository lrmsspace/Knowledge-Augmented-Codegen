// Source: https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and a positive integer k.
//
// The level sum in the tree is the sum of the values of the nodes that are on the same level.
//
// Return the kth largest level sum in the tree (not necessarily distinct). If there are fewer than k levels in the tree, return -1.
//
// Note that two nodes are on the same level if they have the same distance from the root.
//
// Example:
// Input: root = [5,8,9,2,1,3,7,4,6], k = 2
// Output: 13
// Explanation: The level sums are the following:
// - Level 1: 5.
// - Level 2: 8 + 9 = 17.
// - Level 3: 2 + 1 + 3 + 7 = 13.
// - Level 4: 4 + 6 = 10.
// The 2nd largest level sum is 13.
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= 106
// 	1 <= k <= n
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
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
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
long long kthLargestLevelSum(struct TreeNode* root, int k) {
    #define MAX_HEAP_SIZE 100005

    typedef struct {
        long long data[MAX_HEAP_SIZE];
        int size;
    } MinHeap;

    void minHeapInit(MinHeap* heap) {
        heap->size = 0;
    }

    void minHeapInsert(MinHeap* heap, long long value) {
        if (heap->size < k) {
            heap->data[heap->size++] = value;
            int i = heap->size - 1;
            while (i > 0) {
                int parent = (i - 1) / 2;
                if (heap->data[parent] <= heap->data[i]) break;
                long long temp = heap->data[parent];
                heap->data[parent] = heap->data[i];
                heap->data[i] = temp;
                i = parent;
            }
        } else if (value > heap->data[0]) {
            heap->data[0] = value;
            int i = 0;
            while (1) {
                int left = 2 * i + 1;
                int right = 2 * i + 2;
                int smallest = i;
                if (left < heap->size && heap->data[left] < heap->data[smallest]) smallest = left;
                if (right < heap->size && heap->data[right] < heap->data[smallest]) smallest = right;
                if (smallest == i) break;
                long long temp = heap->data[i];
                heap->data[i] = heap->data[smallest];
                heap->data[smallest] = temp;
                i = smallest;
            }
        }
    }

    #undef MAX_HEAP_SIZE

    #define QUEUE_SIZE 100005

    typedef struct {
        struct TreeNode* data[QUEUE_SIZE];
        int front, rear;
    } Queue;

    void queueInit(Queue* q) {
        q->front = q->rear = 0;
    }

    int queueIsEmpty(Queue* q) {
        return q->front == q->rear;
    }

    void queueEnqueue(Queue* q, struct TreeNode* node) {
        q->data[q->rear++] = node;
    }

    struct TreeNode* queueDequeue(Queue* q) {
        return q->data[q->front++];
    }       

    MinHeap heap;
    minHeapInit(&heap);
    Queue queue;
    queueInit(&queue);
    queueEnqueue(&queue, root);
    while (!queueIsEmpty(&queue)) {
        int levelSize = queue.rear - queue.front;
        long long levelSum = 0;
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queueDequeue(&queue);
            levelSum += node->val;
            if (node->left) queueEnqueue(&queue, node->left);
            if (node->right) queueEnqueue(&queue, node->right);
        }
        minHeapInsert(&heap, levelSum);
    }
    if (heap.size < k) return -1;
    return heap.data[0];
}
