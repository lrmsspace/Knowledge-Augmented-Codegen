// Source: https://leetcode.com/problems/zuma-game/   |   Difficulty: Hard
//
// Problem Description:
// You are playing a variation of the game Zuma.
//
// In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.
//
// Your goal is to clear all of the balls from the board. On each turn:
//
//
// 	Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
// 	If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
// 	
// 		If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
// 	
// 	
// 	If there are no more balls on the board, then you win the game.
// 	Repeat this process until you either win or do not have any more balls in your hand.
//
//
// Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.
//
// Example:
// Input: board = "WRRBBW", hand = "RB"
// Output: -1
// Explanation: It is impossible to clear all the balls. The best you can do is:
// - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
// - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
// There are still balls remaining on the board, and you are out of balls to insert.
//
// Constraints:
// 1 <= board.length <= 16
// 	1 <= hand.length <= 5
// 	board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
// 	The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.
//

int findMinStep(char* board, char* hand) {
    // Implementation of Zuma Game using backtracking and pruning
    
    #define COLORS 5
    #define MAX_HAND 5
    #define MAX_BOARD 16

    int handCount[COLORS] = {0};
    for (int i = 0; hand[i]; i++) {
        switch (hand[i]) {
            case 'R': handCount[0]++; break;
            case 'Y': handCount[1]++; break;
            case 'B': handCount[2]++; break;
            case 'G': handCount[3]++; break;
            case 'W': handCount[4]++; break;
        }
    }

    int minSteps = -1;

    void removeConsecutive(char* b) {
        int len = strlen(b);
        int i = 0;
        while (i < len) {
            int j = i;
            while (j < len && b[j] == b[i]) j++;
            if (j - i >= 3) {
                memmove(&b[i], &b[j], len - j + 1);
                len -= (j - i);
                i = 0; // Restart from beginning
            } else {
                i++;
            }
        }
    }

    void backtrack(char* b, int steps) {
        removeConsecutive(b);
        if (b[0] == '\0') {
            if (minSteps == -1 || steps < minSteps) {
                minSteps = steps;
            }
            return;
        }
        if (steps >= minSteps && minSteps != -1) return; // Prune

        int len = strlen(b);
        for (int i = 0; i <= len; i++) {
            for (int c = 0; c < COLORS; c++) {
                if (handCount[c] == 0) continue;

                char colorChar;
                switch (c) {
                    case 0: colorChar = 'R'; break;
                    case 1: colorChar = 'Y'; break;
                    case 2: colorChar = 'B'; break;
                    case 3: colorChar = 'G'; break;
                    case 4: colorChar = 'W'; break;
                }

                handCount[c]--;
                char newBoard[MAX_BOARD + MAX_HAND + 1];
                strncpy(newBoard, b, i);
                newBoard[i] = colorChar;
                strcpy(&newBoard[i + 1], &b[i]);
                backtrack(newBoard, steps + 1);
                handCount[c]++;
            }
        }
    }
    backtrack(board, 0);
    return minSteps;
}
