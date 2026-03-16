// Source: https://leetcode.com/problems/path-crossing/   |   Difficulty: Easy
//
// Problem Description:
// Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk on the path specified by path.
//
// Return true if the path crosses itself at any point, that is, if at any time you are on a location you have previously visited. Return false otherwise.
//
// Example:
// Input: path = "NES"
// Output: false 
// Explanation: Notice that the path doesn't cross any point more than once.
//
// Constraints:
// 1 <= path.length <= 104
// 	path[i] is either 'N', 'S', 'E', or 'W'.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isPathCrossing(char* path) {
    // Using a hash set to store visited coordinates
    #define HASH_SIZE 20011  // A prime number for better distribution
    typedef struct Node {
        int x;
        int y;
        struct Node* next;
    } Node;

    Node* hashTable[HASH_SIZE] = {0};

    int hash(int x, int y) {
        return ((x * 31 + y) % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
    }

    void insert(int x, int y) {
        int h = hash(x, y);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->x = x;
        newNode->y = y;
        newNode->next = hashTable[h];
        hashTable[h] = newNode;
    }

    bool exists(int x, int y) {
        int h = hash(x, y);
        Node* curr = hashTable[h];
        while (curr) {
            if (curr->x == x && curr->y == y) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    int x = 0, y = 0;
    insert(x, y);  // Starting point

    for (int i = 0; path[i] != '\0'; i++) {
        switch (path[i]) {
            case 'N': y++; break;
            case 'S': y--; break;
            case 'E': x++; break;
            case 'W': x--; break;
        }
        if (exists(x, y)) {
            // Free allocated memory before returning
            for (int j = 0; j < HASH_SIZE; j++) {
                Node* curr = hashTable[j];
                while (curr) {
                    Node* temp = curr;
                    curr = curr->next;
                    free(temp);
                }
            }
            return true;
        }
        insert(x, y);
    }

    // Free allocated memory before returning
    for (int j = 0; j < HASH_SIZE; j++) {
        Node* curr = hashTable[j];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return false;       
}
