// Source: https://leetcode.com/problems/make-array-elements-equal-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// Start by selecting a starting position curr such that nums[curr] == 0, and choose a movement direction of either left or right.
//
// After that, you repeat the following process:
//
//
// 	If curr is out of the range [0, n - 1], this process ends.
// 	If nums[curr] == 0, move in the current direction by incrementing curr if you are moving right, or decrementing curr if you are moving left.
// 	Else if nums[curr] > 0:
// 	
// 		Decrement nums[curr] by 1.
// 		Reverse your movement direction (left becomes right and vice versa).
// 		Take a step in your new direction.
// 	
// 	
//
//
// A selection of the initial position curr and movement direction is considered valid if every element in nums becomes 0 by the end of the process.
//
// Return the number of possible valid selections.
//
// Example:
// Input: nums = [1,0,2,0,3]
//
// Output: 2
//
// Explanation:
//
// The only possible valid selections are the following:
//
//
// 	Choose curr = 3, and a movement direction to the left.
//
// 	
// 		[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,1,0,3] -> [1,0,1,0,3] -> [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,0,0,2] -> [1,0,0,0,2] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,1] -> [0,0,0,0,0].
// 	
// 	
// 	Choose curr = 3, and a movement direction to the right.
// 	
// 		[1,0,2,0,3] -> [1,0,2,0,3] -> [1,0,2,0,2] -> [1,0,2,0,2] -> [1,0,1,0,2] -> [1,0,1,0,2] -> [1,0,1,0,1] -> [1,0,1,0,1] -> [1,0,0,0,1] -> [1,0,0,0,1] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [1,0,0,0,0] -> [0,0,0,0,0].
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 100
// 	There is at least one element i where nums[i] == 0.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countValidSelections(int* nums, int numsSize) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            // Check both directions
            for (int dir = -1; dir <= 1; dir += 2) {
                int curr = i;
                int* temp = (int*)malloc(numsSize * sizeof(int));
                memcpy(temp, nums, numsSize * sizeof(int));
                while (curr >= 0 && curr < numsSize) {
                    if (temp[curr] == 0) {
                        curr += dir;
                    } else {
                        temp[curr]--;
                        dir = -dir; // Reverse direction
                        curr += dir;
                    }
                }
                // Check if all elements are zero
                int allZero = 1;
                for (int j = 0; j < numsSize; j++) {
                    if (temp[j] != 0) {
                        allZero = 0;
                        break;
                    }
                }
                if (allZero) {
                    count++;
                }
                free(temp);
            }
        }
    }
    return count;       
}
