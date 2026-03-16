// Source: https://leetcode.com/problems/reveal-cards-in-increasing-order/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array deck. There is a deck of cards where every card has a unique integer. The integer on the ith card is deck[i].
//
// You can order the deck in any order you want. Initially, all the cards start face down (unrevealed) in one deck.
//
// You will do the following steps repeatedly until all cards are revealed:
//
//
// 	Take the top card of the deck, reveal it, and take it out of the deck.
// 	If there are still cards in the deck then put the next top card of the deck at the bottom of the deck.
// 	If there are still unrevealed cards, go back to step 1. Otherwise, stop.
//
//
// Return an ordering of the deck that would reveal the cards in increasing order.
//
// Note that the first entry in the answer is considered to be the top of the deck.
//
// Example:
// Input: deck = [17,13,11,2,3,5,7]
// Output: [2,13,3,11,5,17,7]
// Explanation: 
// We get the deck in the order [17,13,11,2,3,5,7] (this order does not matter), and reorder it.
// After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
// We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
// We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
// We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
// We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
// We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
// We reveal 13, and move 17 to the bottom.  The deck is now [17].
// We reveal 17.
// Since all the cards revealed are in increasing order, the answer is correct.
//
// Constraints:
// 1 <= deck.length <= 1000
// 	1 <= deck[i] <= 106
// 	All the values of deck are unique.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - bucket-sort (array, linked-list, bucket-sort)
//   • When to use: Use when sorting elements, especially floating-point numbers, that are uniformly distributed over a range. It offers linear time complexity on average for such distributions.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually using another sorting algorithm, and then concatenates the sorted buckets. It achieves an average time complexity of O(N+K), where N is the number of elements and K is the number of buckets.
//   • Invariants: Before sorting any bucket, all elements are correctly placed in their respective buckets based on their range.; After sorting each individual bucket, all elements within that bucket are in sorted order.
//   • Tips: Use a stable sorting algorithm like Insertion Sort for individual buckets to maintain overall stability.; The number of buckets should be chosen carefully, often proportional to N, to optimize performance.
//   • Pitfalls: Performance degrades significantly with non-uniform data distributions, potentially becoming O(N^2).; Requires extra space for the buckets, which can be substantial for many buckets or large elements.
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
int* deckRevealedIncreasing(int* deck, int deckSize, int* returnSize) {
    // Step 1: Sort the deck
    qsort(deck, deckSize, sizeof(int), cmp);

    // Step 2: Create an array to hold the result
    int* result = (int*)malloc(deckSize * sizeof(int));
    if (!result) return NULL; // Handle malloc failure

    // Step 3: Use a queue to simulate the revealing process
    int* queue = (int*)malloc(deckSize * sizeof(int));
    if (!queue) {
        free(result);
        return NULL; // Handle malloc failure
    }
    int front = 0, rear = 0;

    // Initialize the queue with indices
    for (int i = 0; i < deckSize; i++) {
        queue[rear++] = i;
    }

    // Step 4: Fill the result array according to the revealing process
    for (int i = 0; i < deckSize; i++) {
        int index = queue[front++]; // Get the front index
        result[index] = deck[i]; // Place the card in the correct position

        if (front < rear) { // If there are still indices in the queue
            queue[rear++] = queue[front++]; // Move the next index to the back of the queue
        }
    }

    free(queue); // Clean up the queue memory
    *returnSize = deckSize; // Set the return size
    return result; // Return the resulting array        
}
