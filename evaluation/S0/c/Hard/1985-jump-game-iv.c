// Source: https://leetcode.com/problems/jump-game-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers arr, you are initially positioned at the first index of the array.
//
// In one step you can jump from index i to index:
//
//
// 	i + 1 where: i + 1 < arr.length.
// 	i - 1 where: i - 1 >= 0.
// 	j where: arr[i] == arr[j] and i != j.
//
//
// Return the minimum number of steps to reach the last index of the array.
//
// Notice that you can not jump outside of the array at any time.
//
// Example:
// Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
// Output: 3
// Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	-108 <= arr[i] <= 108
//

int minJumps(int* arr, int arrSize) {
    if (arrSize <= 1) return 0;

    /* map from value to list of indices */
    #define MAP_CAP 100003
    struct MapEntry {
        int val;
        int *indices;
        int size;
        int cap;
        struct MapEntry *next;
    };
    struct MapEntry **map = (struct MapEntry**)calloc(MAP_CAP, sizeof(struct MapEntry*));
    if (!map) return -1;

    for (int i = 0; i < arrSize; ++i) {
        int h = ((unsigned int)(arr[i]) % MAP_CAP);
        struct MapEntry *e = map[h];
        while (e && e->val != arr[i]) e = e->next;
        if (!e) {
            e = (struct MapEntry*)malloc(sizeof(struct MapEntry));
            if (!e) continue; /* allocation failure, but continue gracefully */
            e->val = arr[i];
            e->indices = NULL; e->size = 0; e->cap = 0;
            e->next = map[h]; map[h] = e;
        }
        if (e->size >= e->cap) {
            int newCap = (e->cap == 0) ? 4 : e->cap * 2;
            int *tmp = (int*)realloc(e->indices, newCap * sizeof(int));
            if (!tmp) continue; /* allocation failure, but continue gracefully */
            e->indices = tmp; e->cap = newCap;
        }
        e->indices[e->size++] = i;
    }

    /* BFS */
    int *queue = (int*)malloc(arrSize * sizeof(int));
    if (!queue) {
        /* free map */
        for (int i = 0; i < MAP_CAP; ++i) {
            struct MapEntry *e = map[i];
            while (e) { struct MapEntry *t = e->next; free(e->indices); free(e); e = t; }
        }
        free(map);
        return -1;
    }
    int front = 0, back = 0;
    int *visited = (int*)calloc(arrSize, sizeof(int));
    if (!visited) {
        free(queue);
        /* free map */
        for (int i = 0; i < MAP_CAP; ++i) {
            struct MapEntry *e = map[i];
            while (e) { struct MapEntry *t = e->next; free(e->indices); free(e); e = t; }
        }
        free(map);
        return -1;
    }
    queue[back++] = 0;
    visited[0] = 1;
    int steps = 0;
    while (front < back) {
        int size = back - front;
        for (int i = 0; i < size; ++i) {
            int idx = queue[front++];
            if (idx == arrSize - 1) {
                /* free resources */
                free(queue);
                free(visited);
                for (int j = 0; j < MAP_CAP; ++j) {
                    struct MapEntry *e = map[j];
                    while (e) { struct MapEntry *t = e->next; free(e->indices); free(e); e = t; }
                }
                free(map);
                return steps;
            }

            /* jump to idx + 1 */
            if (idx + 1 < arrSize && !visited[idx + 1]) {
                visited[idx + 1] = 1;
                queue[back++] = idx + 1;
            }
            /* jump to idx - 1 */
            if (idx - 1 >= 0 && !visited[idx - 1]) {
                visited[idx - 1] = 1;
                queue[back++] = idx - 1;
            }
            /* jump to all indices with same value */
            int h = ((unsigned int)(arr[idx]) % MAP_CAP);
            struct MapEntry *e = map[h];
            while (e && e->val != arr[idx]) e = e->next;
            if (e) {
                for (int j = 0; j < e->size; ++j) {
                    int nextIdx = e->indices[j];
                    if (nextIdx != idx && !visited[nextIdx]) {
                        visited[nextIdx] = 1;
                        queue[back++] = nextIdx;
                    }
                }
                /* clear the list to prevent future redundant processing */
                free(e->indices);
                e->indices = NULL;
                e->size = 0;
                e->cap = 0;
            }
        }
        steps++;
    }
    /* free resources */
    free(queue);
    free(visited);
    for (int i = 0; i < MAP_CAP; ++i) {
        struct MapEntry *e = map[i];
        while (e) { struct MapEntry *t = e->next; free(e->indices); free(e); e = t; }
    }
    free(map);
    return -1;
}
