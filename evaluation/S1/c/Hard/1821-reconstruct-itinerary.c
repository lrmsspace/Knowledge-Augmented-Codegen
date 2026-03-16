// Source: https://leetcode.com/problems/reconstruct-itinerary/   |   Difficulty: Hard
//
// Problem Description:
// You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.
//
// All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.
//
//
// 	For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
//
//
// You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.
//
// Example:
// Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
// Output: ["JFK","MUC","LHR","SFO","SJC"]
//
// Constraints:
// 1 <= tickets.length <= 300
// 	tickets[i].length == 2
// 	fromi.length == 3
// 	toi.length == 3
// 	fromi and toi consist of uppercase English letters.
// 	fromi != toi
//
// Helpful references (internal KB):
// - Depth-first search (graph, array, dfs, biconnected-components)
//   • When to use: Use when exploring all reachable nodes from a starting point, finding paths, or detecting cycles in a graph. It's suitable for problems requiring a deep, exhaustive search.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs represented with adjacency lists.
//   • Invariants: Every node `v` is visited exactly once.; When `dfs(G, u, v)` is called, `v` is unvisited and `u` is its immediate predecessor in the current path.
//   • Tips: Maintain a visited set/array to avoid revisiting nodes and infinite loops.; Pass the parent node in recursive calls to correctly identify back-edges for cycle detection.
//   • Pitfalls: Failing to mark nodes as visited can lead to infinite loops in cyclic graphs.; Deep recursion can cause stack overflow errors on large graphs; use an iterative approach if needed.
// - Finding the Eulerian path in O(M) (graph, eulerian-circuit, dfs)
//   • When to use: Use when you need to find a path or cycle that traverses every edge exactly once in a given graph. It's applicable when specific vertex degree conditions are met for path or cycle existence.
//   • Idea: This algorithm constructs an Eulerian path or cycle by first verifying vertex degree conditions and graph connectivity, then performing a recursive DFS-like traversal to build the path. It achieves a time complexity of O(M), where M is the number of edges.
//   • Invariants: Every edge in the constructed path has been traversed exactly once.; All edges incident to the current vertex have been explored or are part of the remaining graph.
//   • Tips: Verify graph connectivity, ignoring isolated vertices.; For an Eulerian path, ensure exactly two vertices have odd degrees.
//   • Pitfalls: Failing to check graph connectivity before starting.; Incorrectly counting odd degree vertices for path vs. cycle.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
char** findItinerary(char*** tickets, int ticketsSize, int* ticketsColSize, int* returnSize) {
    /* Build adjacency list */
    #define MAX_AIRPORTS 1000
    #define MAX_TICKETS 300
    typedef struct Node {
        char dest[4];
        struct Node* next;
    } Node;

    Node* adj[MAX_AIRPORTS] = {0};
    int airportCount = 0;
    char airports[MAX_AIRPORTS][4];

    int getAirportIndex(const char* code) {
        for (int i = 0; i < airportCount; i++) {
            if (strcmp(airports[i], code) == 0) return i;
        }
        strcpy(airports[airportCount], code);
        return airportCount++;
    }

    for (int i = 0; i < ticketsSize; i++) {
        int fromIdx = getAirportIndex(tickets[i][0]);
        Node* newNode = (Node*)malloc(sizeof(Node));
        strcpy(newNode->dest, tickets[i][1]);
        newNode->next = adj[fromIdx];
        adj[fromIdx] = newNode;
    }

    /* Sort adjacency lists to ensure lexical order */
    for (int i = 0; i < airportCount; i++) {
        // Simple insertion sort for linked list
        Node* sorted = NULL;
        Node* current = adj[i];
        while (current) {
            Node* next = current->next;
            if (!sorted || strcmp(current->dest, sorted->dest) < 0) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;
                while (temp->next && strcmp(temp->next->dest, current->dest) < 0) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        adj[i] = sorted;
    }

    /* Hierholzer's algorithm to find Eulerian path */
    char** result = (char**)malloc((ticketsSize + 1) * sizeof(char*));
    int resultIdx = ticketsSize;
    void dfs(int airportIdx) {
        Node* node = adj[airportIdx];
        while (node) {
            int nextIdx = getAirportIndex(node->dest);
            Node* temp = node;
            node = node->next;
            adj[airportIdx] = node; // Remove edge
            dfs(nextIdx);
            free(temp); // Free used edge
        }
        result[resultIdx--] = (char*)malloc(4 * sizeof(char));
        strcpy(result[resultIdx + 1], airports[airportIdx]);
    }
    int startIdx = getAirportIndex("JFK");
    dfs(startIdx);
    *returnSize = ticketsSize + 1;
    return result;
}
