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
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        // Step 1: Create a copy of each node and insert it right after the original node.
        Node* curr = head;
        while (curr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }

        // Step 2: Assign random pointers for the copied nodes.
        curr = head;
        while (curr) {
            if (curr->random) {
                curr->next->random = curr->random->next; // Point to the copied random node
            }
            curr = curr->next->next; // Move to the next original node
        }

        // Step 3: Separate the original and copied nodes to form the final copied list.
        Node* pseudoHead = new Node(0); // A dummy node to help with separation
        Node* copyCurr = pseudoHead;
        curr = head;

        while (curr) {
            copyCurr->next = curr->next; // Link the copied node
            copyCurr = copyCurr->next;    // Move to the next copied node

            curr->next = curr->next->next; // Restore the original list
            curr = curr->next;             // Move to the next original node
        }

        return pseudoHead->next; // Return the head of the copied list          
    }
};
