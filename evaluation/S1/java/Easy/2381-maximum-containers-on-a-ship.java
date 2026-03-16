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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxContainers(int n, int w, int maxWeight) {
        int totalCells = n * n;
        int maxContainersByWeight = maxWeight / w;
        return Math.min(totalCells, maxContainersByWeight);         
    }
}
