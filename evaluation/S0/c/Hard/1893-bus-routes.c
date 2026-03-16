// Source: https://leetcode.com/problems/bus-routes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.
//
//
// 	For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
//
//
// You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.
//
// Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.
//
// Example:
// Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
// Output: 2
// Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
//
// Constraints:
// 1 <= routes.length <= 500.
// 	1 <= routes[i].length <= 105
// 	All the values of routes[i] are unique.
// 	sum(routes[i].length) <= 105
// 	0 <= routes[i][j] < 106
// 	0 <= source, target < 106
//

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    if (source == target) return 0;

    /* Build stop -> buses map */
    #define MAX_STOP 1000000
    int *stopToBuses[MAX_STOP];
    int stopBusCounts[MAX_STOP];
    memset(stopToBuses, 0, sizeof(stopToBuses));
    memset(stopBusCounts, 0, sizeof(stopBusCounts));

    for (int bus = 0; bus < routesSize; ++bus) {
        for (int j = 0; j < routesColSize[bus]; ++j) {
            int stop = routes[bus][j];
            int count = stopBusCounts[stop]++;
            stopToBuses[stop] = (int*)realloc(stopToBuses[stop], count + 1 * sizeof(int));
            stopToBuses[stop][count] = bus;
        }
    }

    /* BFS */
    int visitedBuses[routesSize];
    memset(visitedBuses, 0, sizeof(visitedBuses));
    int queue[MAX_STOP];
    int front = 0, back = 0;
    queue[back++] = source;
    int busesTaken = 0;

    while (front < back) {
        int levelSize = back - front;
        ++busesTaken;
        for (int i = 0; i < levelSize; ++i) {
            int currStop = queue[front++];
            int *buses = stopToBuses[currStop];
            int busCount = stopBusCounts[currStop];
            for (int j = 0; j < busCount; ++j) {
                int bus = buses[j];
                if (visitedBuses[bus]) continue;
                visitedBuses[bus] = 1;
                for (int k = 0; k < routesColSize[bus]; ++k) {
                    int nextStop = routes[bus][k];
                    if (nextStop == target) {
                        /* Free allocated memory */
                        for (int s = 0; s < MAX_STOP; ++s) {
                            free(stopToBuses[s]);
                        }
                        return busesTaken;
                    }
                    queue[back++] = nextStop;
                }
            }
        }
    }

    /* Free allocated memory */
    for (int s = 0; s < MAX_STOP; ++s) {
        free(stopToBuses[s]);
    }  
    return -1;     
}
