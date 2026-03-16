// Source: https://leetcode.com/problems/walking-robot-simulation/   |   Difficulty: Medium
//
// Problem Description:
// A robot on an infinite XY-plane starts at point (0, 0) facing north. The robot receives an array of integers commands, which represents a sequence of moves that it needs to execute. There are only three possible types of instructions the robot can receive:
//
//
// 	-2: Turn left 90 degrees.
// 	-1: Turn right 90 degrees.
// 	1 <= k <= 9: Move forward k units, one unit at a time.
//
//
// Some of the grid squares are obstacles. The ith obstacle is at grid point obstacles[i] = (xi, yi). If the robot runs into an obstacle, it will stay in its current location (on the block adjacent to the obstacle) and move onto the next command.
//
// Return the maximum squared Euclidean distance that the robot reaches at any point in its path (i.e. if the distance is 5, return 25).
//
// Note:
//
//
// 	There can be an obstacle at (0, 0). If this happens, the robot will ignore the obstacle until it has moved off the origin. However, it will be unable to return to (0, 0) due to the obstacle.
// 	North means +Y direction.
// 	East means +X direction.
// 	South means -Y direction.
// 	West means -X direction.
//
// Example:
// Input: commands = [4,-1,3], obstacles = []
//
// Output: 25
//
// Explanation: 
//
// The robot starts at (0, 0):
//
//
// 	Move north 4 units to (0, 4).
// 	Turn right.
// 	Move east 3 units to (3, 4).
//
//
// The furthest point the robot ever gets from the origin is (3, 4), which squared is 32 + 42 = 25 units away.
//
// Constraints:
// 1 <= commands.length <= 104
// 	commands[i] is either -2, -1, or an integer in the range [1, 9].
// 	0 <= obstacles.length <= 104
// 	-3 * 104 <= xi, yi <= 3 * 104
// 	The answer is guaranteed to be less than 231.
//
// Helpful references (internal KB):
// - Minimum Enclosing Circle (geometry, number, simulation)
//   • When to use: When you need to find the smallest circle that contains all given points in a 2D plane, often with a requirement for expected linear time complexity.
//   • Idea: This algorithm iteratively constructs the Minimum Enclosing Circle (MEC) by considering points one by one, potentially updating the circle if a new point lies outside. It achieves an expected linear time complexity, O(N), through randomization.
//   • Invariants: The current circle C is the MEC for the subset of points processed so far.; If C is defined by 1 point p_i, it is the MEC of points processed so far that passes through p_i.
//   • Tips: Randomly shuffle input points to achieve expected linear time complexity.; The Minimum Enclosing Circle is always defined by 2 or 3 points on its boundary.
//   • Pitfalls: A naive implementation without randomization can lead to O(N^3) worst-case time complexity.; Floating-point precision issues can arise in geometric calculations, requiring careful handling.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Floyd-Warshall Algorithm (number, simulation)
//   • When to use: When you need to find the shortest paths between all possible pairs of vertices in a graph. It is particularly suitable for dense graphs or when negative edge weights are present, as long as no negative cycles are reachable.
//   • Idea: Floyd-Warshall is a dynamic programming algorithm that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path distances, achieving an O(V^3) time complexity.
//   • Invariants: After the k-th iteration, dist[i][j] contains the shortest path from i to j considering only vertices 0 to k-1 as intermediate nodes.; For any pair (i, j), dist[i][j] is always greater than or equal to the true shortest path distance from i to j (or infinity if unreachable).
//   • Tips: Initialize distances: direct edge weights, infinity for no direct edge, zero for self-loops.; The outermost loop must iterate through intermediate vertices (k).
//   • Pitfalls: Incorrect loop order (k not outermost) leads to incorrect results.; Integer overflow with large path sums if not using appropriate data types.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize) {
    // Directions: North, East, South, West
    int dirX[4] = {0, 1, 0, -1};
    int dirY[4] = {1, 0, -1, 0};
    int direction = 0; // Start facing North
    int x = 0, y = 0; // Start at origin
    int maxDistSq = 0;

    // Use a hash set to store obstacles for O(1) access
    #define HASH_SIZE 65536
    typedef struct ObstacleNode {
        int x;
        int y;
        struct ObstacleNode* next;
    } ObstacleNode;

    ObstacleNode* obstacleHash[HASH_SIZE] = {0};

    // Hash function
    unsigned int hash(int x, int y) {
        return ((unsigned int)(x * 73856093) ^ (unsigned int)(y * 19349663)) % HASH_SIZE;
    }

    // Insert obstacles into hash set
    for (int i = 0; i < obstaclesSize; i++) {
        int ox = obstacles[i][0];
        int oy = obstacles[i][1];
        unsigned int h = hash(ox, oy);
        ObstacleNode* node = (ObstacleNode*)malloc(sizeof(ObstacleNode));
        node->x = ox;
        node->y = oy;
        node->next = obstacleHash[h];
        obstacleHash[h] = node;
    }

    // Check if a position is an obstacle
    int isObstacle(int x, int y) {
        unsigned int h = hash(x, y);
        ObstacleNode* node = obstacleHash[h];
        while (node) {
            if (node->x == x && node->y == y) {
                return 1;
            }
            node = node->next;
        }
        return 0;
    }

    // Process each command
    for (int i = 0; i < commandsSize; i++) {
        int cmd = commands[i];
        if (cmd == -2) {
            // Turn left
            direction = (direction + 3) % 4;
        } else if (cmd == -1) {
            // Turn right
            direction = (direction + 1) % 4;
        } else {
            // Move forward cmd steps
            for (int step = 0; step < cmd; step++) {
                int nextX = x + dirX[direction];
                int nextY = y + dirY[direction];
                if (isObstacle(nextX, nextY)) {
                    // Hit an obstacle, stop moving
                    break;
                } else {
                    x = nextX;
                    y = nextY;
                    int distSq = x * x + y * y;
                    if (distSq > maxDistSq) {
                        maxDistSq = distSq;
                    }
                }
            }
        }
    }
    // Free obstacle hash set
    for (int i = 0; i < HASH_SIZE; i++) {
        ObstacleNode* node = obstacleHash[i];
        while (node) {
            ObstacleNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    return maxDistSq;
}
