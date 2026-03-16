// Source: https://leetcode.com/problems/relocate-marbles/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums representing the initial positions of some marbles. You are also given two 0-indexed integer arrays moveFrom and moveTo of equal length.
//
// Throughout moveFrom.length steps, you will change the positions of the marbles. On the ith step, you will move all marbles at position moveFrom[i] to position moveTo[i].
//
// After completing all the steps, return the sorted list of occupied positions.
//
// Notes:
//
//
// 	We call a position occupied if there is at least one marble in that position.
// 	There may be multiple marbles in a single position.
//
// Example:
// Input: nums = [1,6,7,8], moveFrom = [1,7,2], moveTo = [2,9,5]
// Output: [5,6,8,9]
// Explanation: Initially, the marbles are at positions 1,6,7,8.
// At the i = 0th step, we move the marbles at position 1 to position 2. Then, positions 2,6,7,8 are occupied.
// At the i = 1st step, we move the marbles at position 7 to position 9. Then, positions 2,6,8,9 are occupied.
// At the i = 2nd step, we move the marbles at position 2 to position 5. Then, positions 5,6,8,9 are occupied.
// At the end, the final positions containing at least one marbles are [5,6,8,9].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= moveFrom.length <= 105
// 	moveFrom.length == moveTo.length
// 	1 <= nums[i], moveFrom[i], moveTo[i] <= 109
// 	The test cases are generated such that there is at least a marble in moveFrom[i] at the moment we want to apply the ith move.
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
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
int* relocateMarbles(int* nums, int numsSize, int* moveFrom, int moveFromSize, int* moveTo, int moveToSize, int* returnSize) {
    // Use a hash table to track occupied positions
    #define TABLE_SIZE 200003  // A large prime number for better distribution
    typedef struct Node {
        long long key;
        struct Node* next;
    } Node;

    Node** table = (Node**)calloc(TABLE_SIZE, sizeof(Node*));

    // Hash function
    unsigned long hash(long long key) {
        return (unsigned long)(key % TABLE_SIZE);
    }

    // Insert key into hash table
    void insert(long long key) {
        unsigned long idx = hash(key);
        Node* curr = table[idx];
        while (curr) {
            if (curr->key == key) return;  // Key already exists
            curr = curr->next;
        }
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->next = table[idx];
        table[idx] = newNode;
    }

    // Remove key from hash table
    void removeKey(long long key) {
        unsigned long idx = hash(key);
        Node* curr = table[idx];
        Node* prev = NULL;
        while (curr) {
            if (curr->key == key) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    table[idx] = curr->next;
                }
                free(curr);
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // Initialize the hash table with initial positions
    for (int i = 0; i < numsSize; i++) {
        insert((long long)nums[i]);
    }

    // Process each move
    for (int i = 0; i < moveFromSize; i++) {
        long long from = (long long)moveFrom[i];
        long long to = (long long)moveTo[i];
        removeKey(from);
        insert(to);
    }

    // Collect occupied positions
    int* result = (int*)malloc(numsSize * sizeof(int));
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr) {
            result[count++] = (int)(curr->key);
            curr = curr->next;
        }
    }

    // Free the hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(table);
    // Sort the result using mergesort
    void merge(int* arr, int* temp, int left, int mid, int right) {
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) {
            temp[k++] = arr[i++];
        }
        while (j <= right) {
            temp[k++] = arr[j++];
        }
        for (i = left; i <= right; i++) {
            arr[i] = temp[i];
        }
    }
    void mergeSort(int* arr, int* temp, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, temp, left, mid);
            mergeSort(arr, temp, mid + 1, right);
            merge(arr, temp, left, mid, right);
        }
    }
    int* temp = (int*)malloc(count * sizeof(int));
    mergeSort(result, temp, 0, count - 1);
    free(temp);
    *returnSize = count;
    return result;
}
