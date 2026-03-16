// Source: https://leetcode.com/problems/open-the-lock/   |   Difficulty: Medium
//
// Problem Description:
// You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.
//
// The lock initially starts at '0000', a string representing the state of the 4 wheels.
//
// You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.
//
// Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.
//
// Example:
// Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
// Output: 6
// Explanation: 
// A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
// Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
// because the wheels of the lock become stuck after the display becomes the dead end "0102".
//
// Constraints:
// 1 <= deadends.length <= 500
// 	deadends[i].length == 4
// 	target.length == 4
// 	target will not be in the list deadends.
// 	target and deadends[i] consist of digits only.
//

int openLock(char** deadends, int deadendsSize, char* target) {
    // BFS approach
    #define MAX_COMBO 10000

    int deadSet[MAX_COMBO] = {0};
    for (int i = 0; i < deadendsSize; i++) {
        int num = (deadends[i][0] - '0') * 1000 + (deadends[i][1] - '0') * 100 + (deadends[i][2] - '0') * 10 + (deadends[i][3] - '0');
        deadSet[num] = 1;
    }

    int targetNum = (target[0] - '0') * 1000 + (target[1] - '0') * 100 + (target[2] - '0') * 10 + (target[3] - '0');

    if (deadSet[0]) return -1;

    int queue[MAX_COMBO];
    int front = 0, rear = 0;
    int visited[MAX_COMBO] = {0};
    visited[0] = 1;
    queue[rear++] = 0;
    int steps = 0;

    while (front < rear) {
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            int curr = queue[front++];
            if (curr == targetNum) return steps;

            for (int j = 0; j < 4; j++) {
                int digit = (curr / (int)pow(10, 3 - j)) % 10;
                for (int move = -1; move <= 1; move += 2) {
                    int newDigit = (digit + move + 10) % 10;
                    int newCombo = curr + (newDigit - digit) * (int)pow(10, 3 - j);
                    if (!deadSet[newCombo] && !visited[newCombo]) {
                        visited[newCombo] = 1;
                        queue[rear++] = newCombo;
                    }
                }
            }
        }
        steps++;
    }

    return -1;      
}
