// Source: https://leetcode.com/problems/graph-connectivity-with-threshold/   |   Difficulty: Hard
//
// Problem Description:
// We have n cities labeled from 1 to n. Two different cities with labels x and y are directly connected by a bidirectional road if and only if x and y share a common divisor strictly greater than some threshold. More formally, cities with labels x and y have a road between them if there exists an integer z such that all of the following are true:
//
//
// 	x % z == 0,
// 	y % z == 0, and
// 	z > threshold.
//
//
// Given the two integers, n and threshold, and an array of queries, you must determine for each queries[i] = [ai, bi] if cities ai and bi are connected directly or indirectly. (i.e. there is some path between them).
//
// Return an array answer, where answer.length == queries.length and answer[i] is true if for the ith query, there is a path between ai and bi, or answer[i] is false if there is no path.
//
// Example:
// Input: n = 6, threshold = 2, queries = [[1,4],[2,5],[3,6]]
// Output: [false,false,true]
// Explanation: The divisors for each number:
// 1:   1
// 2:   1, 2
// 3:   1, 3
// 4:   1, 2, 4
// 5:   1, 5
// 6:   1, 2, 3, 6
// Using the underlined divisors above the threshold, only cities 3 and 6 share a common divisor, so they are the
// only ones directly connected. The result of each query:
// [1,4]   1 is not connected to 4
// [2,5]   2 is not connected to 5
// [3,6]   3 is connected to 6 through path 3--6
//
// Constraints:
// 2 <= n <= 104
// 	0 <= threshold <= n
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	1 <= ai, bi <= cities
// 	ai != bi
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
//   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
//   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
//   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
//   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
//   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number} threshold
 * @param {number[][]} queries
 * @return {boolean[]}
 */
var areConnected = function(n, threshold, queries) {
    // Disjoint Set Union (DSU) implementation
    class DSU {
        constructor(size) {
            this.parent = Array.from({ length: size }, (_, i) => i);
            this.rank = Array(size).fill(1);
        }
        find(x) {
            if (this.parent[x] !== x) {
                this.parent[x] = this.find(this.parent[x]); // Path compression
            }
            return this.parent[x];
        }
        union(x, y) {
            const rootX = this.find(x);
            const rootY = this.find(y);
            if (rootX !== rootY) {
                // Union by rank
                if (this.rank[rootX] > this.rank[rootY]) {
                    this.parent[rootY] = rootX;
                }
                else if (this.rank[rootX] < this.rank[rootY]) { 
                    this.parent[rootX] = rootY;
                }
                else {
                    this.parent[rootY] = rootX;
                    this.rank[rootX]++;
                }
            }
        }
    }
    
    const dsu = new DSU(n + 1);
    // Connect cities that share a common divisor greater than threshold
    for (let i = threshold + 1; i <= n; i++) {
        for (let j = 2 * i; j <= n; j += i) {
            dsu.union(i, j);
        }
    }
    // Process queries
    const result = [];
    for (const [a, b] of queries) {
        result.push(dsu.find(a) === dsu.find(b));
    }
    return result;
                
};
