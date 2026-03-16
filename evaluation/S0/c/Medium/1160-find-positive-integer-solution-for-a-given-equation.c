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

/*
 * // This is the definition for customFunction API.
 * // You should not implement it, or speculate about its implementation
 *
 * // Returns f(x, y) for any given positive integers x and y.
 * // Note that f(x, y) is increasing with respect to both x and y.
 * // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findSolution(int (*customFunction)(int, int), int z, int* returnSize, int** returnColumnSizes) {
    int capacity = 16;
    int** result = malloc(capacity * sizeof(int*));
    *returnColumnSizes = malloc(capacity * sizeof(int));
    *returnSize = 0;

    for (int x = 1; x <= 1000; x++) {
        for (int y = 1; y <= 1000; y++) {
            int val = customFunction(x, y);
            if (val == z) {
                if (*returnSize >= capacity) {
                    capacity *= 2;
                    result = realloc(result, capacity * sizeof(int*));
                    *returnColumnSizes = realloc(*returnColumnSizes, capacity * sizeof(int));
                }
                result[*returnSize] = malloc(2 * sizeof(int));
                result[*returnSize][0] = x;
                result[*returnSize][1] = y;
                (*returnColumnSizes)[*returnSize] = 2;
                (*returnSize)++;
            } else if (val > z) {
                break; // No need to check further y values for this x
            }
        }
    }

    return result;  	
}
