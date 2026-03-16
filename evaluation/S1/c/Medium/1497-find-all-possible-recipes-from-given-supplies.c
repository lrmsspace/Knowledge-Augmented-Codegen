// Source: https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/   |   Difficulty: Medium
//
// Problem Description:
// You have information about n different recipes. You are given a string array recipes and a 2D string array ingredients. The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients from ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may contain a string that is in recipes.
//
// You are also given a string array supplies containing all the ingredients that you initially have, and you have an infinite supply of all of them.
//
// Return a list of all the recipes that you can create. You may return the answer in any order.
//
// Note that two recipes may contain each other in their ingredients.
//
// Example:
// Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
// Output: ["bread"]
// Explanation:
// We can create "bread" since we have the ingredients "yeast" and "flour".
//
// Constraints:
// n == recipes.length == ingredients.length
// 	1 <= n <= 100
// 	1 <= ingredients[i].length, supplies.length <= 100
// 	1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
// 	recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
// 	All the values of recipes and supplies combined are unique.
// 	Each ingredients[i] does not contain any duplicate values.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Topological Sorting (graph, array, dfs, topo)
//   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
//   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
//   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
//   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findAllRecipes(char** recipes, int recipesSize, char*** ingredients, int ingredientsSize, int* ingredientsColSize, char** supplies, int suppliesSize, int* returnSize) {
    // Topological Sort using Kahn's Algorithm

    // Step 1: Create a mapping from ingredient to recipes that require it
    #define MAX_INGREDIENTS 10000
    #define MAX_RECIPES 100
    typedef struct {
        char* recipe;
        int indegree;
    } RecipeNode;

    RecipeNode recipeNodes[MAX_RECIPES];
    int recipeCount = 0;

    // Hash map for ingredient to list of recipes
    typedef struct {
        char* ingredient;
        RecipeNode* recipes[MAX_RECIPES];
        int recipeCount;
    } IngredientMap;

    IngredientMap ingredientMap[MAX_INGREDIENTS];
    int ingredientMapSize = 0;

    // Function to find or create an ingredient map entry
    IngredientMap* getIngredientMapEntry(char* ingredient) {
        for (int i = 0; i < ingredientMapSize; i++) {
            if (strcmp(ingredientMap[i].ingredient, ingredient) == 0) {
                return &ingredientMap[i];
            }
        }
        ingredientMap[ingredientMapSize].ingredient = ingredient;
        ingredientMap[ingredientMapSize].recipeCount = 0;
        return &ingredientMap[ingredientMapSize++];
    }

    // Step 2: Initialize recipe nodes and build the graph
    for (int i = 0; i < recipesSize; i++) {
        recipeNodes[i].recipe = recipes[i];
        recipeNodes[i].indegree = ingredientsColSize[i];

        for (int j = 0; j < ingredientsColSize[i]; j++) {
            IngredientMap* entry = getIngredientMapEntry(ingredients[i][j]);
            entry->recipes[entry->recipeCount++] = &recipeNodes[i];
        }
    }
    recipeCount = recipesSize;

    // Step 3: Initialize the queue with available supplies
    RecipeNode* queue[MAX_RECIPES];
    int front = 0, back = 0;
    for (int i = 0; i < suppliesSize; i++) {
        IngredientMap* entry = getIngredientMapEntry(supplies[i]);
        for (int j = 0; j < entry->recipeCount; j++) {
            RecipeNode* recipeNode = entry->recipes[j];
            recipeNode->indegree--;
            if (recipeNode->indegree == 0) {
                queue[back++] = recipeNode;
            }
        }
    }
    // Step 4: Process the queue
    char** result = (char**)malloc(MAX_RECIPES * sizeof(char*));
    int resultCount = 0;
    while (front < back) {
        RecipeNode* current = queue[front++];
        result[resultCount++] = current->recipe;

        // For each ingredient in the current recipe, reduce indegree of dependent recipes
        IngredientMap* entry = getIngredientMapEntry(current->recipe);
        for (int i = 0; i < entry->recipeCount; i++) {
            RecipeNode* dependentRecipe = entry->recipes[i];
            dependentRecipe->indegree--;
            if (dependentRecipe->indegree == 0) {
                queue[back++] = dependentRecipe;
            }
        }
    }
    *returnSize = resultCount;
    return result;
}
