# Source: https://leetcode.com/problems/alphabet-board-path/   |   Difficulty: Medium
#
# Problem Description:
# On an alphabet board, we start at position (0, 0), corresponding to character board[0][0].
#
# Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"], as shown in the diagram below.
#
#
#
# We may make the following moves:
#
#
# 	'U' moves our position up one row, if the position exists on the board;
# 	'D' moves our position down one row, if the position exists on the board;
# 	'L' moves our position left one column, if the position exists on the board;
# 	'R' moves our position right one column, if the position exists on the board;
# 	'!' adds the character board[r][c] at our current position (r, c) to the answer.
#
#
# (Here, the only positions that exist on the board are positions with letters on them.)
#
# Return a sequence of moves that makes our answer equal to target in the minimum number of moves.  You may return any path that does so.
#
# Example:
# Input: target = "leet"
# Output: "DDR!UURRR!!DDD!"
#
# Constraints:
# 1 <= target.length <= 100
# 	target consists only of English lowercase letters.
#

class Solution(object):
    def alphabetBoardPath(self, target):
        """
        :type target: str
        :rtype: str
        """
        board = {}
        for i in range(26):
            board[chr(ord('a') + i)] = (i // 5, i % 5)
        
        result = []
        curr_pos = (0, 0)
        
        for char in target:
            target_pos = board[char]
            vertical_move = target_pos[0] - curr_pos[0]
            horizontal_move = target_pos[1] - curr_pos[1]
            
            # Special case for 'z'
            if char == 'z':
                # Move horizontally first, then vertically
                if horizontal_move < 0:
                    result.append('L' * abs(horizontal_move))
                elif horizontal_move > 0:
                    result.append('R' * horizontal_move)
                
                if vertical_move < 0:
                    result.append('U' * abs(vertical_move))
                elif vertical_move > 0:
                    result.append('D' * vertical_move)
            else:
                # Move vertically first, then horizontally
                if vertical_move < 0:
                    result.append('U' * abs(vertical_move))
                elif vertical_move > 0:
                    result.append('D' * vertical_move)
                
                if horizontal_move < 0:
                    result.append('L' * abs(horizontal_move))
                elif horizontal_move > 0:
                    result.append('R' * horizontal_move)
            
            result.append('!')
            curr_pos = target_pos
        
        return ''.join(result)