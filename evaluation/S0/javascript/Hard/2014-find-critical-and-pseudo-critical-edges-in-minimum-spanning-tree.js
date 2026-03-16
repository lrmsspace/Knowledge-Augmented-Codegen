// Source: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.
//
// Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
//
// Note that you can return the indices of the edges in any order.
//
// Example:
// Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
// Output: [[0,1],[2,3,4,5]]
// Explanation: The figure above describes the graph.
// The following figure shows all the possible MSTs:
//
// Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
// The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
//
// Constraints:
// 2 <= n <= 100
// 	1 <= edges.length <= min(200, n * (n - 1) / 2)
// 	edges[i].length == 3
// 	0 <= ai < bi < n
// 	1 <= weighti <= 1000
// 	All pairs (ai, bi) are distinct.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number[][]}
 */
var findCriticalAndPseudoCriticalEdges = function(n, edges) {
	const indexedEdges = edges.map((edge, index) => ({
		u: edge[0],
		v: edge[1],
		w: edge[2],
		idx: index
	}));

	indexedEdges.sort((a, b) => a.w - b.w || a.idx - b.idx);

	class DSU {
		constructor(size) {
			this.parent = Array.from({ length: size }, (_, i) => i);
			this.rank = Array(size).fill(0);
			this.count = size;
		}
		find(x) {
			if (this.parent[x] !== x) {
				this.parent[x] = this.find(this.parent[x]);
			}
			return this.parent[x];
		}
		union(a, b) {
			const rootA = this.find(a);
			const rootB = this.find(b);
			if (rootA === rootB) {
				return false;
			}
			if (this.rank[rootA] < this.rank[rootB]) {
				this.parent[rootA] = rootB;
			} else if (this.rank[rootA] > this.rank[rootB]) {
				this.parent[rootB] = rootA;
			} else {
				this.parent[rootB] = rootA;
				this.rank[rootA] += 1;
			}
			this.count -= 1;
			return true;
		}
	}

	const kruskal = (skipIndex, forceIndex) => {
		const dsu = new DSU(n);
		let weight = 0;

		if (forceIndex !== null) {
			const edge = indexedEdges[forceIndex];
			if (dsu.union(edge.u, edge.v)) {
				weight += edge.w;
			}
		}

		for (let i = 0; i < indexedEdges.length; i += 1) {
			if (i === skipIndex) {
				continue;
			}
			const edge = indexedEdges[i];
			if (dsu.union(edge.u, edge.v)) {
				weight += edge.w;
			}
		}

		return dsu.count === 1 ? weight : Number.POSITIVE_INFINITY;
	};

	const baseWeight = kruskal(null, null);
	const critical = [];
	const pseudoCritical = [];

	for (let i = 0; i < indexedEdges.length; i += 1) {
		const withoutEdge = kruskal(i, null);
		if (withoutEdge > baseWeight) {
			critical.push(indexedEdges[i].idx);
			continue;
		}
		const withEdge = kruskal(null, i);
		if (withEdge === baseWeight) {
			pseudoCritical.push(indexedEdges[i].idx);
		}
	}

	return [critical, pseudoCritical];
};
