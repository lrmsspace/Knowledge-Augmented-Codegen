// Source: https://leetcode.com/problems/cat-and-mouse-ii/   |   Difficulty: Hard
//
// Problem Description:
// A game is played by a cat and a mouse named Cat and Mouse.
//
// The environment is represented by a grid of size rows x cols, where each element is a wall, floor, player (Cat, Mouse), or food.
//
//
// 	Players are represented by the characters 'C'(Cat),'M'(Mouse).
// 	Floors are represented by the character '.' and can be walked on.
// 	Walls are represented by the character '#' and cannot be walked on.
// 	Food is represented by the character 'F' and can be walked on.
// 	There is only one of each character 'C', 'M', and 'F' in grid.
//
//
// Mouse and Cat play according to the following rules:
//
//
// 	Mouse moves first, then they take turns to move.
// 	During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
// 	catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
// 	Staying in the same position is allowed.
// 	Mouse can jump over Cat.
//
//
// The game can end in 4 ways:
//
//
// 	If Cat occupies the same position as Mouse, Cat wins.
// 	If Cat reaches the food first, Cat wins.
// 	If Mouse reaches the food first, Mouse wins.
// 	If Mouse cannot get to the food within 1000 turns, Cat wins.
//
//
// Given a rows x cols matrix grid and two integers catJump and mouseJump, return true if Mouse can win the game if both Cat and Mouse play optimally, otherwise return false.
//
// Example:
// Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
// Output: true
// Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
//
// Constraints:
// rows == grid.length
// 	cols = grid[i].length
// 	1 <= rows, cols <= 8
// 	grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
// 	There is only one of each character 'C', 'M', and 'F' in grid.
// 	1 <= catJump, mouseJump <= 8
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean canMouseWin(String[] grid, int catJump, int mouseJump) {
        int rows = grid.length, cols = grid[0].length();
        int catPos = 0, mousePos = 0, foodPos = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                char cell = grid[i].charAt(j);
                if (cell == 'C') catPos = i * cols + j;
                else if (cell == 'M') mousePos = i * cols + j;
                else if (cell == 'F') foodPos = i * cols + j;
            }
        }

        return dfs(grid, catJump, mouseJump, catPos, mousePos, foodPos, true, new Boolean[rows * cols][rows * cols][2]);            
    }
}
