// Source: https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:
//
//
// 	'S': Starting position of the student
// 	'L': Litter that must be collected (once collected, the cell becomes empty)
// 	'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
// 	'X': Obstacle the student cannot pass through
// 	'.': Empty space
//
//
// You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.
//
// Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.
//
// Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.
//
// Example:
// Input: classroom = ["S.", "XL"], energy = 2
//
// Output: 2
//
// Explanation:
//
//
// 	The student starts at cell (0, 0) with 2 units of energy.
// 	Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
// 	A valid sequence of moves to collect all litter is as follows:
// 	
// 		Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
// 		Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
// 	
// 	
// 	The student collects all the litter using 2 moves. Thus, the output is 2.
//
// Constraints:
// 1 <= m == classroom.length <= 20
// 	1 <= n == classroom[i].length <= 20
// 	classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
// 	1 <= energy <= 50
// 	There is exactly one 'S' in the grid.
// 	There are at most 10 'L' cells in the grid.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, stack, bfs, enumeration)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
//   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
//   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
//   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        // Find starting position and all litter positions
        int sx = -1, sy = -1;
        vector<pair<int, int>> litter;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }
        
        // If no litter, return 0
        if (litter.empty()) return 0;
        
        // Use BFS to find shortest path between any two points
        auto bfs = [&](int x1, int y1, int x2, int y2, int maxEnergy) -> int {
            queue<tuple<int, int, int>> q;
            set<pair<int, int>> visited;
            
            q.push({x1, y1, maxEnergy});
            visited.insert({x1, y1});
            
            int moves = 0;
            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};
            
            while (!q.empty()) {
                int size = q.size();
                moves++;
                
                for (int i = 0; i < size; i++) {
                    auto [x, y, eng] = q.front();
                    q.pop();
                    
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && 
                            classroom[nx][ny] != 'X' && visited.find({nx, ny}) == visited.end()) {
                            
                            int newEng = eng - 1;
                            if (classroom[nx][ny] == 'R') newEng = maxEnergy;
                            
                            if (newEng >= 0) {
                                if (nx == x2 && ny == y2) return moves;
                                visited.insert({nx, ny});
                                q.push({nx, ny, newEng});
                            }
                        }
                    }
                }
            }
            
            return -1;
        };
        
        // BFS to find shortest path between two points considering energy
        auto bfsPath = [&](int x1, int y1, int x2, int y2, int maxEnergy) -> int {
            queue<tuple<int, int, int, int>> q;
            map<pair<int, int>, pair<int, int>> visited; // position -> (min moves, energy at that position)
            
            q.push({x1, y1, 0, maxEnergy});
            visited[{x1, y1}] = {0, maxEnergy};
            
            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};
            
            while (!q.empty()) {
                auto [x, y, moves, eng] = q.front();
                q.pop();
                
                if (x == x2 && y == y2) return moves;
                
                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] != 'X') {
                        int newEng = eng - 1;
                        if (classroom[nx][ny] == 'R') newEng = maxEnergy;
                        
                        if (newEng >= 0) {
                            auto it = visited.find({nx, ny});
                            if (it == visited.end() || it->second.second < newEng) {
                                visited[{nx, ny}] = {moves + 1, newEng};
                                q.push({nx, ny, moves + 1, newEng});
                            }
                        }
                    }
                }
            }
            
            return -1;
        };
        
        // Try all permutations of litter collection order
        int totalMoves = INT_MAX;
        sort(litter.begin(), litter.end());
        
        do {
            int currentX = sx, currentY = sy;
            int currentEnergy = energy;
            int moves = 0;
            bool possible = true;
            
            for (auto [x, y] : litter) {
                // Find path from current position to litter
                int pathMoves = bfsPath(currentX, currentY, x, y, energy);
                
                if (pathMoves == -1) {
                    possible = false;
                    break;
                }
                
                // Update energy after reaching litter
                // Need to recompute energy tracking
                queue<tuple<int, int, int, int>> q;
                map<pair<int, int>, int> dist;
                
                q.push({currentX, currentY, 0, energy});
                dist[{currentX, currentY}] = 0;
                
                int dx[] = {-1, 1, 0, 0};
                int dy[] = {0, 0, -1, 1};
                int finalEnergy = -1;
                
                while (!q.empty()) {
                    auto [cx, cy, d, eng] = q.front();
                    q.pop();
                    
                    if (cx == x && cy == y) {
                        finalEnergy = eng;
                        break;
                    }
                    
                    for (int dir = 0; dir < 4; dir++) {
                        int nx = cx + dx[dir];
                        int ny = cy + dy[dir];
                        
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] != 'X') {
                            int newEng = eng - 1;
                            if (classroom[nx][ny] == 'R') newEng = energy;
                            
                            if (newEng >= 0 && dist.find({nx, ny}) == dist.end()) {
                                dist[{nx, ny}] = d + 1;
                                q.push({nx, ny, d + 1, newEng});
                            }
                        }
                    }
                }
                
                if (finalEnergy == -1) {
                    possible = false;
                    break;
                }
                
                moves += pathMoves;
                currentX = x;
                currentY = y;
                currentEnergy = finalEnergy;
            }
            
            if (possible) {
                totalMoves = min(totalMoves, moves);
            }
        } while (next_permutation(litter.begin(), litter.end()));
        
        return totalMoves == INT_MAX ? -1 : totalMoves;
    }
};
