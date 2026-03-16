// Source: https://leetcode.com/problems/rank-transform-of-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of matrix[row][col].
//
// The rank is an integer that represents how large an element is compared to other elements. It is calculated using the following rules:
//
//
// 	The rank is an integer starting from 1.
// 	If two elements p and q are in the same row or column, then:
// 	
// 		If p < q then rank(p) < rank(q)
// 		If p == q then rank(p) == rank(q)
// 		If p > q then rank(p) > rank(q)
// 	
// 	
// 	The rank should be as small as possible.
//
//
// The test cases are generated so that answer is unique under the given rules.
//
// Example:
// Input: matrix = [[1,2],[3,4]]
// Output: [[1,2],[2,3]]
// Explanation:
// The rank of matrix[0][0] is 1 because it is the smallest integer in its row and column.
// The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0] and matrix[0][0] is rank 1.
// The rank of matrix[1][0] is 2 because matrix[1][0] > matrix[0][0] and matrix[0][0] is rank 1.
// The rank of matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] > matrix[1][0], and both matrix[0][1] and matrix[1][0] are rank 2.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 500
// 	-109 <= matrix[row][col] <= 109
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Finding Bridges Online (graph, tree, union-find, counting)
//   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
//   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
//   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
//   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
//   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} matrix
 * @return {number[][]}
 */
var matrixRankTransform = function(matrix) {
	var m = matrix.length;
	var n = matrix[0].length;

	var valueMap = new Map();
	for (var r = 0; r < m; r++) {
		for (var c = 0; c < n; c++) {
			var v = matrix[r][c];
			if (!valueMap.has(v)) {
				valueMap.set(v, []);
			}
			valueMap.get(v).push([r, c]);
		}
	}

	var values = Array.from(valueMap.keys()).sort(function(a, b) { return a - b; });
	var rowRank = new Array(m).fill(0);
	var colRank = new Array(n).fill(0);
	var answer = Array.from({ length: m }, function() { return new Array(n).fill(0); });

	function makeDsu(size) {
		var parent = new Array(size);
		var rank = new Array(size).fill(0);
		for (var i = 0; i < size; i++) {
			parent[i] = i;
		}
		function find(x) {
			while (parent[x] !== x) {
				parent[x] = parent[parent[x]];
				x = parent[x];
			}
			return x;
		}
		function union(a, b) {
			var ra = find(a);
			var rb = find(b);
			if (ra === rb) {
				return;
			}
			if (rank[ra] < rank[rb]) {
				parent[ra] = rb;
			} else if (rank[ra] > rank[rb]) {
				parent[rb] = ra;
			} else {
				parent[rb] = ra;
				rank[ra] += 1;
			}
		}
		return { find: find, union: union };
	}

	for (var i = 0; i < values.length; i++) {
		var positions = valueMap.get(values[i]);
		var idMap = new Map();
		var nextId = 0;

		function getRowId(r) {
			var key = "r" + r;
			if (!idMap.has(key)) {
				idMap.set(key, nextId++);
			}
			return idMap.get(key);
		}
		function getColId(c) {
			var key = "c" + c;
			if (!idMap.has(key)) {
				idMap.set(key, nextId++);
			}
			return idMap.get(key);
		}

		for (var p = 0; p < positions.length; p++) {
			var pos = positions[p];
			getRowId(pos[0]);
			getColId(pos[1]);
		}

		var dsu = makeDsu(nextId);
		for (var j = 0; j < positions.length; j++) {
			var cell = positions[j];
			var rowId = getRowId(cell[0]);
			var colId = getColId(cell[1]);
			dsu.union(rowId, colId);
		}

		var componentMax = new Map();
		idMap.forEach(function(id, key) {
			var root = dsu.find(id);
			var baseRank = 0;
			if (key[0] === "r") {
				baseRank = rowRank[parseInt(key.slice(1), 10)];
			} else {
				baseRank = colRank[parseInt(key.slice(1), 10)];
			}
			var prev = componentMax.has(root) ? componentMax.get(root) : 0;
			if (baseRank > prev) {
				componentMax.set(root, baseRank);
			}
		});

		var componentRank = new Map();
		componentMax.forEach(function(maxRank, root) {
			componentRank.set(root, maxRank + 1);
		});

		for (var k = 0; k < positions.length; k++) {
			var cell2 = positions[k];
			var r2 = cell2[0];
			var c2 = cell2[1];
			var root2 = dsu.find(getRowId(r2));
			var rankValue = componentRank.get(root2);
			answer[r2][c2] = rankValue;
			if (rankValue > rowRank[r2]) {
				rowRank[r2] = rankValue;
			}
			if (rankValue > colRank[c2]) {
				colRank[c2] = rankValue;
			}
		}
	}

	return answer;
};
