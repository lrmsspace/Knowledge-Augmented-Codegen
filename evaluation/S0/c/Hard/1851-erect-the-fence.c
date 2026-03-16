// Source: https://leetcode.com/problems/erect-the-fence/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.
//
// Fence the entire garden using the minimum length of rope, as it is expensive. The garden is well-fenced only if all the trees are enclosed.
//
// Return the coordinates of trees that are exactly located on the fence perimeter. You may return the answer in any order.
//
// Example:
// Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
// Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
// Explanation: All the trees will be on the perimeter of the fence except the tree at [2, 2], which will be inside the fence.
//
// Constraints:
// 1 <= trees.length <= 3000
// 	trees[i].length == 2
// 	0 <= xi, yi <= 100
// 	All the given positions are unique.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** outerTrees(int** trees, int treesSize, int* treesColSize, int* returnSize, int** returnColumnSizes) {
    // Implementation of the Jarvis March (Gift Wrapping) algorithm to find the convex hull
    
    if (treesSize <= 3) {
        *returnSize = treesSize;
        *returnColumnSizes = (int*)malloc(treesSize * sizeof(int));
        for (int i = 0; i < treesSize; i++) {
            (*returnColumnSizes)[i] = 2;
        }
        return trees;
    }

    // Function to calculate orientation
    int orientation(int* p, int* q, int* r) {
        return (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    }

    // Find the leftmost point
    int leftmost = 0;
    for (int i = 1; i < treesSize; i++) {
        if (trees[i][0] < trees[leftmost][0]) {
            leftmost = i;
        }
    }

    int** hull = (int**)malloc(treesSize * sizeof(int*));
    int hullSize = 0;
    int p = leftmost;

    do {
        hull[hullSize++] = trees[p];
        int next = (p + 1) % treesSize;

        for (int i = 0; i < treesSize; i++) {
            int o = orientation(trees[p], trees[i], trees[next]);
            if (o < 0) {
                next = i;
            } else if (o == 0) {
                // If collinear, choose the farthest point
                int dist1 = (trees[i][0] - trees[p][0]) * (trees[i][0] - trees[p][0]) +
                            (trees[i][1] - trees[p][1]) * (trees[i][1] - trees[p][1]);
                int dist2 = (trees[next][0] - trees[p][0]) * (trees[next][0] - trees[p][0]) +
                            (trees[next][1] - trees[p][1]) * (trees[next][1] - trees[p][1]);
                if (dist1 > dist2) {
                    next = i;
                }
            }
        }

        // Check for collinear points between p and next
        for (int i = 0; i < treesSize; i++) {
            if (i != p && i != next && orientation(trees[p], trees[i], trees[next]) == 0) {
                hull[hullSize++] = trees[i];
            }
        }
        p = next;
    } while (p != leftmost);
    // Remove duplicates from hull
    int** uniqueHull = (int**)malloc(hullSize * sizeof(int*));
    int uniqueSize = 0;
    for (int i = 0; i < hullSize; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < uniqueSize; j++) {
            if (hull[i][0] == uniqueHull[j][0] && hull[i][1] == uniqueHull[j][1]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            uniqueHull[uniqueSize++] = hull[i];
        }
    }
    free(hull);
    *returnSize = uniqueSize;
    *returnColumnSizes = (int*)malloc(uniqueSize * sizeof(int));
    for (int i = 0; i < uniqueSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return uniqueHull;
}
