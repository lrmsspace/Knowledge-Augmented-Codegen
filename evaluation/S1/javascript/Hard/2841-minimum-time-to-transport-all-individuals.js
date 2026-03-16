// Source: https://leetcode.com/problems/minimum-time-to-transport-all-individuals/   |   Difficulty: Hard
//
// Problem Description:
// You are given n individuals at a base camp who need to cross a river to reach a destination using a single boat. The boat can carry at most k people at a time. The trip is affected by environmental conditions that vary cyclically over m stages.
//
// Each stage j has a speed multiplier mul[j]:
//
//
// 	If mul[j] > 1, the trip slows down.
// 	If mul[j] < 1, the trip speeds up.
//
//
// Each individual i has a rowing strength represented by time[i], the time (in minutes) it takes them to cross alone in neutral conditions.
//
// Rules:
//
//
// 	A group g departing at stage j takes time equal to the maximum time[i] among its members, multiplied by mul[j] minutes to reach the destination.
// 	After the group crosses the river in time d, the stage advances by floor(d) % m steps.
// 	If individuals are left behind, one person must return with the boat. Let r be the index of the returning person, the return takes time[r] × mul[current_stage], defined as return_time, and the stage advances by floor(return_time) % m.
//
//
// Return the minimum total time required to transport all individuals. If it is not possible to transport all individuals to the destination, return -1.
//
// Example:
// Input: n = 1, k = 1, m = 2, time = [5], mul = [1.0,1.3]
//
// Output: 5.00000
//
// Explanation:
//
//
// 	Individual 0 departs from stage 0, so crossing time = 5 × 1.00 = 5.00 minutes.
// 	All team members are now at the destination. Thus, the total time taken is 5.00 minutes.
//
// Constraints:
// 1 <= n == time.length <= 12
// 	1 <= k <= 5
// 	1 <= m <= 5
// 	1 <= time[i] <= 100
// 	m == mul.length
// 	0.5 <= mul[i] <= 2.0
//
// Helpful references (internal KB):
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, greedy, dijkstra, bellman-ford)
//   • When to use: This algorithm finds a minimum-cost flow of a given amount from a source to a sink in a flow network. It is suitable when both flow capacity and edge costs are present.
//   • Idea: The successive shortest path algorithm iteratively finds augmenting paths with minimum cost in a residual graph, using shortest path algorithms like Bellman-Ford or Dijkstra with potentials, until the desired flow is achieved. Its complexity depends on the shortest path algorithm used and the number of augmentations.
//   • Invariants: The total flow pushed from source to sink never exceeds the sum of capacities of edges leaving the source.; For any edge (u, v) with flow f_uv, 0 <= f_uv <= capacity_uv.
//   • Tips: Use potentials with Dijkstra for non-negative edge costs in the residual graph.; Bellman-Ford is necessary if initial edge costs can be negative or if potentials are not used.
//   • Pitfalls: Incorrectly updating potentials can lead to wrong shortest paths.; Forgetting to add reverse edges with negative costs in the residual graph.
// - Dijkstra on sparse graphs (heap, queue, dijkstra)
//   • When to use: When you need to find the shortest paths from a single source vertex to all other vertices in a graph with non-negative edge weights, especially efficient for sparse graphs.
//   • Idea: Dijkstra's algorithm finds the shortest paths from a single source to all other vertices in a weighted graph with non-negative edge weights. It uses a priority queue to greedily explore vertices, achieving O(E log V) complexity with a binary heap.
//   • Invariants: At the start of each iteration, dist[u] holds the shortest distance found so far from the source to u.; All vertices already extracted from the priority queue have their final shortest distance determined.
//   • Tips: Use a priority queue (min-heap) to efficiently retrieve the unvisited vertex with the smallest distance.; Initialize all distances to infinity and the source distance to zero.
//   • Pitfalls: Does not work correctly with negative edge weights; Bellman-Ford or SPFA is needed.; Forgetting to mark vertices as visited or handle duplicate entries in the priority queue can lead to incorrectness or TLE.
// - Finding bridges in a graph in O(N+M) (graph, dfs)
//   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
//   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
//   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
//   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
//   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number} k
 * @param {number} m
 * @param {number[]} time
 * @param {number[]} mul
 * @return {number}
 */
var minTime = function(n, k, m, time, mul) {
	const fullMask = (1 << n) - 1;
	const totalStates = (1 << n) * m * 2;
	const dist = new Array(totalStates).fill(Infinity);

	const popcount = new Array(1 << n).fill(0);
	for (let mask = 1; mask <= fullMask; mask++) {
		popcount[mask] = popcount[mask >> 1] + (mask & 1);
	}

	const maxTime = new Array(1 << n).fill(0);
	for (let mask = 1; mask <= fullMask; mask++) {
		const lb = mask & -mask;
		const idx = Math.log2(lb) | 0;
		const prev = mask ^ lb;
		const candidate = time[idx];
		maxTime[mask] = maxTime[prev] > candidate ? maxTime[prev] : candidate;
	}

	const encode = (mask, stage, side) => ((mask * m + stage) * 2 + side);

	class MinHeap {
		constructor() {
			this.data = [];
		}
		push(item) {
			this.data.push(item);
			this._siftUp(this.data.length - 1);
		}
		pop() {
			if (this.data.length === 0) return null;
			const top = this.data[0];
			const last = this.data.pop();
			if (this.data.length > 0) {
				this.data[0] = last;
				this._siftDown(0);
			}
			return top;
		}
		_siftUp(i) {
			while (i > 0) {
				const p = (i - 1) >> 1;
				if (this.data[p][0] <= this.data[i][0]) break;
				[this.data[p], this.data[i]] = [this.data[i], this.data[p]];
				i = p;
			}
		}
		_siftDown(i) {
			const n = this.data.length;
			while (true) {
				let smallest = i;
				const l = i * 2 + 1;
				const r = l + 1;
				if (l < n && this.data[l][0] < this.data[smallest][0]) smallest = l;
				if (r < n && this.data[r][0] < this.data[smallest][0]) smallest = r;
				if (smallest === i) break;
				[this.data[smallest], this.data[i]] = [this.data[i], this.data[smallest]];
				i = smallest;
			}
		}
		get size() {
			return this.data.length;
		}
	}

	const startIdx = encode(0, 0, 0);
	dist[startIdx] = 0;
	const heap = new MinHeap();
	heap.push([0, startIdx]);

	// Dijkstra over (mask, stage, side) states.
	while (heap.size > 0) {
		const [curDist, idx] = heap.pop();
		if (curDist !== dist[idx]) continue;

		const side = idx % 2;
		const tmp = (idx - side) / 2;
		const stage = tmp % m;
		const mask = (tmp - stage) / m;

		if (mask === fullMask && side === 1) return curDist;

		if (side === 0) {
			const baseMask = fullMask ^ mask;
			for (let sub = baseMask; sub > 0; sub = (sub - 1) & baseMask) {
				if (popcount[sub] > k) continue;
				const trip = maxTime[sub] * mul[stage];
				const stage2 = (stage + (Math.floor(trip) % m)) % m;
				const mask2 = mask | sub;
				const idx2 = encode(mask2, stage2, 1);
				const nd = curDist + trip;
				if (nd < dist[idx2]) {
					dist[idx2] = nd;
					heap.push([nd, idx2]);
				}
			}
		} else {
			if (mask === fullMask) continue;
			for (let sub = mask; sub > 0; sub &= sub - 1) {
				const lb = sub & -sub;
				const i = Math.log2(lb) | 0;
				const trip = time[i] * mul[stage];
				const stage2 = (stage + (Math.floor(trip) % m)) % m;
				const mask2 = mask ^ lb;
				const idx2 = encode(mask2, stage2, 0);
				const nd = curDist + trip;
				if (nd < dist[idx2]) {
					dist[idx2] = nd;
					heap.push([nd, idx2]);
				}
			}
		}
	}

	return -1;
};
