// Week 7: Graph Algorithms - Test Suite
// Students: Implement the advanced graph algorithms in graph.cpp

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "../../assignments/week07-graphs/graph.cpp"

// Test fixture for graph algorithms
class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create an undirected graph for testing
        undirectedGraph = std::make_unique<Graph<int>>(false);
        undirectedGraph->addEdge(1, 2);
        undirectedGraph->addEdge(2, 3);
        undirectedGraph->addEdge(3, 4);
        undirectedGraph->addEdge(4, 5);
        undirectedGraph->addEdge(2, 6);
        
        // Create a directed graph for testing
        directedGraph = std::make_unique<Graph<int>>(true);
        directedGraph->addEdge(1, 2);
        directedGraph->addEdge(2, 3);
        directedGraph->addEdge(3, 1); // Creates a cycle
        directedGraph->addEdge(3, 4);
    }

    std::unique_ptr<Graph<int>> undirectedGraph;
    std::unique_ptr<Graph<int>> directedGraph;
};

// Basic Graph Construction Tests
TEST_F(GraphTest, AddVertexAndEdge) {
    Graph<char> g;
    g.addVertex('A');
    g.addEdge('A', 'B');
    
    EXPECT_TRUE(g.hasEdge('A', 'B'));
    EXPECT_EQ(g.getVertexCount(), 2);
    EXPECT_EQ(g.getEdgeCount(), 1);
}

TEST_F(GraphTest, RemoveEdge) {
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    
    EXPECT_TRUE(g.hasEdge(1, 2));
    EXPECT_TRUE(g.removeEdge(1, 2));
    EXPECT_FALSE(g.hasEdge(1, 2));
    EXPECT_TRUE(g.hasEdge(1, 3));
}

// BFS Tests
TEST_F(GraphTest, BFSTraversal) {
    auto result = undirectedGraph->BFS(1);
    
    // BFS should visit all connected vertices
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], 1); // Should start with the starting vertex
    
    // Check that all vertices are visited
    std::unordered_set<int> visited(result.begin(), result.end());
    for (int i = 1; i <= 6; i++) {
        EXPECT_TRUE(visited.find(i) != visited.end());
    }
}

TEST_F(GraphTest, BFSStartFromDifferentVertex) {
    auto result = undirectedGraph->BFS(3);
    
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], 3); // Should start with vertex 3
}

// DFS Tests
TEST_F(GraphTest, DFSTraversal) {
    auto result = undirectedGraph->DFS(1);
    
    // DFS should visit all connected vertices
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], 1); // Should start with the starting vertex
    
    // Check that all vertices are visited
    std::unordered_set<int> visited(result.begin(), result.end());
    for (int i = 1; i <= 6; i++) {
        EXPECT_TRUE(visited.find(i) != visited.end());
    }
}

TEST_F(GraphTest, DFSStartFromDifferentVertex) {
    auto result = undirectedGraph->DFS(4);
    
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], 4); // Should start with vertex 4
}

// Cycle Detection Tests
TEST_F(GraphTest, CycleDetectionUndirected) {
    Graph<int> acyclic(false);
    acyclic.addEdge(1, 2);
    acyclic.addEdge(2, 3);
    acyclic.addEdge(3, 4);
    
    EXPECT_FALSE(acyclic.hasCycle());
    
    // Add an edge to create a cycle
    acyclic.addEdge(4, 1);
    EXPECT_TRUE(acyclic.hasCycle());
}

TEST_F(GraphTest, CycleDetectionDirected) {
    Graph<int> acyclic(true);
    acyclic.addEdge(1, 2);
    acyclic.addEdge(2, 3);
    acyclic.addEdge(3, 4);
    
    EXPECT_FALSE(acyclic.hasCycle());
    
    // Our directed graph has a cycle (1->2->3->1)
    EXPECT_TRUE(directedGraph->hasCycle());
}

// Edge and Vertex Queries
TEST_F(GraphTest, GetNeighbors) {
    auto neighbors = undirectedGraph->getNeighbors(2);
    
    EXPECT_EQ(neighbors.size(), 3); // 2 is connected to 1, 3, and 6
    
    // Extract just the vertex values
    std::vector<int> neighborVertices;
    for (const auto& neighbor : neighbors) {
        neighborVertices.push_back(neighbor.first);
    }
    
    EXPECT_TRUE(std::find(neighborVertices.begin(), neighborVertices.end(), 1) != neighborVertices.end());
    EXPECT_TRUE(std::find(neighborVertices.begin(), neighborVertices.end(), 3) != neighborVertices.end());
    EXPECT_TRUE(std::find(neighborVertices.begin(), neighborVertices.end(), 6) != neighborVertices.end());
}

TEST_F(GraphTest, GetAllVertices) {
    auto vertices = undirectedGraph->getAllVertices();
    
    EXPECT_EQ(vertices.size(), 6);
    
    // Check that all expected vertices are present
    std::unordered_set<int> vertexSet(vertices.begin(), vertices.end());
    for (int i = 1; i <= 6; i++) {
        EXPECT_TRUE(vertexSet.find(i) != vertexSet.end());
    }
}

TEST_F(GraphTest, EdgeCount) {
    EXPECT_EQ(undirectedGraph->getEdgeCount(), 5); // 5 edges in undirected graph
    EXPECT_EQ(directedGraph->getEdgeCount(), 4);   // 4 edges in directed graph
}

// Weighted Graph Tests
TEST_F(GraphTest, WeightedEdges) {
    Graph<char> weighted(true);
    weighted.addEdge('A', 'B', 10);
    weighted.addEdge('B', 'C', 20);
    
    auto neighbors = weighted.getNeighbors('A');
    EXPECT_EQ(neighbors.size(), 1);
    EXPECT_EQ(neighbors[0].first, 'B');
    EXPECT_EQ(neighbors[0].second, 10); // Weight should be 10
}

// Disconnected Graph Tests
TEST_F(GraphTest, DisconnectedComponents) {
    Graph<int> disconnected(false);
    disconnected.addEdge(1, 2);
    disconnected.addEdge(3, 4);
    
    // BFS from 1 should only reach 1 and 2
    auto bfsResult = disconnected.BFS(1);
    EXPECT_EQ(bfsResult.size(), 2);
    
    // DFS from 3 should only reach 3 and 4
    auto dfsResult = disconnected.DFS(3);
    EXPECT_EQ(dfsResult.size(), 2);
}

// Empty Graph Tests
TEST_F(GraphTest, EmptyGraph) {
    Graph<int> empty;
    
    EXPECT_EQ(empty.getVertexCount(), 0);
    EXPECT_EQ(empty.getEdgeCount(), 0);
    EXPECT_FALSE(empty.hasCycle());
}

// Single Vertex Tests
TEST_F(GraphTest, SingleVertex) {
    Graph<int> single;
    single.addVertex(1);
    
    EXPECT_EQ(single.getVertexCount(), 1);
    EXPECT_EQ(single.getEdgeCount(), 0);
    EXPECT_FALSE(single.hasCycle());
    
    auto bfs = single.BFS(1);
    EXPECT_EQ(bfs.size(), 1);
    EXPECT_EQ(bfs[0], 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}