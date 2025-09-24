// Graph Implementation with BFS, DFS, and Advanced Algorithms
// Week 7: Graph Algorithms Assignment

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>

/**
 * Graph class template supporting both directed and undirected graphs
 * Supports weighted and unweighted edges
 */
template<typename T>
class Graph {
private:
    std::unordered_map<T, std::vector<std::pair<T, int>>> adjList;
    bool isDirected;

public:
    /**
     * Constructor
     */
    explicit Graph(bool directed = false) : isDirected(directed) {}

    /**
     * Add a vertex to the graph
     */
    void addVertex(const T& vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = std::vector<std::pair<T, int>>();
        }
    }

    /**
     * Add an edge to the graph
     */
    void addEdge(const T& from, const T& to, int weight = 1) {
        addVertex(from);
        addVertex(to);
        
        adjList[from].emplace_back(to, weight);
        
        if (!isDirected) {
            adjList[to].emplace_back(from, weight);
        }
    }

    /**
     * Remove an edge from the graph
     */
    bool removeEdge(const T& from, const T& to) {
        auto it = adjList.find(from);
        if (it == adjList.end()) return false;
        
        auto& neighbors = it->second;
        auto edge = std::find_if(neighbors.begin(), neighbors.end(),
                                [&to](const std::pair<T, int>& p) { return p.first == to; });
        
        if (edge != neighbors.end()) {
            neighbors.erase(edge);
            
            if (!isDirected) {
                auto& reverseNeighbors = adjList[to];
                auto reverseEdge = std::find_if(reverseNeighbors.begin(), reverseNeighbors.end(),
                                              [&from](const std::pair<T, int>& p) { return p.first == from; });
                if (reverseEdge != reverseNeighbors.end()) {
                    reverseNeighbors.erase(reverseEdge);
                }
            }
            return true;
        }
        return false;
    }

    /**
     * Breadth-First Search (BFS)
     */
    std::vector<T> BFS(const T& start) {
        std::vector<T> visited;
        std::unordered_set<T> visitedSet;
        std::queue<T> queue;
        
        queue.push(start);
        visitedSet.insert(start);
        
        while (!queue.empty()) {
            T current = queue.front();
            queue.pop();
            visited.push_back(current);
            
            for (const auto& neighbor : adjList[current]) {
                if (visitedSet.find(neighbor.first) == visitedSet.end()) {
                    visitedSet.insert(neighbor.first);
                    queue.push(neighbor.first);
                }
            }
        }
        
        return visited;
    }

    /**
     * Depth-First Search (DFS)
     */
    std::vector<T> DFS(const T& start) {
        std::vector<T> visited;
        std::unordered_set<T> visitedSet;
        
        DFSUtil(start, visitedSet, visited);
        return visited;
    }

private:
    void DFSUtil(const T& vertex, std::unordered_set<T>& visitedSet, std::vector<T>& result) {
        visitedSet.insert(vertex);
        result.push_back(vertex);
        
        for (const auto& neighbor : adjList[vertex]) {
            if (visitedSet.find(neighbor.first) == visitedSet.end()) {
                DFSUtil(neighbor.first, visitedSet, result);
            }
        }
    }

public:
    /**
     * Check if the graph has a cycle
     */
    bool hasCycle() {
        std::unordered_set<T> visited;
        std::unordered_set<T> recStack;
        
        for (const auto& vertex : adjList) {
            if (visited.find(vertex.first) == visited.end()) {
                if (hasCycleUtil(vertex.first, T{}, visited, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool hasCycleUtil(const T& vertex, const T& parent, 
                     std::unordered_set<T>& visited, 
                     std::unordered_set<T>& recStack) {
        visited.insert(vertex);
        recStack.insert(vertex);
        
        for (const auto& neighbor : adjList[vertex]) {
            T neighborVertex = neighbor.first;
            
            if (visited.find(neighborVertex) == visited.end()) {
                if (hasCycleUtil(neighborVertex, vertex, visited, recStack)) {
                    return true;
                }
            } else if (!isDirected && neighborVertex == parent) {
                continue; // Skip parent in undirected graph
            } else if (recStack.find(neighborVertex) != recStack.end()) {
                return true; // Back edge found
            }
        }
        
        recStack.erase(vertex);
        return false;
    }

public:
    /**
     * Get all vertices in the graph
     */
    std::vector<T> getAllVertices() const {
        std::vector<T> vertices;
        for (const auto& vertex : adjList) {
            vertices.push_back(vertex.first);
        }
        return vertices;
    }

    /**
     * Get neighbors of a vertex
     */
    std::vector<std::pair<T, int>> getNeighbors(const T& vertex) const {
        auto it = adjList.find(vertex);
        if (it != adjList.end()) {
            return it->second;
        }
        return {};
    }

    /**
     * Check if there's an edge between two vertices
     */
    bool hasEdge(const T& from, const T& to) const {
        auto it = adjList.find(from);
        if (it == adjList.end()) return false;
        
        for (const auto& neighbor : it->second) {
            if (neighbor.first == to) return true;
        }
        return false;
    }

    /**
     * Get the number of vertices
     */
    size_t getVertexCount() const {
        return adjList.size();
    }

    /**
     * Get the number of edges
     */
    size_t getEdgeCount() const {
        size_t count = 0;
        for (const auto& vertex : adjList) {
            count += vertex.second.size();
        }
        return isDirected ? count : count / 2;
    }

    // TODO: Students should implement these advanced algorithms:
    // - Dijkstra's shortest path algorithm
    // - A* pathfinding algorithm  
    // - Minimum spanning tree (Kruskal's or Prim's)
    // - Topological sorting for directed acyclic graphs
    // - Strongly connected components
    // - Graph connectivity checking
    // - Shortest path between two specific vertices
    // - Graph visualization/printing methods
};

// Students can add a main function here for testing their implementations
// int main() {
//     Graph<int> g(false); // Undirected graph
//     g.addEdge(1, 2);
//     g.addEdge(2, 3);
//     g.addEdge(3, 4);
//     
//     auto bfs = g.BFS(1);
//     std::cout << "BFS: ";
//     for (const auto& vertex : bfs) {
//         std::cout << vertex << " ";
//     }
//     std::cout << std::endl;
//     
//     return 0;
// }