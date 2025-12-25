#include <iostream>
#include<queue>
#include<stack>
#include<vector>
#include <climits>
#include <utility>

using P = std::pair<int, int>;

using namespace std;

const int GRAPH_MAX = 50;

// Directed Weighted Graph based on the Given Class Sigunatures
template<class VertexType>
class Graph
{
    int numOfVertices;               ///Current Number of Vertices
    VertexType vertices[GRAPH_MAX];  ///Max Number of Vertices is 50
    int edges[GRAPH_MAX][GRAPH_MAX];              ///Adjacency Matrix
    bool marks[GRAPH_MAX];     /// track visited/unvisited vertices

public:
    explicit Graph(): numOfVertices(0) {}

    // ================================ Basic Helpers ================================ //

    void makeEmpty();
    bool isEmpty();
    bool isFull();

    // ================================ Main Functions ================================ //

    // ----- Adds a Vertex to the Graph ----- //
    void addVertex (const VertexType& vertex);

    // ----- Adds an Edge in the Adjacency Matrix (edges) ----- //
    void addEdge(VertexType fromVertex,VertexType toVertex, int Weight );

    // ----- This is NOT shortest path - This is NOT multi-edge traversal ----- //
    // ----- This is only one edge lookup in the adjacency matrix ----- //
    int getPathWeight (VertexType fromVertex,VertexType toVertex);

    // ----- Convert a Vertex value to Index ----- //
    int getIndex (const VertexType& vertex);

    // ----- Get the Neighbors of the Vertex ----- //
    void getAdjVertices (VertexType vertex, queue<VertexType> & VertexQ);

    // ================================ Marking System ================================ //

    // ----- Reset all vertices as unvisited ----- //
    void clearMarks ();

    // ----- Mark vertex as visited ----- //
    void markVertex(VertexType vertex);

    // ----- Check if vertex v was visited ----- //
    bool isMarked (VertexType vertex);

    // ================================ Graph Traversing Functions ================================ //

    ///Standard Algorithms ( only one from 1 , 2 ) and Implement 3
    ////1.
    // Same Logic as BFS but using the "Stack" (LIFO) - Deep first
    void depthFirstSearch (const VertexType& startVertex, const VertexType& endVertex);   /// Stack , Queue
    ///2.
    // Same Logic as DFS but using the "Queue" (FIFO) - Level first
    void breadthFirstSearch (const VertexType& startVertex, const VertexType& endVertex);  /// 2 Queue

    ///3. Print All Shortest Path /// Dijkstra
    void dijkstra (const VertexType& startVertex); /// Pirority Queue , Adjacent Queue

};

template<class VertexType>
void Graph<VertexType>::makeEmpty()
{
    // 1. Reset vertex count
    numOfVertices = 0;

    // 2. Clear adjacency matrix
    for(int i{}; i < GRAPH_MAX; i++)
    {
        for(int j{}; j < GRAPH_MAX; j++) edges[i][j] = 0;
    }

    // 3. Clear marks
    for(int i{}; i < GRAPH_MAX; i++) marks[i] = false;
}

template<class VertexType>
bool Graph<VertexType>::isEmpty()
{
    return numOfVertices == 0;
}

template<class VertexType>
bool Graph<VertexType>::isFull()
{
    return numOfVertices == GRAPH_MAX;
}

template<class VertexType>
void Graph<VertexType>::addVertex (const VertexType& vertex)
{
    // Graph must NOT be full
    if (isFull()) return;

    // 1. Store the vertex value
    vertices[numOfVertices] = vertex; // New vertex goes at index numOfVertices

    // 2. Initialize its connections with all other vertices - Since this is a new vertex, it has NO edges yet
    // Initialize adjacency matrix entries
    for (int i = 0; i <= numOfVertices; i++)
    {
        edges[numOfVertices][i] = 0;
        edges[i][numOfVertices] = 0;
    }

    // 3. Initialize its mark status
    marks[numOfVertices] = false;

    // 4. Increase the vertex count
    numOfVertices++;
}

template<class VertexType>
void Graph<VertexType>::addEdge(VertexType fromVertex,VertexType toVertex, int weight )
{
    // 1. Find indices of both vertices
    int fromIndex = getIndex(fromVertex);
    int toIndex = getIndex(toVertex);

    // 2. Validate vertices exist
    // If either vertex does not exist then we cannot add an edge.
    if(fromIndex == -1 || toIndex == -1) return;

    // 3. Insert weight into adjacency matrix - Directed Graph
    edges[fromIndex][toIndex] = weight;
}

template<class VertexType>
int Graph<VertexType>::getPathWeight (VertexType fromVertex,VertexType toVertex)
{
    // Only one edge lookup in the adjacency matrix

    // 1. Find indices of both vertices
    int fromIndex = getIndex(fromVertex);
    int toIndex = getIndex(toVertex);

    // 2. Validate vertices exist
    if(fromIndex == -1 || toIndex == -1) return -1;

    // 3. Return the weight value
    return  edges[fromIndex][toIndex];
}

template<class VertexType>
int Graph<VertexType>::getIndex(const VertexType& vertex)
{
    // 1. Search for it inside vertices
    for(int i{}; i < numOfVertices; i++)
    {
        // 2. Return its index if found
        if(vertices[i] == vertex) return i; // This requires "VertexType" supports [operator==]
    }

    // 3. Return -1 if it doesn’t exist
    return -1;
}

template<class VertexType>
void Graph<VertexType>::getAdjVertices(VertexType vertex, queue<VertexType>& vertexQ)
{
    // 1. Clear the queue
    while (!vertexQ.empty()) vertexQ.pop();

    // 2. Get vertex index
    int vertexIndex = getIndex(vertex);
    if (vertexIndex == -1) return;


    // 3. Scan adjacency matrix for the given vertex
    for(int i{}; i < numOfVertices; i++)
    {
        // 4. If there the weight is not 0 , then it's an Adjacent Vertex ==> Add to the Queue
        if(edges[vertexIndex][i] == 0) continue;
        else vertexQ.push(vertices[i]);
    }
}

template<class VertexType>
void Graph<VertexType>::clearMarks()
{
    for(int i{}; i < numOfVertices; i++) marks[i] = false;
}

template<class VertexType>
void Graph<VertexType>::markVertex(VertexType vertex)
{
    // 1. Get the Index of the Vertex
    int index = getIndex(vertex);

    // 2. Update the Marks list if the Index Exist

    if (index != -1) marks[index] = true;
}

template<class VertexType>
bool Graph<VertexType>::isMarked (VertexType vertex)
{
    // 1. Get the Index of the Vertex
    int index = getIndex(vertex);

    // 2. Check the Marks list
    if (index != -1) return marks[index];
    return false; // Non-existing vertex is treated as unvisited
}

template<class VertexType>
void Graph<VertexType>::depthFirstSearch (const VertexType& startVertex, const VertexType& endVertex)   /// Stack , Queue
{
    // 1. Clear Marks
    clearMarks();

    // 2. Create a stack and push the start vertex to it
    stack<VertexType> s;
    s.push(startVertex);

    // While the stack is not empty:
    while(!s.empty())
    {
        // 3. Pop vertex from stack
        VertexType current = s.top();
        s.pop();

        // If "current" Vertex is NOT marked:
        if(!isMarked(current))
        {
            markVertex(current);        // 4. Mark it
            cout << current << " ";     // 5. Print it

            if (current == endVertex) return; // If you reach the end then stop

            // 6. Get Adjacent Vertices of the "current" Vertex.
            queue<VertexType> adjVertices;
            getAdjVertices(current, adjVertices);

            // 7. Push neighbors onto stack
            // For each neighbor of the node:
            while(!adjVertices.empty())
            {
                // 7.1 Get the Neighbor
                VertexType next = adjVertices.front();
                adjVertices.pop();

                // If the neighbor is NOT marked
                if (!isMarked(next)) s.push(next); // 7.2 Push it into the stack.
            }
        }
    }

    cout << endl;
}

template<class VertexType>
void Graph<VertexType>::breadthFirstSearch (const VertexType& startVertex, const VertexType& endVertex)  /// 2 Queue
{
    // 1. Clear Marks
    clearMarks();

    // 2. Create a Queue and Enqueue the start vertex to it
    queue<VertexType> q;
    q.push(startVertex);

    // While the Queue is not empty:
    while(!q.empty())
    {
        // 3. Dequeue vertex from Queue
        VertexType current = q.front();
        q.pop();

        // If "current" Vertex is NOT marked:
        if(!isMarked(current))
        {
            markVertex(current);        // 4. Mark it
            cout << current << " ";     // 5. Print it

            if (current == endVertex) return; // If you reach the end then stop

            // 6. Get Adjacent Vertices of the "current" Vertex.
            queue<VertexType> adjVertices;
            getAdjVertices(current, adjVertices);

            // 7. Push neighbors onto stack
            // For each neighbor of the node:
            while(!adjVertices.empty())
            {
                // 7.1 Get the Neighbor
                VertexType next = adjVertices.front();
                adjVertices.pop();

                // If the neighbor is NOT marked
                if (!isMarked(next)) q.push(next); // 7.2 Push it into the Queue
            }
        }
    }

    cout << endl;
}

///3. Print All Shortest Path /// Dijkstra
template<class VertexType>
void Graph<VertexType>::dijkstra (const VertexType& startVertex) /// Pirority Queue , Adjacent Queue
{
    // 1. Clear Marks
    clearMarks();

    // 2. Create a Distance array for all the shortest paths, set everything is “infinite”
    const int INF = INT_MAX;
    int dist[GRAPH_MAX]; // Shortest distance from start
    for (int i = 0; i < numOfVertices; i++) dist[i] = INF;

    // 3. Set distance of startVertex to 0
    int startIndex = getIndex(startVertex);
    if (startIndex == -1) return;

    dist[startIndex] = 0; // Distance to itself is 0

    // 4. Create the Min Heap - Priority Queue ==> pair<distance, vertexIndex>
    priority_queue<
    P,
    vector<P>,
    greater<P>
    > pq;

    // 5. Push Start Vertex
    pq.push({0, startIndex});

    // Continue until there are no reachable vertices left.
    while (!pq.empty())
    {
        // 6. Extract closest vertex
        int currentVertex = pq.top().second;
        pq.pop();

        // 7. If already marked ==> Skip
        if (marks[currentVertex]) continue; // already visited

        // 8. Mark the Vertex
        markVertex(vertices[currentVertex]);

        // Update neighbors
        for (int neighbor = 0; neighbor < numOfVertices; neighbor++)
        {
            int weight = edges[currentVertex][neighbor];

            // If there is No edge OR already visited
            if (weight == 0 || marks[neighbor]) continue; // 9. Skip it

            // 10. Update Distance if the current distance is less than the previous one
            if (dist[currentVertex] != INF && dist[currentVertex] + weight < dist[neighbor])
            {
                dist[neighbor] = dist[currentVertex] + weight;

                // 11. Push updated distance
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    // Print distances
    cout << "\n--- Shortest paths from " << startVertex << " ---\n";
    for (int i = 0; i < numOfVertices; i++)
        cout    << startVertex << " -> " << vertices[i]
                << " = " << dist[i] << endl;
}

int main()
{
    // Graph
    // A → B (4)
    // A → C (2)
    // B → C (5)
    // B → D (10)
    // C → E (3)
    // E → D (4)

    Graph<char> g;

    // ===== Add Vertices =====
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');

    // ===== Add Edges (Directed, Weighted) =====
    g.addEdge('A', 'B', 4);
    g.addEdge('A', 'C', 2);
    g.addEdge('B', 'C', 5);
    g.addEdge('B', 'D', 10);
    g.addEdge('C', 'E', 3);
    g.addEdge('E', 'D', 4);

    // ===== Test Path Weight =====
    cout << "Weight A -> B = " << g.getPathWeight('A', 'B') << endl;
    cout << "Weight C -> E = " << g.getPathWeight('C', 'E') << endl;
    cout << endl;

    // ===== DFS =====
    cout << "DFS from A to D: ";
    g.depthFirstSearch('A', 'D');
    cout << endl;

    // ===== BFS =====
    cout << "BFS from A to D: ";
    g.breadthFirstSearch('A', 'D');
    cout << endl;

    // ===== Dijkstra =====
    g.dijkstra('A');

    return 0;
}
