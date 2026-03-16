// Source: https://leetcode.com/problems/copy-list-with-random-pointer/   |   Difficulty: Medium
//
// Problem Description:
// A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.
//
// Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.
//
// For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.
//
// Return the head of the copied linked list.
//
// The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:
//
//
// 	val: an integer representing Node.val
// 	random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
//
//
// Your code will only be given the head of the original linked list.
//
// Example:
// Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
//
// Constraints:
// 0 <= n <= 1000
// 	-104 <= Node.val <= 104
// 	Node.random is null or is pointing to some node in the linked list.
//
// Helpful references (internal KB):
// - Linked-list implementations of collections (linked-list, ds, simulation)
//   • When to use: When you need dynamic collections that efficiently support insertions and deletions at specific points, or when memory usage needs to be precisely managed without contiguous memory allocation.
//   • Idea: This describes how fundamental data structures like stacks, queues, and bags can be implemented using linked lists, providing dynamic resizing and efficient element manipulation. Operations typically achieve O(1) time complexity for additions and removals at the ends.
//   • Invariants: The head pointer always points to the first element, or is null if the list is empty.; The tail pointer always points to the last element, or is null if the list is empty.
//   • Tips: Use a Node class to encapsulate data and a reference to the next element.; Maintain head and tail pointers for efficient O(1) operations in queues.
//   • Pitfalls: Forgetting to handle edge cases like empty lists or single-element lists.; Introducing 'loitering' by not nullifying references to removed objects, preventing garbage collection.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Hash Tables (array, linked-list, hashing)
//   • When to use: Use when efficient average-case O(1) insertion, deletion, and lookup of data based on keys is required, especially for non-integer or complex key types.
//   • Idea: Hash tables store key-value pairs by mapping keys to array indices using a hash function, aiming for O(1) average-case time complexity for basic operations. Collisions are handled to ensure correctness and data integrity.
//   • Invariants: Each key maps to a unique value, or collisions are correctly resolved and handled.; The hash function consistently produces the same hash value for identical keys.
//   • Tips: Choose a good hash function to minimize collisions and distribute keys uniformly across buckets.; Use prime numbers for modular arithmetic in polynomial hashing to reduce collision frequency.
//   • Pitfalls: A poorly designed hash function can lead to frequent collisions and degrade performance to O(N) in the worst case.; Forgetting to handle integer overflow during hash computation, especially with large multipliers or long keys.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

struct Node* copyRandomList(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }

    // Step 1: Create new nodes and interleave them with original nodes
    struct Node* curr = head;
    while (curr != NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->val = curr->val;
        newNode->next = curr->next;
        newNode->random = NULL; // Will set this later
        curr->next = newNode;
        curr = newNode->next;
    }

    // Step 2: Set random pointers for the new nodes
    curr = head;
    while (curr != NULL) {
        if (curr->random != NULL) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }

    // Step 3: Separate the original and copied lists
    curr = head;
    struct Node* copiedHead = head->next;
    struct Node* copyCurr = copiedHead;

    while (curr != NULL) {
        curr->next = curr->next->next;
        if (copyCurr->next != NULL) {
            copyCurr->next = copyCurr->next->next;
        }
        curr = curr->next;
        copyCurr = copyCurr->next;
    }

    return copiedHead;  	
}
