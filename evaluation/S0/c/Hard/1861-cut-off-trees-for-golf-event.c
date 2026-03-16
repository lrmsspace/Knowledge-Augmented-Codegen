// Source: https://leetcode.com/problems/cut-off-trees-for-golf-event/   |   Difficulty: Hard
//
// Problem Description:
// You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an m x n matrix. In this matrix:
//
//
// 	0 means the cell cannot be walked through.
// 	1 represents an empty cell that can be walked through.
// 	A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.
//
//
// In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.
//
// You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes 1 (an empty cell).
//
// Starting from the point (0, 0), return the minimum steps you need to walk to cut off all the trees. If you cannot cut off all the trees, return -1.
//
// Note: The input is generated such that no two trees have the same height, and there is at least one tree needs to be cut off.
//
// Example:
// Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
// Output: 6
// Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
//
// Constraints:
// m == forest.length
// 	n == forest[i].length
// 	1 <= m, n <= 50
// 	0 <= forest[i][j] <= 109
// 	Heights of all trees are distinct.
//

int cutOffTree(int** forest, int forestSize, int* forestColSize) {
    int rows = forestSize;
    int cols = forestColSize[0];
    typedef struct {
        int row;
        int col;
        int height;
    } Tree;
    int treeCount = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (forest[r][c] > 1) {
                treeCount++;
            }
        }
    }
    Tree *trees = (Tree*)malloc(treeCount * sizeof(Tree));
    if (!trees) return -1;
    int idx = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (forest[r][c] > 1) {
                trees[idx].row = r;
                trees[idx].col = c;
                trees[idx].height = forest[r][c];
                idx++;
            }
        }
    }
    // Sort trees by height
    int cmpTree(const void *a, const void *b) {
        return ((Tree*)a)->height - ((Tree*)b)->height;
    }
    qsort(trees, treeCount, sizeof(Tree), cmpTree);

    // BFS function to find shortest path
    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int bfs(int startRow, int startCol, int targetRow, int targetCol) {
        if (startRow == targetRow && startCol == targetCol) return 0;
        int visited[50][50] = {0};
        typedef struct {
            int row;
            int col;
            int steps;
        } Node;
        Node queue[2500];
        int front = 0, back = 0;
        queue[back++] = (Node){startRow, startCol, 0};
        visited[startRow][startCol] = 1;

        while (front < back) {
            Node current = queue[front++];
            for (int d = 0; d < 4; ++d) {
                int newRow = current.row + directions[d][0];
                int newCol = current.col + directions[d][1];
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                    forest[newRow][newCol] != 0 && !visited[newRow][newCol]) {
                    if (newRow == targetRow && newCol == targetCol) {
                        return current.steps + 1;
                    }
                    visited[newRow][newCol] = 1;
                    queue[back++] = (Node){newRow, newCol, current.steps + 1};
                }
            }
        }
        return -1;
        
}
