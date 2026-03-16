// Source: https://leetcode.com/problems/sliding-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0. A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
//
// The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
//
// Given the puzzle board board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.
//
// Example:
// Input: board = [[1,2,3],[4,0,5]]
// Output: 1
// Explanation: Swap the 0 and the 5 in one move.
//
// Constraints:
// board.length == 2
// 	board[i].length == 3
// 	0 <= board[i][j] <= 5
// 	Each value board[i][j] is unique.
//

int slidingPuzzle(int** board, int boardSize, int* boardColSize) {
    const char* target = "123450";
    char start[7];
    int idx = 0;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            start[idx++] = board[i][j] + '0';
        }
    }
    start[6] = '\0';
    if (strcmp(start, target) == 0) return 0;

    int directions[6][4] = {
        {1, 3, -1, -1}, // 0
        {0, 2, 4, -1}, // 1
        {1, 5, -1, -1}, // 2
        {0, 4, -1, -1}, // 3
        {1, 3, 5, -1}, // 4
        {2, 4, -1, -1}  // 5
    };
    typedef struct {
        char state[7];
        int zeroPos;
        int moves;
    } Node;
    Node queue[720]; // 6! = 720 possible states
    int front = 0, rear = 0;
    int visited[720] = {0};
    queue[rear].zeroPos = strchr(start, '0') - start;
    strcpy(queue[rear].state, start);
    queue[rear].moves = 0;
    visited[0] = 1; // Mark start state as visited
    rear++;
    while (front < rear) {
        Node current = queue[front++];
        for (int i = 0; i < 4; i++) {
            int newZeroPos = directions[current.zeroPos][i];
            if (newZeroPos == -1) continue;
            Node next = current;
            // Swap 0 with the adjacent number
            char temp = next.state[current.zeroPos];
            next.state[current.zeroPos] = next.state[newZeroPos];
            next.state[newZeroPos] = temp;
            next.zeroPos = newZeroPos;
            next.moves++;
            if (strcmp(next.state, target) == 0) {
                return next.moves;
            }
            // Check if this state has been visited
            int hash = 0;
            for (int j = 0; j < 6; j++) {
                hash = hash * 10 + (next.state[j] - '0');
            }
            if (!visited[hash]) {
                visited[hash] = 1;
                queue[rear++] = next;
            }
        }
    }
    return -1;
}
