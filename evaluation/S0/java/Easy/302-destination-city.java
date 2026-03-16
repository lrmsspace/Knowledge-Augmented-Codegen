// Source: https://leetcode.com/problems/destination-city/   |   Difficulty: Easy
//
// Problem Description:
// You are given the array paths, where paths[i] = [cityAi, cityBi] means there exists a direct path going from cityAi to cityBi. Return the destination city, that is, the city without any path outgoing to another city.
//
// It is guaranteed that the graph of paths forms a line without any loop, therefore, there will be exactly one destination city.
//
// Example:
// Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
// Output: "Sao Paulo" 
// Explanation: Starting at "London" city you will reach "Sao Paulo" city which is the destination city. Your trip consist of: "London" -> "New York" -> "Lima" -> "Sao Paulo".
//
// Constraints:
// 1 <= paths.length <= 100
// 	paths[i].length == 2
// 	1 <= cityAi.length, cityBi.length <= 10
// 	cityAi != cityBi
// 	All strings consist of lowercase and uppercase English letters and the space character.
//

class Solution {
    public String destCity(List<List<String>> paths) {
        Set<String> departureCities = new HashSet<>();
        for (List<String> path : paths) {
            departureCities.add(path.get(0));
        }

        for (List<String> path : paths) {
            String destinationCity = path.get(1);
            if (!departureCities.contains(destinationCity)) {
                return destinationCity;
            }
        }

        return "";          
    }
}
