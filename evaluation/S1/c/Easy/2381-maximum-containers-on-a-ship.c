// Source: https://leetcode.com/problems/maximum-containers-on-a-ship/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer n representing an n x n cargo deck on a ship. Each cell on the deck can hold one container with a weight of exactly w.
//
// However, the total weight of all containers, if loaded onto the deck, must not exceed the ship's maximum weight capacity, maxWeight.
//
// Return the maximum number of containers that can be loaded onto the ship.
//
// Example:
// Input: n = 2, w = 3, maxWeight = 15
//
// Output: 4
//
// Explanation: 
//
// The deck has 4 cells, and each container weighs 3. The total weight of loading all containers is 12, which does not exceed maxWeight.
//
// Constraints:
// 1 <= n <= 1000
// 	1 <= w <= 1000
// 	1 <= maxWeight <= 109
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxContainers(int n, int w, int maxWeight) {
    long long totalCells = (long long)n * n;
    long long totalWeight = (long long)w * totalCells;

    if (totalWeight <= maxWeight) {
        return (int)totalCells;
    } else {
        return (int)(maxWeight / w);
    }       
}
