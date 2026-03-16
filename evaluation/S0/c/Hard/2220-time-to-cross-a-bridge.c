// Source: https://leetcode.com/problems/time-to-cross-a-bridge/   |   Difficulty: Hard
//
// Problem Description:
// There are k workers who want to move n boxes from the right (old) warehouse to the left (new) warehouse. You are given the two integers n and k, and a 2D integer array time of size k x 4 where time[i] = [righti, picki, lefti, puti].
//
// The warehouses are separated by a river and connected by a bridge. Initially, all k workers are waiting on the left side of the bridge. To move the boxes, the ith worker can do the following:
//
//
// 	Cross the bridge to the right side in righti minutes.
// 	Pick a box from the right warehouse in picki minutes.
// 	Cross the bridge to the left side in lefti minutes.
// 	Put the box into the left warehouse in puti minutes.
//
//
// The ith worker is less efficient than the jth worker if either condition is met:
//
//
// 	lefti + righti > leftj + rightj
// 	lefti + righti == leftj + rightj and i > j
//
//
// The following rules regulate the movement of the workers through the bridge:
//
//
// 	Only one worker can use the bridge at a time.
// 	When the bridge is unused prioritize the least efficient worker (who have picked up the box) on the right side to cross. If not, prioritize the least efficient worker on the left side to cross.
// 	If enough workers have already been dispatched from the left side to pick up all the remaining boxes, no more workers will be sent from the left side.
//
//
// Return the elapsed minutes at which the last box reaches the left side of the bridge.
//
// Example:
// Input: n = 1, k = 3, time = [[1,1,2,1],[1,1,3,1],[1,1,4,1]]
//
// Output: 6
//
// Explanation:
//
//
// From 0 to 1 minutes: worker 2 crosses the bridge to the right.
// From 1 to 2 minutes: worker 2 picks up a box from the right warehouse.
// From 2 to 6 minutes: worker 2 crosses the bridge to the left.
// From 6 to 7 minutes: worker 2 puts a box at the left warehouse.
// The whole process ends after 7 minutes. We return 6 because the problem asks for the instance of time at which the last worker reaches the left side of the bridge.
//
// Constraints:
// 1 <= n, k <= 104
// 	time.length == k
// 	time[i].length == 4
// 	1 <= lefti, picki, righti, puti <= 1000
//

int findCrossingTime(int n, int k, int** time, int timeSize, int* timeColSize) {
    typedef struct {
        int idx;
        int cross;
        int pick;
        int back;
        int put;
        int eff; /* efficiency = cross + back */
    } Worker;

    typedef struct {
        Worker *data;
        int size;
        int cap;
    } Heap;

    #define HEAP_INIT_CAP 16

    static int cmpLeft(const void *a, const void *b) {
        const Worker *wa = (const Worker*)a;
        const Worker *wb = (const Worker*)b;
        if (wa->eff != wb->eff) return wb->eff - wa->eff;
        return wb->idx - wa->idx;
    }

    static int cmpRight(const void *a, const void *b) {
        const Worker *wa = (const Worker*)a;
        const Worker *wb = (const Worker*)b;
        if (wa->eff != wb->eff) return wb->eff - wa->eff;
        return wb->idx - wa->idx;
    }

    static void heapPush(Heap *heap, Worker w, int (*cmp)(const void*, const void*)) {
        if (heap->size >= heap->cap) {
            int newCap = (heap->cap == 0) ? HEAP_INIT_CAP : heap->cap * 2;
            Worker *tmp = (Worker*)realloc(heap->data, newCap * sizeof(Worker));
            if (!tmp) return; /* allocation failure, but continue gracefully */
            heap->data = tmp; heap->cap = newCap;
        }
        heap->data[heap->size++] = w;
        int i = heap->size - 1;
        while (i > 0) {
            int p = (i - 1) / 2;
            if (cmp(&heap->data[i], &heap->data[p]) <= 0) break;
            Worker t = heap->data[i];
            heap->data[i] = heap->data[p];
            heap->data[p] = t;
            i = p;
        }
    }

    static Worker heapPop(Heap *heap, int (*cmp)(const void*, const void*)) {
        Worker ret = heap->data[0];
        heap->data[0] = heap->data[--heap->size];
        int i = 0;
        while (1) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int largest = i;
            if (l < heap->size && cmp(&heap->data[l], &heap->data[largest]) > 0) largest = l;
            if (r < heap->size && cmp(&heap->data[r], &heap->data[largest]) > 0) largest = r;
            if (largest == i) break;
            Worker t = heap->data[i];
            heap->data[i] = heap->data[largest];
            heap->data[largest] = t;
            i = largest;
        }
        return ret;
    }
    Heap leftHeap = {NULL, 0, 0};
    Heap rightHeap = {NULL, 0, 0};
    for (int i = 0; i < k; ++i) {
        Worker w = {i, time[i][0], time[i][1], time[i][2], time[i][3], time[i][0] + time[i][2]};
        heapPush(&leftHeap, w, cmpLeft);
    }
    int currTime = 0;
    int boxesLeft = n;
    typedef struct {
        Worker worker;
        int availableTime;
    } BusyWorker;
    BusyWorker *busyWorkers = (BusyWorker*)malloc(sizeof(BusyWorker) * k * 2);
    int busyCount = 0;
    while (boxesLeft > 0 || rightHeap.size > 0) {
        for (int i = 0; i < busyCount; ) {
            if (busyWorkers[i].availableTime <= currTime) {
                if (busyWorkers[i].worker.idx >= 0) {
                    /* finished crossing to right */
                    heapPush(&rightHeap, busyWorkers[i].worker, cmpRight);
                } else {
                    /* finished crossing to left */
                    heapPush(&leftHeap, busyWorkers[i].worker, cmpLeft);
                }
                busyWorkers[i] = busyWorkers[--busyCount];
            } else {
                ++i;
            }
        }
        if (rightHeap.size > 0) {
            Worker w = heapPop(&rightHeap, cmpRight);
            currTime += w.back;
            BusyWorker bw = {w, currTime + w.put};
            busyWorkers[busyCount++] = bw;
        } else if (boxesLeft > 0 && leftHeap.size > 0) {
            Worker w = heapPop(&leftHeap, cmpLeft);
            currTime += w.cross;
            BusyWorker bw = {w, currTime + w.pick};
            busyWorkers[busyCount++] = bw;
            boxesLeft--;
        } else {
            int nextTime = -1;
            for (int i = 0; i < busyCount; ++i) {
                if (nextTime == -1 || busyWorkers[i].availableTime < nextTime) {
                    nextTime = busyWorkers[i].availableTime;
                }
            }
            currTime = nextTime;
        }
    }
    free(busyWorkers);
    free(leftHeap.data);
    free(rightHeap.data);
    return currTime;
}
