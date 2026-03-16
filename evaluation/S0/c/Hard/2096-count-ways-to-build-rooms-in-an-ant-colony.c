// Source: https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/   |   Difficulty: Hard
//
// Problem Description:
// You are an ant tasked with adding n new rooms numbered 0 to n-1 to your colony. You are given the expansion plan as a 0-indexed integer array of length n, prevRoom, where prevRoom[i] indicates that you must build room prevRoom[i] before building room i, and these two rooms must be connected directly. Room 0 is already built, so prevRoom[0] = -1. The expansion plan is given such that once all the rooms are built, every room will be reachable from room 0.
//
// You can only build one room at a time, and you can travel freely between rooms you have already built only if they are connected. You can choose to build any room as long as its previous room is already built.
//
// Return the number of different orders you can build all the rooms in. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: prevRoom = [-1,0,1]
// Output: 1
// Explanation: There is only one way to build the additional rooms: 0 → 1 → 2
//
// Constraints:
// n == prevRoom.length
// 	2 <= n <= 105
// 	prevRoom[0] == -1
// 	0 <= prevRoom[i] < n for all 1 <= i < n
// 	Every room is reachable from room 0 once all the rooms are built.
//

int waysToBuildRooms(int* prevRoom, int prevRoomSize){


    const int MOD = 1000000007;

    /* build adjacency list */
    int n = prevRoomSize;
    int *head = (int*)calloc(n, sizeof(int));
    int *next = (int*)calloc(n - 1, sizeof(int));
    int *to = (int*)calloc(n - 1, sizeof(int));
    if (!head || !next || !to) {
        free(head); free(next); free(to);
        return 0; /* allocation failure */
    }
    memset(head, -1, n * sizeof(int));
    for (int i = 1; i < n; ++i) {
        to[i - 1] = i;
        next[i - 1] = head[prevRoom[i]];
        head[prevRoom[i]] = i - 1;
    }

    /* precompute factorials and inverses */
    long long *fact = (long long*)calloc(n + 1, sizeof(long long));
    long long *invFact = (long long*)calloc(n + 1, sizeof(long long));
    if (!fact || !invFact) {
        free(head); free(next); free(to);
        free(fact); free(invFact);
        return 0; /* allocation failure */
    }
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = (fact[i - 1] * i) % MOD;
    invFact[n] = 1;
    long long base = fact[n];
    long long exp = MOD - 2;
    while (exp) {
        if (exp & 1) invFact[n] = (invFact[n] * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    for (int i = n - 1; i >= 0; --i)
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;

    /* DFS to compute sizes and ways */
    int *size = (int*)calloc(n, sizeof(int));
    if (!size) {
        free(head); free(next); free(to);
        free(fact); free(invFact);
        return 0; /* allocation failure */
    }

    long long dfs(int u) {
        long long ways = 1;
        size[u] = 1;
        for (int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            ways = (ways * dfs(v)) % MOD;
            ways = (ways * invFact[size[v]]) % MOD;
            size[u] += size[v];
        }
        ways = (ways * fact[size[u] - 1]) % MOD;
        return ways;
    }
    long long result = dfs(0);
    /* cleanup */
    free(head); free(next); free(to);
    free(fact); free(invFact);
    free(size);
    return (int)result;
}
