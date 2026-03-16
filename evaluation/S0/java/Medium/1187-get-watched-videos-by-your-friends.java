// Source: https://leetcode.com/problems/get-watched-videos-by-your-friends/   |   Difficulty: Medium
//
// Problem Description:
// There are n people, each person has a unique id between 0 and n-1. Given the arrays watchedVideos and friends, where watchedVideos[i] and friends[i] contain the list of watched videos and the list of friends respectively for the person with id = i.
//
// Level 1 of videos are all watched videos by your friends, level 2 of videos are all watched videos by the friends of your friends and so on. In general, the level k of videos are all watched videos by people with the shortest path exactly equal to k with you. Given your id and the level of videos, return the list of videos ordered by their frequencies (increasing). For videos with the same frequency order them alphabetically from least to greatest.
//
// Example:
// Input: watchedVideos = [["A","B"],["C"],["B","C"],["D"]], friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
// Output: ["B","C"] 
// Explanation: 
// You have id = 0 (green color in the figure) and your friends are (yellow color in the figure):
// Person with id = 1 -> watchedVideos = ["C"] 
// Person with id = 2 -> watchedVideos = ["B","C"] 
// The frequencies of watchedVideos by your friends are: 
// B -> 1 
// C -> 2
//
// Constraints:
// n == watchedVideos.length == friends.length
// 	2 <= n <= 100
// 	1 <= watchedVideos[i].length <= 100
// 	1 <= watchedVideos[i][j].length <= 8
// 	0 <= friends[i].length < n
// 	0 <= friends[i][j] < n
// 	0 <= id < n
// 	1 <= level < n
// 	if friends[i] contains j, then friends[j] contains i
//

class Solution {
    public List<String> watchedVideosByFriends(List<List<String>> watchedVideos, int[][] friends, int id, int level) {
        int n = watchedVideos.size();
        boolean[] visited = new boolean[n];
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(id);
        visited[id] = true;
        int currentLevel = 0;

        while (!queue.isEmpty() && currentLevel < level) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int person = queue.poll();
                for (int friend : friends[person]) {
                    if (!visited[friend]) {
                        visited[friend] = true;
                        queue.offer(friend);
                    }
                }
            }
            currentLevel++;
        }

        Map<String, Integer> frequencyMap = new HashMap<>();
        while (!queue.isEmpty()) {
            int friend = queue.poll();
            for (String video : watchedVideos.get(friend)) {
                frequencyMap.put(video, frequencyMap.getOrDefault(video, 0) + 1);
            }
        }

        List<String> result = new ArrayList<>(frequencyMap.keySet());
        Collections.sort(result, (a, b) -> {
            int freqA = frequencyMap.get(a);
            int freqB = frequencyMap.get(b);
            if (freqA == freqB) {
                return a.compareTo(b);
            }
            return Integer.compare(freqA, freqB);
        });

        return result;          
    }
}
