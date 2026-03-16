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
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Check if point belongs to the convex pol (geometry, array, binary-search)
//   • When to use: This algorithm is used to efficiently determine if a given query point lies inside or on the boundary of a convex polygon, especially when many queries are performed on the same polygon.
//   • Idea: The core idea is to decompose the convex polygon into triangles originating from a reference vertex. Binary search is then used to find the specific triangle that could contain the query point, followed by a point-in-triangle check.
//   • Invariants: The reference point p_0 is the lexicographically smallest vertex of the polygon.; All polygon vertices p_1, ..., p_n are ordered counter-clockwise by polar angle around p_0.
//   • Tips: Choose a consistent reference point, typically the lexicographically smallest vertex, to simplify angular sorting.; Ensure polygon vertices are ordered (e.g., counter-clockwise) relative to the reference point for correct binary search behavior.
//   • Pitfalls: Floating point precision errors can lead to incorrect results for collinear points or boundary checks; prefer integer arithmetic with cross products.; Incorrectly handling boundary conditions (points exactly on an edge or vertex) can lead to false negatives or positives.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize) {
    // Directions: North, East, South, West
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int x = 0, y = 0; // Robot's current position
    int direction = 0; // Start facing north
    int maxDistanceSq = 0;

    // Create a hash set for obstacles for O(1) lookups
    #define HASH_SIZE 10007
    typedef struct Node {
        int x;
        int y;
        struct Node* next;
    } Node;

    Node* hashTable[HASH_SIZE] = {NULL};

    void insertObstacle(int x, int y) {
        int hashKey = ((x + 30000) * 60001 + (y + 30000)) % HASH_SIZE;
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->x = x;
        newNode->y = y;
        newNode->next = hashTable[hashKey];
        hashTable[hashKey] = newNode;
    }

    int isObstacle(int x, int y) {
        int hashKey = ((x + 30000) * 60001 + (y + 30000)) % HASH_SIZE;
        Node* current = hashTable[hashKey];
        while (current) {
            if (current->x == x && current->y == y) {
                return 1; // Obstacle found
            }
            current = current->next;
        }
        return 0; // No obstacle
    }

    // Insert obstacles into the hash set
    for (int i = 0; i < obstaclesSize; i++) {
        insertObstacle(obstacles[i][0], obstacles[i][1]);
    }

    // Process each command
    for (int i = 0; i < commandsSize; i++) {
        if (commands[i] == -2) { // Turn left
            direction = (direction + 3) % 4; // Equivalent to -1 mod 4
        } else if (commands[i] == -1) { // Turn right
            direction = (direction + 1) % 4;
        } else { // Move forward commands[i] steps
            for (int step = 0; step < commands[i]; step++) {
                int nextX = x + dx[direction];
                int nextY = y + dy[direction];
                if (isObstacle(nextX, nextY)) {
                    break; // Stop moving if there's an obstacle
                }
                x = nextX;
                y = nextY;
                int distanceSq = x * x + y * y;
                if (distanceSq > maxDistanceSq) {
                    maxDistanceSq = distanceSq; // Update max distance squared
                }
            }
        }

}
    return maxDistanceSq;
}