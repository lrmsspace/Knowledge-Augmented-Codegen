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

class Solution {
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        vector<int> count(batchSize, 0);
        int happyGroups = 0;

        // Count groups based on their size modulo batchSize
        for (int group : groups) {
            int mod = group % batchSize;
            if (mod == 0) {
                happyGroups++;  // These groups are always happy
            } else {
                count[mod]++;
            }
        }

        // Use memoization to store intermediate results
        unordered_map<string, int> memo;

        function<int(int, vector<int>&)> dfs = [&](int remainder, vector<int>& count) {
            string key = to_string(remainder) + "#";
            for (int c : count) key += to_string(c) + ",";
            if (memo.count(key)) return memo[key];

            int maxHappy = 0;
            for (int i = 1; i < batchSize; ++i) {
                if (count[i] > 0) {
                    count[i]--;
                    int newRemainder = (remainder + i) % batchSize;
                    int additionalHappy = (newRemainder == 0) ? 1 : 0;
                    maxHappy = max(maxHappy, additionalHappy + dfs(newRemainder, count));
                    count[i]++;
                }
            }

            memo[key] = maxHappy;
            return maxHappy;
        };

        happyGroups += dfs(0, count);
        return happyGroups;         
    }
};
