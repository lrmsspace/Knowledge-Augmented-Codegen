// Source: https://leetcode.com/problems/process-restricted-friend-requests/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n indicating the number of people in a network. Each person is labeled from 0 to n - 1.
//
// You are also given a 0-indexed 2D integer array restrictions, where restrictions[i] = [xi, yi] means that person xi and person yi cannot become friends, either directly or indirectly through other people.
//
// Initially, no one is friends with each other. You are given a list of friend requests as a 0-indexed 2D integer array requests, where requests[j] = [uj, vj] is a friend request between person uj and person vj.
//
// A friend request is successful if uj and vj can be friends. Each friend request is processed in the given order (i.e., requests[j] occurs before requests[j + 1]), and upon a successful request, uj and vj become direct friends for all future friend requests.
//
// Return a boolean array result, where each result[j] is true if the jth friend request is successful or false if it is not.
//
// Note: If uj and vj are already direct friends, the request is still successful.
//
// Example:
// Input: n = 3, restrictions = [[0,1]], requests = [[0,2],[2,1]]
// Output: [true,false]
// Explanation:
// Request 0: Person 0 and person 2 can be friends, so they become direct friends. 
// Request 1: Person 2 and person 1 cannot be friends since person 0 and person 1 would be indirect friends (1--2--0).
//
// Constraints:
// 2 <= n <= 1000
// 	0 <= restrictions.length <= 1000
// 	restrictions[i].length == 2
// 	0 <= xi, yi <= n - 1
// 	xi != yi
// 	1 <= requests.length <= 1000
// 	requests[j].length == 2
// 	0 <= uj, vj <= n - 1
// 	uj != vj
//

class Solution {
    public boolean[] friendRequests(int n, int[][] restrictions, int[][] requests) {
        UnionFind uf = new UnionFind(n);
        boolean[] result = new boolean[requests.length];

        for (int i = 0; i < requests.length; i++) {
            int u = requests[i][0];
            int v = requests[i][1];
            int pu = uf.find(u);
            int pv = uf.find(v);

            boolean canBeFriends = true;
            for (int[] restriction : restrictions) {
                int x = restriction[0];
                int y = restriction[1];
                int px = uf.find(x);
                int py = uf.find(y);

                if ((pu == px && pv == py) || (pu == py && pv == px)) {
                    canBeFriends = false;
                    break;
                }
            }

            if (canBeFriends) {
                uf.union(u, v);
                result[i] = true;
            } else {
                result[i] = false;
            }
        }

        return result;          
    }
}
