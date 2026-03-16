// Source: https://leetcode.com/problems/escape-a-large-maze/   |   Difficulty: Hard
//
// Problem Description:
// There is a 1 million by 1 million grid on an XY-plane, and the coordinates of each grid square are (x, y).
//
// We start at the source = [sx, sy] square and want to reach the target = [tx, ty] square. There is also an array of blocked squares, where each blocked[i] = [xi, yi] represents a blocked square with coordinates (xi, yi).
//
// Each move, we can walk one square north, east, south, or west if the square is not in the array of blocked squares. We are also not allowed to walk outside of the grid.
//
// Return true if and only if it is possible to reach the target square from the source square through a sequence of valid moves.
//
// Example:
// Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
// Output: false
// Explanation: The target square is inaccessible starting from the source square because we cannot move.
// We cannot move north or east because those squares are blocked.
// We cannot move south or west because we cannot go outside of the grid.
//
// Constraints:
// 0 <= blocked.length <= 200
// 	blocked[i].length == 2
// 	0 <= xi, yi < 106
// 	source.length == target.length == 2
// 	0 <= sx, sy, tx, ty < 106
// 	source != target
// 	It is guaranteed that source and target are not blocked.
//

bool isEscapePossible(int** blocked, int blockedSize, int* blockedColSize, int* source, int sourceSize, int* target, int targetSize) {
    /* Since the maximum number of blocked cells is 200, the maximum area they can enclose is small.
       We can perform a BFS from both source and target up to a certain limit (e.g., 20000 steps).
       If we reach the target or exceed the limit, we return true. If we exhaust all possibilities
       without reaching the target or exceeding the limit, we return false. */

    #define GRID_SIZE 1000000
    #define MAX_STEPS 20000

    typedef struct {
        int x, y;
    } Point;

    typedef struct {
        Point *data;
        int front, rear, size, capacity;
    } Queue;

    Queue* createQueue(int capacity) {
        Queue *queue = (Queue*)malloc(sizeof(Queue));
        queue->data = (Point*)malloc(capacity * sizeof(Point));
        queue->front = queue->rear = queue->size = 0;
        queue->capacity = capacity;
        return queue;
    }

    void enqueue(Queue *queue, Point p) {
        if (queue->size == queue->capacity) return; // Queue full
        queue->data[queue->rear] = p;
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->size++;
    }

    Point dequeue(Queue *queue) {
        Point p = { -1, -1 };
        if (queue->size == 0) return p; // Queue empty
        p = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return p;
    }

    int isEmpty(Queue *queue) {
        return queue->size == 0;
    }

    void freeQueue(Queue *queue) {
        free(queue->data);
        free(queue);
    }

    // Hash function for blocked cells
    #define HASH_SIZE 100003
    typedef struct HashSet {
        int **table;
    } HashSet;

    HashSet* createHashSet() {
        HashSet *set = (HashSet*)malloc(sizeof(HashSet));
        set->table = (int**)calloc(HASH_SIZE, sizeof(int*));
        return set;
    }

    int hash(int x, int y) {
        return ((long long)x * GRID_SIZE + y) % HASH_SIZE;     
    }
    void addBlocked(HashSet *set, int x, int y) {
        int h = hash(x, y);
        int *node = (int*)malloc(2 * sizeof(int));
        node[0] = x; node[1] = y;
        node[2] = (long long)set->table[h]; // Store next pointer
        set->table[h] = node;
    }
    int isBlocked(HashSet *set, int x, int y) {
        int h = hash(x, y);
        int *node = set->table[h];
        while (node) {
            if (node[0] == x && node[1] == y) return 1;
            node = (int*)node[2];
        }
        return 0;
    }
    void freeHashSet(HashSet *set) {
        for (int i = 0; i < HASH_SIZE; ++i) {
            int *node = set->table[i];
            while (node) {
                int *temp = (int*)node[2];
                free(node);
                node = temp;
            }
        }
        free(set->table);
        free(set);
    }
    int bfs(int *start, int *end, HashSet *blockedSet) {
        Queue *queue = createQueue(MAX_STEPS);
        HashSet *visited = createHashSet();
        enqueue(queue, (Point){start[0], start[1]});
        addBlocked(visited, start[0], start[1]);
        int directions[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        int steps = 0;

        while (!isEmpty(queue) && steps < MAX_STEPS) {
            Point p = dequeue(queue);
            if (p.x == end[0] && p.y == end[1]) {
                freeQueue(queue);
                freeHashSet(visited);
                return 1; // Reached target
            }
            for (int i = 0; i < 4; ++i) {
                int nx = p.x + directions[i][0];
                int ny = p.y + directions[i][1];
                if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE &&
                    !isBlocked(blockedSet, nx, ny) &&
                    !isBlocked(visited, nx, ny)) {
                    enqueue(queue, (Point){nx, ny});
                    addBlocked(visited, nx, ny);
                }
            }
            steps++;
        }

        freeQueue(queue);
        freeHashSet(visited);
        return steps >= MAX_STEPS; // If we exceeded max steps, we assume escape is possible
    }
    HashSet *blockedSet = createHashSet();
    for (int i = 0; i < blockedSize; ++i) {
        addBlocked(blockedSet, blocked[i][0], blocked[i][1]);
    }
    int canEscapeFromSource = bfs(source, target, blockedSet);
    int canEscapeFromTarget = bfs(target, source, blockedSet);
    freeHashSet(blockedSet);
    return canEscapeFromSource && canEscapeFromTarget; 
}
