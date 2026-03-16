// Source: https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected graph of n nodes. You are given a 2D array edges, where edges[i] = [ui, vi, lengthi] describes an edge between node ui and node vi with a traversal time of lengthi units.
//
// Additionally, you are given an array disappear, where disappear[i] denotes the time when the node i disappears from the graph and you won't be able to visit it.
//
// Note that the graph might be disconnected and might contain multiple edges.
//
// Return the array answer, with answer[i] denoting the minimum units of time required to reach node i from node 0. If node i is unreachable from node 0 then answer[i] is -1.
//
// Example:
// Input: n = 3, edges = [[0,1,2],[1,2,1],[0,2,4]], disappear = [1,1,5]
//
// Output: [0,-1,4]
//
// Explanation:
//
//
//
// We are starting our journey from node 0, and our goal is to find the minimum time required to reach each node before it disappears.
//
//
// 	For node 0, we don't need any time as it is our starting point.
// 	For node 1, we need at least 2 units of time to traverse edges[0]. Unfortunately, it disappears at that moment, so we won't be able to visit it.
// 	For node 2, we need at least 4 units of time to traverse edges[2].
//
// Constraints:
// 1 <= n <= 5 * 104
// 	0 <= edges.length <= 105
// 	edges[i] == [ui, vi, lengthi]
// 	0 <= ui, vi <= n - 1
// 	1 <= lengthi <= 105
// 	disappear.length == n
// 	1 <= disappear[i] <= 105
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} disappear
 * @return {number[]}
 */
var minimumTime = function(n, edges, disappear) {
    // Build adjacency list
    const adj = Array.from({ length: n }, () => []);
    for (const [u, v, w] of edges) {
        adj[u].push([v, w]);
        adj[v].push([u, w]);
    }

    const INF = Number.MAX_SAFE_INTEGER;
    const dist = Array(n).fill(INF);

    // Min-heap priority queue: [time, node]
    class MinHeap {
        constructor() { this.data = []; }
        size() { return this.data.length; }
        push(item) {
            const a = this.data;
            a.push(item);
            this._siftUp(a.length - 1);
        }
        pop() {
            const a = this.data;
            if (a.length === 0) return null;
            const res = a[0];
            const last = a.pop();
            if (a.length > 0) {
                a[0] = last;
                this._siftDown(0);
            }
            return res;
        }
        _siftUp(i) {
            const a = this.data;
            while (i > 0) {
                const p = (i - 1) >> 1;
                if (a[p][0] <= a[i][0]) break;
                [a[p], a[i]] = [a[i], a[p]];
                i = p;
            }
        }
        _siftDown(i) {
            const a = this.data;
            const n = a.length;
            while (true) {
                let smallest = i;
                const left = (i << 1) + 1;
                const right = (i << 1) + 2; 
                if (left < n && a[left][0] < a[smallest][0]) smallest = left;
                if (right < n && a[right][0] < a[smallest][0]) smallest = right;
                if (smallest === i) break;
                [a[smallest], a[i]] = [a[i], a[smallest]];
                i = smallest;
            }
        }
    }
};  