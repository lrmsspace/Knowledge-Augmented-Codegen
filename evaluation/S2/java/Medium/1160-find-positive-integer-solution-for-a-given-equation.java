// Source: https://leetcode.com/problems/find-positive-integer-solution-for-a-given-equation/   |   Difficulty: Medium
//
// Problem Description:
// Given a callable function f(x, y) with a hidden formula and a value z, reverse engineer the formula and return all positive integer pairs x and y where f(x,y) == z. You may return the pairs in any order.
//
// While the exact formula is hidden, the function is monotonically increasing, i.e.:
//
//
// 	f(x, y) < f(x + 1, y)
// 	f(x, y) < f(x, y + 1)
//
//
// The function interface is defined like this:
//
//
// interface CustomFunction {
// public:
//   // Returns some positive integer f(x, y) for two positive integers x and y based on a formula.
//   int f(int x, int y);
// };
//
//
// We will judge your solution as follows:
//
//
// 	The judge has a list of 9 hidden implementations of CustomFunction, along with a way to generate an answer key of all valid pairs for a specific z.
// 	The judge will receive two inputs: a function_id (to determine which implementation to test your code with), and the target z.
// 	The judge will call your findSolution and compare your results with the answer key.
// 	If your results match the answer key, your solution will be Accepted.
//
// Example:
// Input: function_id = 1, z = 5
// Output: [[1,4],[2,3],[3,2],[4,1]]
// Explanation: The hidden formula for function_id = 1 is f(x, y) = x + y.
// The following positive integer values of x and y make f(x, y) equal to 5:
// x=1, y=4 -> f(1, 4) = 1 + 4 = 5.
// x=2, y=3 -> f(2, 3) = 2 + 3 = 5.
// x=3, y=2 -> f(3, 2) = 3 + 2 = 5.
// x=4, y=1 -> f(4, 1) = 4 + 1 = 5.
//
// Constraints:
// 1 <= function_id <= 9
// 	1 <= z <= 100
// 	It is guaranteed that the solutions of f(x, y) == z will be in the range 1 <= x, y <= 1000.
// 	It is also guaranteed that f(x, y) will fit in 32 bit signed integer if 1 <= x, y <= 1000.
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

/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     public int f(int x, int y);
 * };
 */

class Solution {
    public List<List<Integer>> findSolution(CustomFunction customfunction, int z) {
        List<List<Integer>> result = new ArrayList<>();
        for (int x = 1; x <= 1000; x++) {
            for (int y = 1; y <= 1000; y++) {
                if (customfunction.f(x, y) == z) {
                    result.add(Arrays.asList(x, y));
                }
            }
        }
        return result;          
    }
}
