// Source: https://leetcode.com/problems/minimum-jumps-to-reach-home/   |   Difficulty: Medium
//
// Problem Description:
// A certain bug's home is on the x-axis at position x. Help them get there from position 0.
//
// The bug jumps according to the following rules:
//
//
// 	It can jump exactly a positions forward (to the right).
// 	It can jump exactly b positions backward (to the left).
// 	It cannot jump backward twice in a row.
// 	It cannot jump to any forbidden positions.
//
//
// The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.
//
// Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.
//
// Example:
// Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
// Output: 3
// Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
//
// Constraints:
// 1 <= forbidden.length <= 1000
// 	1 <= a, b, forbidden[i] <= 2000
// 	0 <= x <= 2000
// 	All the elements in forbidden are distinct.
// 	Position x is not forbidden.
//

int minimumJumps(int* forbidden, int forbiddenSize, int a, int b, int x) {
    #define MAX_POS 6000
    int visited[MAX_POS][2] = {0}; // visited[position][0: forward, 1: backward]
    for (int i = 0; i < forbiddenSize; i++) {
        if (forbidden[i] < MAX_POS) {
            visited[forbidden[i]][0] = 1;
            visited[forbidden[i]][1] = 1;
        }
    }

    typedef struct {
        int position;
        int backward;
        int steps;
    } State;

    State queue[MAX_POS * 2];
    int front = 0, rear = 0;

    queue[rear++] = (State){0, 0, 0};
    visited[0][0] = 1;

    while (front < rear) {
        State curr = queue[front++];
        if (curr.position == x) {
            return curr.steps;
        }

        // Jump forward
        int nextPos = curr.position + a;
        if (nextPos < MAX_POS && !visited[nextPos][0]) {
            visited[nextPos][0] = 1;
            queue[rear++] = (State){nextPos, 0, curr.steps + 1};
        }

        // Jump backward
        nextPos = curr.position - b;
        if (curr.backward == 0 && nextPos >= 0 && !visited[nextPos][1]) {
            visited[nextPos][1] = 1;
            queue[rear++] = (State){nextPos, 1, curr.steps + 1};
        }
    }

    return -1;
}
