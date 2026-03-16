// Source: https://leetcode.com/problems/asteroid-collision/   |   Difficulty: Medium
//
// Problem Description:
// We are given an array asteroids of integers representing asteroids in a row. The indices of the asteriod in the array represent their relative position in space.
//
// For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.
//
// Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.
//
// Example:
// Input: asteroids = [5,10,-5]
// Output: [5,10]
// Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
//
// Constraints:
// 2 <= asteroids.length <= 104
// 	-1000 <= asteroids[i] <= 1000
// 	asteroids[i] != 0
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* asteroidCollision(int* asteroids, int asteroidsSize, int* returnSize) {
    int* stack = (int*)malloc(sizeof(int) * asteroidsSize);
    int top = -1;

    for (int i = 0; i < asteroidsSize; i++) {
        int curr = asteroids[i];
        int destroyed = 0;

        while (top >= 0 && curr < 0 && stack[top] > 0) {
            if (stack[top] < -curr) {
                top--; // The top asteroid is destroyed
            } else if (stack[top] == -curr) {
                top--; // Both asteroids are destroyed
                destroyed = 1;
                break;
            } else {
                destroyed = 1; // Current asteroid is destroyed
                break;
            }
        }

        if (!destroyed) {
            stack[++top] = curr; // Push current asteroid onto the stack
        }
    }

    *returnSize = top + 1;
    return stack;       
}
