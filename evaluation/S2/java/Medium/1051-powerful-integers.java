// Source: https://leetcode.com/problems/powerful-integers/   |   Difficulty: Medium
//
// Problem Description:
// Given three integers x, y, and bound, return a list of all the powerful integers that have a value less than or equal to bound.
//
// An integer is powerful if it can be represented as xi + yj for some integers i >= 0 and j >= 0.
//
// You may return the answer in any order. In your answer, each value should occur at most once.
//
// Example:
// Input: x = 2, y = 3, bound = 10
// Output: [2,3,4,5,7,9,10]
// Explanation:
// 2 = 20 + 30
// 3 = 21 + 30
// 4 = 20 + 31
// 5 = 21 + 31
// 7 = 22 + 31
// 9 = 23 + 30
// 10 = 20 + 32
//
// Constraints:
// 1 <= x, y <= 100
// 	0 <= bound <= 106
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
    public List<Integer> powerfulIntegers(int x, int y, int bound) {
        Set<Integer> powerfulInts = new HashSet<>();
        
        for (int i = 0; Math.pow(x, i) < bound; i++) {
            for (int j = 0; Math.pow(y, j) < bound; j++) {
                int sum = (int)(Math.pow(x, i) + Math.pow(y, j));
                if (sum <= bound) {
                    powerfulInts.add(sum);
                } else {
                    break; // No need to continue if the sum exceeds the bound
                }
            }
        }
        
        return new ArrayList<>(powerfulInts);           
    }
}
