// Source: https://leetcode.com/problems/remove-invalid-parentheses/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
//
// Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.
//
// Example:
// Input: s = "()())()"
// Output: ["(())()","()()()"]
//
// Constraints:
// 1 <= s.length <= 25
// 	s consists of lowercase English letters and parentheses '(' and ')'.
// 	There will be at most 20 parentheses in s.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
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
char** removeInvalidParentheses(char* s, int* returnSize) {
    // Function to check if a string has valid parentheses
    bool isValid(char* str) {
        int balance = 0;
        while (*str) {
            if (*str == '(') balance++;
            else if (*str == ')') {
                if (balance == 0) return false;
                balance--;
            }
            str++;
        }
        return balance == 0;
    }
    // BFS to find all valid strings with minimum removals
    typedef struct Node {
        char* str;
        struct Node* next;
    } Node;
    Node* createNode(char* str) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->str = str;
        node->next = NULL;
        return node;
    }
    Node* queueHead = createNode(s);
    Node* queueTail = queueHead;
    bool* visited = (bool*)calloc(10000, sizeof(bool));
    visited[0] = true;
    char** results = (char**)malloc(10000 * sizeof(char*));
    *returnSize = 0;    
    bool found = false;
    while (queueHead) {
        int levelSize = 0;
        Node* temp = queueHead;
        while (temp) {
            levelSize++;
            temp = temp->next;
        }
        for (int i = 0; i < levelSize; i++) {
            Node* currentNode = queueHead;
            queueHead = queueHead->next;
            char* currentStr = currentNode->str;
            free(currentNode);
            if (isValid(currentStr)) {
                results[*returnSize] = (char*)malloc((strlen(currentStr) + 1) * sizeof(char));
                strcpy(results[*returnSize], currentStr);
                (*returnSize)++;
                found = true;
            }
            if (found) continue; // Stop generating new states once a valid string is found
            for (int j = 0; currentStr[j]; j++) {
                if (currentStr[j] != '(' && currentStr[j] != ')') continue;
                char* newStr = (char*)malloc((strlen(currentStr)) * sizeof(char));
                strncpy(newStr, currentStr, j);
                strcpy(newStr + j, currentStr + j + 1);
                // Check if newStr has been visited
                bool alreadyVisited = false;
                for (int k = 0; k < *returnSize; k++) {
                    if (strcmp(results[k], newStr) == 0) {
                        alreadyVisited = true;
                        break;
                    }
                }
                if (!alreadyVisited) {
                    Node* newNode = createNode(newStr);
                    queueTail->next = newNode;
                    queueTail = newNode;
                } else {
                    free(newStr);
                }
            }
        }
        if (found) break;
    }
    // Cleanup remaining nodes in the queue
    while (queueHead) {
        Node* temp = queueHead;
        queueHead = queueHead->next;
        free(temp->str);
        free(temp);
    }   
    free(visited);
    return results;
}
