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

char* destCity(char*** paths, int pathsSize, int* pathsColSize) {
    // Create a hash set to store all starting cities
    #define MAX_CITIES 200
    char* startCities[MAX_CITIES];
    int startCount = 0;

    // Populate the hash set with starting cities
    for (int i = 0; i < pathsSize; i++) {
        startCities[startCount++] = paths[i][0];
    }

    // Check each destination city to see if it is not in the starting cities
    for (int i = 0; i < pathsSize; i++) {
        char* destCity = paths[i][1];
        int found = 0;

        for (int j = 0; j < startCount; j++) {
            if (strcmp(destCity, startCities[j]) == 0) {
                found = 1;
                break;
            }
        }

        // If the destination city is not found in starting cities, return it
        if (!found) {
            return destCity;
        }
    }

    // In case no destination city is found (should not happen as per problem constraints)
    return NULL;        
}
