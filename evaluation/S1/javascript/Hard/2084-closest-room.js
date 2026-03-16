// Source: https://leetcode.com/problems/closest-room/   |   Difficulty: Hard
//
// Problem Description:
// There is a hotel with n rooms. The rooms are represented by a 2D integer array rooms where rooms[i] = [roomIdi, sizei] denotes that there is a room with room number roomIdi and size equal to sizei. Each roomIdi is guaranteed to be unique.
//
// You are also given k queries in a 2D array queries where queries[j] = [preferredj, minSizej]. The answer to the jth query is the room number id of a room such that:
//
//
// 	The room has a size of at least minSizej, and
// 	abs(id - preferredj) is minimized, where abs(x) is the absolute value of x.
//
//
// If there is a tie in the absolute difference, then use the room with the smallest such id. If there is no such room, the answer is -1.
//
// Return an array answer of length k where answer[j] contains the answer to the jth query.
//
// Example:
// Input: rooms = [[2,2],[1,2],[3,2]], queries = [[3,1],[3,3],[5,2]]
// Output: [3,-1,3]
// Explanation: The answers to the queries are as follows:
// Query = [3,1]: Room number 3 is the closest as abs(3 - 3) = 0, and its size of 2 is at least 1. The answer is 3.
// Query = [3,3]: There are no rooms with a size of at least 3, so the answer is -1.
// Query = [5,2]: Room number 3 is the closest as abs(3 - 5) = 2, and its size of 2 is at least 2. The answer is 3.
//
// Constraints:
// n == rooms.length
// 	1 <= n <= 105
// 	k == queries.length
// 	1 <= k <= 104
// 	1 <= roomIdi, preferredj <= 107
// 	1 <= sizei, minSizej <= 107
//
// Helpful references (internal KB):
// - Point location in O(logn) (geometry, sweep-line, binary-search)
//   • When to use: Use this when you need to efficiently determine which region or face a given point lies within a planar subdivision, especially when queries are frequent and an O(log N) per query time is required.
//   • Idea: This algorithm uses a sweep-line approach with event points to maintain an ordered set of active non-vertical edges, augmented by a separate set for vertical edges. Point queries are resolved by binary searching these sets, achieving O(log N) query time after an initial preprocessing.
//   • Invariants: The set t contains all non-vertical edges currently intersected by the sweep-line, ordered by their y-coordinate at the sweep-line's x-position.; The set vert contains all vertical edges whose minimum y-coordinate is at the current sweep-line x-position, cleared for each new x-coordinate.
//   • Tips: Carefully define event types: add edge, remove edge, query point, vertical edge.; Use a balanced binary search tree (e.g., std::set in C++) for active non-vertical edges.
//   • Pitfalls: Incorrectly implementing the geometric comparator for non-vertical edges can lead to wrong ordering.; Failing to handle degenerate cases, such as points on edges or vertices, can result in incorrect face identification.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} rooms
 * @param {number[][]} queries
 * @return {number[]}
 */
var closestRoom = function(rooms, queries) {
    const sortedRooms = rooms.sort((a, b) => b[1] - a[1]);
    const sortedQueries = queries.map((q, i) => [...q, i]).sort((a, b) => b[1] - a[1]);
    const result = new Array(queries.length).fill(-1);
    const availableRooms = new Set();
    let roomIndex = 0;

    for (const [preferred, minSize, queryIndex] of sortedQueries) {
        while (roomIndex < sortedRooms.length && sortedRooms[roomIndex][1] >= minSize) {
            availableRooms.add(sortedRooms[roomIndex][0]);
            roomIndex++;
        }
        if (availableRooms.size > 0) {
            result[queryIndex] = findClosestRoom(preferred, availableRooms);
        }
    }

    return result;
};
