// Source: https://leetcode.com/problems/maximum-genetic-difference-query/   |   Difficulty: Hard
//
// Problem Description:
// There is a rooted tree consisting of n nodes numbered 0 to n - 1. Each node's number denotes its unique genetic value (i.e. the genetic value of node x is x). The genetic difference between two genetic values is defined as the bitwise-XOR of their values. You are given the integer array parents, where parents[i] is the parent for node i. If node x is the root of the tree, then parents[x] == -1.
//
// You are also given the array queries where queries[i] = [nodei, vali]. For each query i, find the maximum genetic difference between vali and pi, where pi is the genetic value of any node that is on the path between nodei and the root (including nodei and the root). More formally, you want to maximize vali XOR pi.
//
// Return an array ans where ans[i] is the answer to the ith query.
//
// Example:
// Input: parents = [-1,0,1,1], queries = [[0,2],[3,2],[2,5]]
// Output: [2,3,7]
// Explanation: The queries are processed as follows:
// - [0,2]: The node with the maximum genetic difference is 0, with a difference of 2 XOR 0 = 2.
// - [3,2]: The node with the maximum genetic difference is 1, with a difference of 2 XOR 1 = 3.
// - [2,5]: The node with the maximum genetic difference is 2, with a difference of 5 XOR 2 = 7.
//
// Constraints:
// 2 <= parents.length <= 105
// 	0 <= parents[i] <= parents.length - 1 for every node i that is not the root.
// 	parents[root] == -1
// 	1 <= queries.length <= 3 * 104
// 	0 <= nodei <= parents.length - 1
// 	0 <= vali <= 2 * 105
//
// Helpful references (internal KB):
// - Depth First Search (tree, graph, dfs)
//   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
//   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
//   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
//   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Lowest Common Ancestor (tree, segment-tree)
//   • When to use: Use this approach to efficiently answer multiple Lowest Common Ancestor queries on a static tree. It is suitable when precomputation time is acceptable for faster subsequent queries.
//   • Idea: This method transforms the LCA problem into a Range Minimum Query (RMQ) problem by constructing an Euler tour of the tree. It achieves O(N log N) precomputation and O(log N) query time by building a segment tree over the depths of nodes in the Euler tour.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry and exit order.; The depth array stores the depth of each node as it appears in the Euler tour.
//   • Tips: Perform a DFS to generate an Euler tour of the tree, recording nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array, leading to wrong ranges for RMQ.; Off-by-one errors when mapping node indices to Euler tour indices or defining segment tree query ranges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} parents
 * @param {number[][]} queries
 * @return {number[]}
 */
var maxGeneticDifference = function(parents, queries) {
	var n = parents.length;
	var children = new Array(n);
	for (var i = 0; i < n; i++) {
		children[i] = [];
	}

	var root = -1;
	for (var i = 0; i < n; i++) {
		var p = parents[i];
		if (p === -1) {
			root = i;
		} else {
			children[p].push(i);
		}
	}

	var queriesByNode = new Array(n);
	for (var i = 0; i < n; i++) {
		queriesByNode[i] = [];
	}
	for (var i = 0; i < queries.length; i++) {
		var node = queries[i][0];
		var val = queries[i][1];
		queriesByNode[node].push([val, i]);
	}

	var ans = new Array(queries.length);

	var MAX_BIT = 17;
	var child0 = [];
	var child1 = [];
	var count = [];

	function createNode() {
		var idx = child0.length;
		child0.push(-1);
		child1.push(-1);
		count.push(0);
		return idx;
	}

	createNode();

	function trieInsert(value, delta) {
		var node = 0;
		count[node] += delta;
		for (var bit = MAX_BIT; bit >= 0; bit--) {
			var b = (value >> bit) & 1;
			var next = b === 0 ? child0[node] : child1[node];
			if (next === -1) {
				if (delta < 0) {
					return;
				}
				next = createNode();
				if (b === 0) {
					child0[node] = next;
				} else {
					child1[node] = next;
				}
			}
			node = next;
			count[node] += delta;
		}
	}

	function trieQuery(value) {
		var node = 0;
		var res = 0;
		for (var bit = MAX_BIT; bit >= 0; bit--) {
			var b = (value >> bit) & 1;
			var preferred = b ^ 1;
			var next = preferred === 0 ? child0[node] : child1[node];
			if (next !== -1 && count[next] > 0) {
				res |= (1 << bit);
				node = next;
			} else {
				next = b === 0 ? child0[node] : child1[node];
				if (next === -1 || count[next] === 0) {
					break;
				}
				node = next;
			}
		}
		return res;
	}

	var stack = [];
	stack.push([root, 0]);

	while (stack.length > 0) {
		var item = stack.pop();
		var node = item[0];
		var state = item[1];

		if (state === 0) {
			trieInsert(node, 1);

			var list = queriesByNode[node];
			for (var i = 0; i < list.length; i++) {
				var qVal = list[i][0];
				var qIdx = list[i][1];
				ans[qIdx] = trieQuery(qVal);
			}

			stack.push([node, 1]);
			var kids = children[node];
			for (var i = kids.length - 1; i >= 0; i--) {
				stack.push([kids[i], 0]);
			}
		} else {
			trieInsert(node, -1);
		}
	}

	return ans;
};
