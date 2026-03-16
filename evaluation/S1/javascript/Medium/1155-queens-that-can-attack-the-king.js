// Source: https://leetcode.com/problems/queens-that-can-attack-the-king/   |   Difficulty: Medium
//
// Problem Description:
// On a 0-indexed 8 x 8 chessboard, there can be multiple black queens and one white king.
//
// You are given a 2D integer array queens where queens[i] = [xQueeni, yQueeni] represents the position of the ith black queen on the chessboard. You are also given an integer array king of length 2 where king = [xKing, yKing] represents the position of the white king.
//
// Return the coordinates of the black queens that can directly attack the king. You may return the answer in any order.
//
// Example:
// Input: queens = [[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]], king = [0,0]
// Output: [[0,1],[1,0],[3,3]]
// Explanation: The diagram above shows the three queens that can directly attack the king and the three queens that cannot attack the king (i.e., marked with red dashes).
//
// Constraints:
// 1 <= queens.length < 64
// 	queens[i].length == king.length == 2
// 	0 <= xQueeni, yQueeni, xKing, yKing < 8
// 	All the given positions are unique.
//
// Helpful references (internal KB):
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} queens
 * @param {number[]} king
 * @return {number[][]}
 */
var queensAttacktheKing = function(queens, king) {
	const directions = [
		[-1, 0], [-1, 1], [0, 1], [1, 1],
		[1, 0], [1, -1], [0, -1], [-1, -1]
	];
	const queenSet = new Set(queens.map(q => q.join(',')));
	const attackingQueens = [];

	for (const [dx, dy] of directions) {
		let x = king[0] + dx;
		let y = king[1] + dy;

		while (x >= 0 && x < 8 && y >= 0 && y < 8) {
			if (queenSet.has(`${x},${y}`)) {
				attackingQueens.push([x, y]);
				break;
			}
			x += dx;
			y += dy;
		}
	}

	return attackingQueens;
};
