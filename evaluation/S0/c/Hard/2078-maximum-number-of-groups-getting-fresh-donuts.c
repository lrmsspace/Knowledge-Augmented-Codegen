// Source: https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/   |   Difficulty: Hard
//
// Problem Description:
// There is a donuts shop that bakes donuts in batches of batchSize. They have a rule where they must serve all of the donuts of a batch before serving any donuts of the next batch. You are given an integer batchSize and an integer array groups, where groups[i] denotes that there is a group of groups[i] customers that will visit the shop. Each customer will get exactly one donut.
//
// When a group visits the shop, all customers of the group must be served before serving any of the following groups. A group will be happy if they all get fresh donuts. That is, the first customer of the group does not receive a donut that was left over from the previous group.
//
// You can freely rearrange the ordering of the groups. Return the maximum possible number of happy groups after rearranging the groups.
//
// Example:
// Input: batchSize = 3, groups = [1,2,3,4,5,6]
// Output: 4
// Explanation: You can arrange the groups as [6,2,4,5,1,3]. Then the 1st, 2nd, 4th, and 6th groups will be happy.
//
// Constraints:
// 1 <= batchSize <= 9
// 	1 <= groups.length <= 30
// 	1 <= groups[i] <= 109
//

int maxHappyGroups(int batchSize, int* groups, int groupsSize) {
    int count[9] = {0};
    int happy = 0;
    for (int i = 0; i < groupsSize; ++i) {
        int rem = groups[i] % batchSize;
        if (rem == 0) {
            happy++;
        } else {
            count[rem]++;
        }
    }

    int memoSize = 1;
    for (int i = 1; i < batchSize; ++i) {
        memoSize *= (count[i] + 1);
    }
    int *memo = (int*)malloc(memoSize * sizeof(int));
    if (!memo) return happy; /* allocation failure, but continue gracefully */
    memset(memo, -1, memoSize * sizeof(int));

    int dfs(int *count) {
        int key = 0;
        int factor = 1;
        for (int i = 1; i < batchSize; ++i) {
            key += count[i] * factor;
            factor *= (count[i] + 1);
        }
        if (memo[key] != -1) return memo[key];

        int maxHappy = 0;
        int totalRem = 0;
        for (int i = 1; i < batchSize; ++i) {
            totalRem += i * count[i];
        }
        for (int i = 1; i < batchSize; ++i) {
            if (count[i] > 0) {
                count[i]--;
                int addHappy = ((totalRem - i) % batchSize == 0) ? 1 : 0;
                int candidate = dfs(count) + addHappy;
                if (candidate > maxHappy) {
                    maxHappy = candidate;
                }
                count[i]++;
            }
        }
        memo[key] = maxHappy;
        return maxHappy;
    }

    happy += dfs(count);
    free(memo);
    return happy;       
}
