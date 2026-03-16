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

class Solution {

    public int waysToBuildRooms(int[] prevRoom) {

        
        int n = prevRoom.length;
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tree.add(new ArrayList<>());
        }
        for (int i = 1; i < n; i++) {
            tree.get(prevRoom[i]).add(i);
        }

        long mod = (long) 1e9 + 7;
        long[] fact = new long[n + 1];
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }

        long[] size = new long[n];
        Arrays.fill(size, 1);

        long[] res = new long[1];
        res[0] = 1;

        dfs(tree, 0, size, fact, mod, res);

        return (int) res[0];
    }

}
