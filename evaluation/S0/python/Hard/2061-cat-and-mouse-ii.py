# Source: https://leetcode.com/problems/cat-and-mouse-ii/   |   Difficulty: Hard
#
# Problem Description:
# A game is played by a cat and a mouse named Cat and Mouse.
#
# The environment is represented by a grid of size rows x cols, where each element is a wall, floor, player (Cat, Mouse), or food.
#
#
# 	Players are represented by the characters 'C'(Cat),'M'(Mouse).
# 	Floors are represented by the character '.' and can be walked on.
# 	Walls are represented by the character '#' and cannot be walked on.
# 	Food is represented by the character 'F' and can be walked on.
# 	There is only one of each character 'C', 'M', and 'F' in grid.
#
#
# Mouse and Cat play according to the following rules:
#
#
# 	Mouse moves first, then they take turns to move.
# 	During each turn, Cat and Mouse can jump in one of the four directions (left, right, up, down). They cannot jump over the wall nor outside of the grid.
# 	catJump, mouseJump are the maximum lengths Cat and Mouse can jump at a time, respectively. Cat and Mouse can jump less than the maximum length.
# 	Staying in the same position is allowed.
# 	Mouse can jump over Cat.
#
#
# The game can end in 4 ways:
#
#
# 	If Cat occupies the same position as Mouse, Cat wins.
# 	If Cat reaches the food first, Cat wins.
# 	If Mouse reaches the food first, Mouse wins.
# 	If Mouse cannot get to the food within 1000 turns, Cat wins.
#
#
# Given a rows x cols matrix grid and two integers catJump and mouseJump, return true if Mouse can win the game if both Cat and Mouse play optimally, otherwise return false.
#
# Example:
# Input: grid = ["####F","#C...","M...."], catJump = 1, mouseJump = 2
# Output: true
# Explanation: Cat cannot catch Mouse on its turn nor can it get the food before Mouse.
#
# Constraints:
# rows == grid.length
# 	cols = grid[i].length
# 	1 <= rows, cols <= 8
# 	grid[i][j] consist only of characters 'C', 'M', 'F', '.', and '#'.
# 	There is only one of each character 'C', 'M', and 'F' in grid.
# 	1 <= catJump, mouseJump <= 8
#

class Solution(object):
    def canMouseWin(self, grid, catJump, mouseJump):
        """
        :type grid: List[str]
        :type catJump: int
        :type mouseJump: int
        :rtype: bool
        """
        rows, cols = len(grid), len(grid[0])
        food = cat = mouse = None
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 'F':
                    food = (r, c)
                elif grid[r][c] == 'C':
                    cat = (r, c)
                elif grid[r][c] == 'M':
                    mouse = (r, c)
        
        @lru_cache(None)
        def dfs(cat_pos, mouse_pos, turn, depth):
            if depth > 1000:
                return False
            if cat_pos == mouse_pos or cat_pos == food:
                return False
            if mouse_pos == food:
                return True
            
            if turn == 0:  # Mouse's turn
                for dr, dc in [(0,1),(1,0),(0,-1),(-1,0)]:
                    for jump in range(mouseJump + 1):
                        nr = mouse_pos[0] + dr * jump
                        nc = mouse_pos[1] + dc * jump
                        if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != '#':
                            if dfs(cat_pos, (nr, nc), 1, depth + 1):
                                return True
                        else:
                            break
                return False
            else:  # Cat's turn
                for dr, dc in [(0,1),(1,0),(0,-1),(-1,0)]:
                    for jump in range(catJump + 1):
                        nr = cat_pos[0] + dr * jump
                        nc = cat_pos[1] + dc * jump
                        if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != '#':
                            if not dfs((nr, nc), mouse_pos, 0, depth + 1):
                                return False
                        else:
                            break
                return True
        
        return dfs(cat, mouse, 0, 0)