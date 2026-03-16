// Source: https://leetcode.com/problems/minimum-genetic-mutation/   |   Difficulty: Medium
//
// Problem Description:
// A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.
//
// Suppose we need to investigate a mutation from a gene string startGene to a gene string endGene where one mutation is defined as one single character changed in the gene string.
//
//
// 	For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
//
//
// There is also a gene bank bank that records all the valid gene mutations. A gene must be in bank to make it a valid gene string.
//
// Given the two gene strings startGene and endGene and the gene bank bank, return the minimum number of mutations needed to mutate from startGene to endGene. If there is no such a mutation, return -1.
//
// Note that the starting point is assumed to be valid, so it might not be included in the bank.
//
// Example:
// Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
// Output: 1
//
// Constraints:
// 0 <= bank.length <= 10
// 	startGene.length == endGene.length == bank[i].length == 8
// 	startGene, endGene, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minMutation(char* startGene, char* endGene, char** bank, int bankSize) {
    const char genes[] = {'A', 'C', 'G', 'T'};
    int visited[bankSize];
    for (int i = 0; i < bankSize; i++) {
        visited[i] = 0;
    }

    typedef struct {
        char gene[9];
        int steps;
    } Node;

    Node queue[10000];
    int front = 0, rear = 0;

    Node startNode;
    for (int i = 0; i < 9; i++) {
        startNode.gene[i] = startGene[i];
    }
    startNode.steps = 0;
    queue[rear++] = startNode;

    while (front < rear) {
        Node current = queue[front++];
        if (strcmp(current.gene, endGene) == 0) {
            return current.steps;
        }

        for (int i = 0; i < bankSize; i++) {
            if (visited[i]) continue;

            int diff = 0;
            for (int j = 0; j < 8; j++) {
                if (current.gene[j] != bank[i][j]) {
                    diff++;
                }
            }

            if (diff == 1) {
                visited[i] = 1;
                Node nextNode;
                for (int j = 0; j < 9; j++) {
                    nextNode.gene[j] = bank[i][j];
                }
                nextNode.steps = current.steps + 1;
                queue[rear++] = nextNode;
            }
        }
    }

    return -1;      
}
