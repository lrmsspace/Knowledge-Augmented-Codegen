// Source: https://leetcode.com/problems/maximize-the-minimum-game-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points of size n and an integer m. There is another array gameScore of size n, where gameScore[i] represents the score achieved at the ith game. Initially, gameScore[i] == 0 for all i.
//
// You start at index -1, which is outside the array (before the first position at index 0). You can make at most m moves. In each move, you can either:
//
//
// 	Increase the index by 1 and add points[i] to gameScore[i].
// 	Decrease the index by 1 and add points[i] to gameScore[i].
//
//
// Note that the index must always remain within the bounds of the array after the first move.
//
// Return the maximum possible minimum value in gameScore after at most m moves.
//
// Example:
// Input: points = [2,4], m = 3
//
// Output: 4
//
// Explanation:
//
// Initially, index i = -1 and gameScore = [0, 0].
//
//
// 	
// 		
// 			Move
// 			Index
// 			gameScore
// 		
// 	
// 	
// 		
// 			Increase i
// 			0
// 			[2, 0]
// 		
// 		
// 			Increase i
// 			1
// 			[2, 4]
// 		
// 		
// 			Decrease i
// 			0
// 			[4, 4]
// 		
// 	
//
//
// The minimum value in gameScore is 4, and this is the maximum possible minimum among all configurations. Hence, 4 is the output.
//
// Constraints:
// 2 <= n == points.length <= 5 * 104
// 	1 <= points[i] <= 106
// 	1 <= m <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: Use when optimizing a unimodal function (finding its maximum or minimum) over a continuous interval, where direct differentiation is hard or impossible.
//   • Idea: This algorithm finds the extremum (maximum or minimum) of a unimodal function over a given interval by repeatedly narrowing the search space. It evaluates the function at two internal points to achieve logarithmic convergence.
//   • Invariants: The extremum of the unimodal function f(x) is always within the current interval [l, r].; The function f(x) remains unimodal within the current interval [l, r].
//   • Tips: Use a fixed number of iterations as a stopping criterion instead of an epsilon value for robustness against floating point errors.; For golden section search, reuse one function evaluation from the previous step to minimize expensive computations.
//   • Pitfalls: Applying this algorithm to a non-unimodal function will yield an incorrect result.; Floating point precision issues can lead to incorrect comparisons or infinite loops if `eps` is too small.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} points
 * @param {number} m
 * @return {number}
 */
var maxScore = function(points, m) {
    const n = points.length;
    let low = 0;
    let high = Math.max(...points) * m; // Maximum possible score if we always pick the highest point

    function canAchieve(score) {
        let moves = 0;
        let currentIndex = -1;
        while (moves < m) {
            if (currentIndex + 1 < n && points[currentIndex + 1] >= score) {
                currentIndex++;
                moves++;
            }
            else if (currentIndex - 1 >= 0 && points[currentIndex - 1] >= score) {
                currentIndex--;
                moves++;
            }
            else {
                return false; // Cannot achieve the score with the remaining moves
            }
        }
        return true; // Achieved the score within m moves
    }
    
    while (low < high) {
        const mid = Math.floor((low + high + 1) / 2);
        if (canAchieve(mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    return low;

};