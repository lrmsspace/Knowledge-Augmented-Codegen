// Source: https://leetcode.com/problems/number-of-pairs-of-interchangeable-rectangles/   |   Difficulty: Medium
//
// Problem Description:
// You are given n rectangles represented by a 0-indexed 2D integer array rectangles, where rectangles[i] = [widthi, heighti] denotes the width and height of the ith rectangle.
//
// Two rectangles i and j (i < j) are considered interchangeable if they have the same width-to-height ratio. More formally, two rectangles are interchangeable if widthi/heighti == widthj/heightj (using decimal division, not integer division).
//
// Return the number of pairs of interchangeable rectangles in rectangles.
//
// Example:
// Input: rectangles = [[4,8],[3,6],[10,20],[15,30]]
// Output: 6
// Explanation: The following are the interchangeable pairs of rectangles by index (0-indexed):
// - Rectangle 0 with rectangle 1: 4/8 == 3/6.
// - Rectangle 0 with rectangle 2: 4/8 == 10/20.
// - Rectangle 0 with rectangle 3: 4/8 == 15/30.
// - Rectangle 1 with rectangle 2: 3/6 == 10/20.
// - Rectangle 1 with rectangle 3: 3/6 == 15/30.
// - Rectangle 2 with rectangle 3: 10/20 == 15/30.
//
// Constraints:
// n == rectangles.length
// 	1 <= n <= 105
// 	rectangles[i].length == 2
// 	1 <= widthi, heighti <= 105
//
// Helpful references (internal KB):
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
//   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
//   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
//   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
//   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
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

long long interchangeableRectangles(int** rectangles, int rectanglesSize, int* rectanglesColSize) {
    // Hash map to store the count of each width-to-height ratio
    #define HASH_MAP_SIZE 100003 // A large prime number for better distribution
    typedef struct HashNode {
        long long key;
        long long value;
        struct HashNode* next;
    } HashNode;

    HashNode* hashMap[HASH_MAP_SIZE] = {0};

    long long getHash(long long key) {
        return (key % HASH_MAP_SIZE + HASH_MAP_SIZE) % HASH_MAP_SIZE;
    }

    void put(long long key) {
        long long hashIndex = getHash(key);
        HashNode* node = hashMap[hashIndex];
        while (node) {
            if (node->key == key) {
                node->value++;
                return;
            }
            node = node->next;
        }
        // Not found, create new node
        HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
        newNode->key = key;
        newNode->value = 1;
        newNode->next = hashMap[hashIndex];
        hashMap[hashIndex] = newNode;
    }

    long long getValue(long long key) {
        long long hashIndex = getHash(key);
        HashNode* node = hashMap[hashIndex];
        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        return 0;
    }

    long long result = 0;

    for (int i = 0; i < rectanglesSize; i++) {
        int width = rectangles[i][0];
        int height = rectangles[i][1];
        long long gcd = 1;
        
        // Compute GCD using Euclidean algorithm
        int a = width, b = height;
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        gcd = a;

        long long ratioKey = ((long long)(width / gcd) << 32) | (height / gcd);
        
        long long count = getValue(ratioKey);
        result += count; // Add the number of previously seen rectangles with the same ratio
        put(ratioKey);   // Insert/update the current ratio in the hash map
    }

    // Free allocated memory for hash map    
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashNode* node = hashMap[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    return result;   
}
