// Source: https://leetcode.com/problems/minimum-total-distance-traveled/   |   Difficulty: Hard
//
// Problem Description:
// There are some robots and factories on the X-axis. You are given an integer array robot where robot[i] is the position of the ith robot. You are also given a 2D integer array factory where factory[j] = [positionj, limitj] indicates that positionj is the position of the jth factory and that the jth factory can repair at most limitj robots.
//
// The positions of each robot are unique. The positions of each factory are also unique. Note that a robot can be in the same position as a factory initially.
//
// All the robots are initially broken; they keep moving in one direction. The direction could be the negative or the positive direction of the X-axis. When a robot reaches a factory that did not reach its limit, the factory repairs the robot, and it stops moving.
//
// At any moment, you can set the initial direction of moving for some robot. Your target is to minimize the total distance traveled by all the robots.
//
// Return the minimum total distance traveled by all the robots. The test cases are generated such that all the robots can be repaired.
//
// Note that
//
//
// 	All robots move at the same speed.
// 	If two robots move in the same direction, they will never collide.
// 	If two robots move in opposite directions and they meet at some point, they do not collide. They cross each other.
// 	If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
// 	If the robot moved from a position x to a position y, the distance it moved is |y - x|.
//
// Example:
// Input: robot = [0,4,6], factory = [[2,2],[6,2]]
// Output: 4
// Explanation: As shown in the figure:
// - The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
// - The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
// - The third robot at position 6 will be repaired at the second factory. It does not need to move.
// The limit of the first factory is 2, and it fixed 2 robots.
// The limit of the second factory is 2, and it fixed 1 robot.
// The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4. It can be shown that we cannot achieve a better total distance than 4.
//
// Constraints:
// 1 <= robot.length, factory.length <= 100
// 	factory[j].length == 2
// 	-109 <= robot[i], positionj <= 109
// 	0 <= limitj <= robot.length
// 	The input will be generated such that it is always possible to repair every robot.
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Solving assignment problem using min-cost-flow (graph, dijkstra, bellman-ford)
//   • When to use: Use when finding a one-to-one assignment between two sets of entities, such as workers to tasks, to minimize the total cost. It's suitable for problems modelable as min-cost max-flow in a bipartite graph.
//   • Idea: This technique models the assignment problem as a minimum cost maximum flow problem on a specially constructed bipartite graph. It finds a perfect matching with the lowest total cost, typically with a polynomial time complexity depending on the shortest path algorithm used.
//   • Invariants: Flow conservation holds for all intermediate nodes in the network.; The flow on any edge never exceeds its defined capacity.
//   • Tips: Construct a bipartite graph with a source and sink nodes.; Set capacities to 1 for all assignment-related edges to ensure one-to-one mapping.
//   • Pitfalls: Incorrectly modeling capacities or costs on graph edges can lead to wrong solutions.; Forgetting to ensure a perfect matching (flow value equals N) is found for a complete assignment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minimumTotalDistance(int* robot, int robotSize, int** factory, int factorySize, int* factoryColSize) {
    // Sort the robot and factory arrays by their positions
    qsort(robot, robotSize, sizeof(int), compare);
    qsort(factory, factorySize, sizeof(int*), compareFactory);

    // Create a DP table to store the minimum total distance for repairing the first i robots with the first j factories
    long long dp[robotSize + 1][factorySize + 1];
    
    // Initialize the DP table with a large value
    for (int i = 0; i <= robotSize; i++) {
        for (int j = 0; j <= factorySize; j++) {
            dp[i][j] = LLONG_MAX;
        }
    }
    
    // Base case: No robots to repair means zero distance
    for (int j = 0; j <= factorySize; j++) {
        dp[0][j] = 0;
    }

    // Fill the DP table
    for (int i = 1; i <= robotSize; i++) {
        for (int j = 1; j <= factorySize; j++) {
            int position = factory[j - 1][0];
            int limit = factory[j - 1][1];
            long long distance = 0;

            // Try repairing up to 'limit' robots at this factory
            for (int k = 0; k < limit && i - k > 0; k++) {
                distance += abs(robot[i - k - 1] - position);
                if (dp[i - k - 1][j - 1] != LLONG_MAX) {
                    dp[i][j] = fmin(dp[i][j], dp[i - k - 1][j - 1] + distance);
                }
            }
        }
    }

    // The answer is the minimum total distance to repair all robots using any number of factories
    long long result = LLONG_MAX;
    for (int j = 0; j <= factorySize; j++) {
        result = fmin(result, dp[robotSize][j]);
    }

    return result;      
}
