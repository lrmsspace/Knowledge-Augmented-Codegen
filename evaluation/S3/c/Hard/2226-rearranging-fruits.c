// Source: https://leetcode.com/problems/rearranging-fruits/   |   Difficulty: Hard
//
// Problem Description:
// You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following operation as many times as you want:
//
//
// 	Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
// 	The cost of the swap is min(basket1[i], basket2[j]).
//
//
// Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.
//
// Return the minimum cost to make both the baskets equal or -1 if impossible.
//
// Example:
// Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
// Output: 1
// Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.
//
// Constraints:
// basket1.length == basket2.length
// 	1 <= basket1.length <= 105
// 	1 <= basket1[i], basket2[i] <= 109
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minCost(int* basket1, int basket1Size, int* basket2, int basket2Size) {
    // Step 1: Calculate the frequency of each fruit cost in both baskets
    // and determine the total cost of all fruits.
    long long totalCost = 0;
    int maxCost = 0;
    for (int i = 0; i < basket1Size; i++) {
        totalCost += basket1[i];
        if (basket1[i] > maxCost) {
            maxCost = basket1[i];
        }
    }
    for (int i = 0; i < basket2Size; i++) {
        totalCost += basket2[i];
        if (basket2[i] > maxCost) {
            maxCost = basket2[i];
        }
    }

    // Step 2: Create frequency arrays for both baskets
    int* freq1 = (int*)calloc(maxCost + 1, sizeof(int));
    int* freq2 = (int*)calloc(maxCost + 1, sizeof(int));
    
    for (int i = 0; i < basket1Size; i++) {
        freq1[basket1[i]]++;
    }
    for (int i = 0; i < basket2Size; i++) {
        freq2[basket2[i]]++;
    }

    // Step 3: Check if it's possible to make the baskets equal
    long long swapCost = 0;
    int minFruitCost = maxCost + 1;
    
    for (int cost = 0; cost <= maxCost; cost++) {
        int diff = freq1[cost] - freq2[cost];
        
        if (diff % 2 != 0) {
            free(freq1);
            free(freq2);
            return -1; // Impossible to make baskets equal
        }
        
        if (diff > 0) {
            swapCost += (long long)diff / 2 * cost;
            if (cost < minFruitCost) {
                minFruitCost = cost;
            }
        }
    }

    // Step 4: Calculate the minimum cost to swap
    long long minSwapCost = swapCost;
    
    for (int cost = 0; cost <= maxCost; cost++) {
        int diff = freq1[cost] - freq2[cost];
        
        if (diff > 0) {
            minSwapCost += ((long long)diff / 2) * minFruitCost;
        }
    }       
}
