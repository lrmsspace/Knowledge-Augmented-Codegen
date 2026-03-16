// Source: https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/   |   Difficulty: Hard
//
// Problem Description:
// In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
//
// In one move the snake can:
//
//
// 	Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
// 	Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
// 	
// 	Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
// 	
//
//
// Return the minimum number of moves to reach the target.
//
// If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [[0,0,0,0,0,1],
//                [1,1,0,0,1,0],
//                [0,0,0,0,1,1],
//                [0,0,1,0,1,0],
//                [0,1,1,0,0,0],
//                [0,1,1,0,0,0]]
// Output: 11
// Explanation:
// One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
//
// Constraints:
// 2 <= n <= 100
// 	0 <= grid[i][j] <= 1
// 	It is guaranteed that the snake starts at empty cells.
//



int minimumMoves(int** grid, int gridSize, int* gridColSize){
    int n = gridSize;
    typedef struct {
        int r, c, dir; // dir: 0-horizontal, 1-vertical
    } State;
    #define MAX_QUEUE (n * n * 2)
    State queue[MAX_QUEUE];
    int dist[MAX_QUEUE];
    int front = 0, back = 0;

    State start = {0, 0, 0};
    queue[back] = start;
    dist[back] = 0;
    back++;

    int target_r = n - 1;
    int target_c = n - 2;

    while (front < back) {
        State curr = queue[front];
        int curr_dist = dist[front];
        front++;

        if (curr.r == target_r && curr.c == target_c && curr.dir == 0) {
            return curr_dist;
        }

        // Move right
        if (curr.dir == 0) { // horizontal
            if (curr.c + 2 < n && grid[curr.r][curr.c + 2] == 0) {
                State next = {curr.r, curr.c + 1, 0};
                queue[back] = next;
                dist[back] = curr_dist + 1;
                back++;
            }
        } else { // vertical
            if (curr.c + 1 < n && grid[curr.r][curr.c + 1] == 0 && grid[curr.r + 1][curr.c + 1] == 0) {
                State next = {curr.r, curr.c + 1, 1};
                queue[back] = next;
                dist[back] = curr_dist + 1;
                back++;
            }
        }

        // Move down
        if (curr.dir == 0) { // horizontal
            if (curr.r + 1 < n && grid[curr.r + 1][curr.c] == 0 && grid[curr.r + 1][curr.c + 1] == 0) {
                State next = {curr.r + 1, curr.c, 0};
                queue[back] = next;
                dist[back] = curr_dist + 1;
                back++;
            }
        } else { // vertical
            if (curr.r + 2 < n && grid[curr.r + 2][curr.c] == 0) {
                State next = {curr.r + 1, curr.c, 1};
                queue[back] = next;
                dist[back] = curr_dist + 1;
                back++;
            }

        // Rotate clockwise
        if (curr.dir == 0) { // horizontal
            if (curr.r + 1 < n && grid[curr.r + 1][curr.c] == 0 && grid[curr.r + 1][curr.c + 1] == 0) {
                State next = {curr.r, curr.c, 1};
                queue[back] = next;
                dist[back] = curr_dist + 1;
                back++;
            }
        } else { // vertical
            if (curr.c + 1 < n && grid[curr.r][curr.c + 1] == 0 && grid[curr.r + 1][curr.c + 1] == 0) {
                State next = {curr.r, curr.c, 0};
                queue[back] = next;
                dist[back] = curr_dist + 1;
                back++;
            }
        }

    }
    return -1;
}
