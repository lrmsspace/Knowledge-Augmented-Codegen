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
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minimumTotalDistance(int* robot, int robotSize, int** factory, int factorySize, int* factoryColSize) {
    // Sort robots and factories by their positions
    qsort(robot, robotSize, sizeof(int), compare);
    qsort(factory, factorySize, sizeof(int*), compareFactory);

    // Create a DP table to store the minimum total distance for repairing the first i robots with the first j factories
    long long dp[robotSize + 1][factorySize + 1];
    for (int i = 0; i <= robotSize; i++) {
        for (int j = 0; j <= factorySize; j++) {
            dp[i][j] = LLONG_MAX;
        }
    }
    dp[0][0] = 0;

    // Fill the DP table
    for (int i = 0; i <= robotSize; i++) {
        for (int j = 0; j < factorySize; j++) {
            if (dp[i][j] == LLONG_MAX) continue;
            // Case 1: Do not use the j-th factory
            dp[i][j + 1] = fmin(dp[i][j + 1], dp[i][j]);
            // Case 2: Use the j-th factory to repair some robots
            long long distance = 0;
            for (int k = 1; k <= factory[j][1] && i + k <= robotSize; k++) {
                distance += llabs(robot[i + k - 1] - factory[j][0]);
                dp[i + k][j + 1] = fmin(dp[i + k][j + 1], dp[i][j] + distance);
            }
        }
    }

    return dp[robotSize][factorySize];      
}
