// Source: https://leetcode.com/problems/trapping-rain-water-ii/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
//
// Example:
// Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
// Output: 4
// Explanation: After the rain, water is trapped between the blocks.
// We have two small ponds 1 and 3 units trapped.
// The total volume of water trapped is 4.
//
// Constraints:
// m == heightMap.length
// 	n == heightMap[i].length
// 	1 <= m, n <= 200
// 	0 <= heightMap[i][j] <= 2 * 104
//

int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize) {
    if (heightMapSize <= 2 || heightMapColSize[0] <= 2) return 0;

    int m = heightMapSize;
    int n = heightMapColSize[0];
    bool visited[m][n];
    memset(visited, 0, sizeof(visited));

    typedef struct {
        int x, y, height;
    } Cell;

    #define MAX_HEAP_SIZE (m * n)
    Cell minHeap[MAX_HEAP_SIZE];
    int heapSize = 0;

    void swap(int i, int j) {
        Cell temp = minHeap[i];
        minHeap[i] = minHeap[j];
        minHeap[j] = temp;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (minHeap[parent].height <= minHeap[index].height) break;
            swap(parent, index);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        while (1) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < heapSize && minHeap[left].height < minHeap[smallest].height) {
                smallest = left;
            }
            if (right < heapSize && minHeap[right].height < minHeap[smallest].height) {
                smallest = right;
            }
            if (smallest == index) break;
            swap(index, smallest);
            index = smallest;
        }
    }

    void push(Cell cell) {
        minHeap[heapSize] = cell;
        heapifyUp(heapSize);
        heapSize++;
    }

    Cell pop() {
        Cell top = minHeap[0];
        heapSize--;
        minHeap[0] = minHeap[heapSize];
        heapifyDown(0);
        return top;
    }

    // Initialize the heap with border cells
    for (int i = 0; i < m; i++) {
        push((Cell){i, 0, heightMap[i][0]});
        push((Cell){i, n - 1, heightMap[i][n - 1]});
        visited[i][0] = true;
        visited[i][n - 1] = true;
    }
    for (int j = 1; j < n - 1; j++) {
        push((Cell){0, j, heightMap[0][j]});
        push((Cell){m - 1, j, heightMap[m - 1][j]});
        visited[0][j] = true;
        visited[m - 1][j] = true;
    }
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int waterTrapped = 0;
    while (heapSize > 0) {
        Cell cell = pop();
        for (int d = 0; d < 4; d++) {
            int newX = cell.x + directions[d][0];
            int newY = cell.y + directions[d][1];
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && !visited[newX][newY]) {
                visited[newX][newY] = true;
                int newHeight = heightMap[newX][newY];
                if (newHeight < cell.height) {
                    waterTrapped += cell.height - newHeight;
                    newHeight = cell.height;
                }
                push((Cell){newX, newY, newHeight});
            }
        }
    }
    return waterTrapped;
}
