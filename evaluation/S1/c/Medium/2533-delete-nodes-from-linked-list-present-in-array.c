// Source: https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums and the head of a linked list. Return the head of the modified linked list after removing all nodes from the linked list that have a value that exists in nums.
//
// Example:
// Input: nums = [1,2,3], head = [1,2,3,4,5]
//
// Output: [4,5]
//
// Explanation:
//
//
//
// Remove the nodes with values 1, 2, and 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	All elements in nums are unique.
// 	The number of nodes in the given list is in the range [1, 105].
// 	1 <= Node.val <= 105
// 	The input is generated such that there is at least one node in the linked list that has a value not present in nums.
//
// Helpful references (internal KB):
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Linked-list implementations of collections (linked-list, ds, simulation)
//   • When to use: When you need dynamic collections that efficiently support insertions and deletions at specific points, or when memory usage needs to be precisely managed without contiguous memory allocation.
//   • Idea: This describes how fundamental data structures like stacks, queues, and bags can be implemented using linked lists, providing dynamic resizing and efficient element manipulation. Operations typically achieve O(1) time complexity for additions and removals at the ends.
//   • Invariants: The head pointer always points to the first element, or is null if the list is empty.; The tail pointer always points to the last element, or is null if the list is empty.
//   • Tips: Use a Node class to encapsulate data and a reference to the next element.; Maintain head and tail pointers for efficient O(1) operations in queues.
//   • Pitfalls: Forgetting to handle edge cases like empty lists or single-element lists.; Introducing 'loitering' by not nullifying references to removed objects, preventing garbage collection.
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* modifiedList(int* nums, int numsSize, struct ListNode* head) {
    // Create a hash table to store the values in nums
    int maxVal = 100000; // Given constraint: 1 <= Node.val <= 10^5
    char hashTable[maxVal + 1];
    for (int i = 0; i <= maxVal; i++) {
        hashTable[i] = 0;
    }
    for (int i = 0; i < numsSize; i++) {
        hashTable[nums[i]] = 1;
    }

    // Create a dummy node to simplify edge cases
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;
    struct ListNode* curr = head;

    // Traverse the linked list and remove nodes present in nums
    while (curr != NULL) {
        if (hashTable[curr->val]) {
            // Node value is in nums, remove it
            prev->next = curr->next;
            struct ListNode* temp = curr;
            curr = curr->next;
            // Optionally free the removed node
            // free(temp);
        } else {
            // Node value is not in nums, move to the next node
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;      
}
