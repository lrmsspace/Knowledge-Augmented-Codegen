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

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string start;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                start += to_string(board[i][j]);
            }
        }
        
        string target = "123450";
        vector<vector<int>> neighbors = {
            {1, 3},    // index 0
            {0, 2, 4}, // index 1
            {1, 5},    // index 2
            {0, 4},    // index 3
            {1, 3, 5}, // index 4
            {2, 4}     // index 5
        };
        
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        
        q.push({start, 0});
        visited.insert(start);
        
        while (!q.empty()) {
            auto [curr, steps] = q.front();
            q.pop();
            
            if (curr == target) {
                return steps;
            }
            
            int zeroIndex = curr.find('0');
            for (int neighbor : neighbors[zeroIndex]) {
                string next = curr;
                swap(next[zeroIndex], next[neighbor]);
                
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push({next, steps + 1});
                }
            }
        }
        
        return -1;          
    }
};
