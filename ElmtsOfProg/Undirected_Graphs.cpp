#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <functional>   // Contains function for hash
using namespace std;

// Used to print out additionals log messages
#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

// -----------------------------------------------------------------------------------------
// This is a Undirected Graph
// http://codereview.stackexchange.com/questions/36464/coding-and-printing-a-graph
// http://stackoverflow.com/questions/5493474/graph-implementation-c
//
// Link on how to make use of "template"s
// http://stackoverflow.com/questions/39095527/how-to-achieve-forward-declaration-of-template-class
//      If you use Graph like Graph<std::string> g;, then the template parameter E will be std::string, the member vertices will be vector<Vertex<std::string>>.
//      Then in Vertex, _data will be std::string, _edges will be vector<Edge<std::string>>
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
// Graph Class
        // Have a vector to store all Vertices of the Graph
        // MAP:
        //      The map is used to quickly tell if Vertex is present or not based on the the
        //      data. 
        //      Key: hash(data) given to Vertex
        //      Val: Place where Vertex is stored on the Vector
        //
        //      So with a Vertex's data, we can hash it to get the Key.
        //      Using the key, find if Vertex is present; Also where the Vertex is present
        //
        // The map also gives where the Vertex is stored in the vector
// http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
// TODO: Check the above link for properly doing it
// -----------------------------------------------------------------------------------------
template <typename E>
class Graph
{
    private:
        template<typename T>
        class Vertex; // Forward Declaration

        vector<Vertex <E> > _vertices;
        unordered_map<uint32_t, uint32_t> _verticesMap;

        // Inner Class corresponding to an Edge of a graph.
        // Each edge has
        //      1) Origin
        //      2) Destination
        //      3) Weight
        // Using the Edge, you can get its origin, destination or its weight
        class Edge
        {
            public:
                Vertex<E>& _orig;

                Vertex<E>& _dest;
                uint32_t _weight;

                Edge(Vertex<E>& orig, Vertex<E>& dest, uint32_t weight) : _orig(orig),
                                                                          _dest(dest),
                                                                          _weight(weight) { }

                Vertex<E>& getOrig() { return _orig; }
                Vertex<E>& getDest() { return _dest; }
                uint32_t getWeight() { return _weight; }
        };

        // Inner Class for Vertex of a Graph
        // Each Vertex has,
        //      1) _id
        //      2) Data
        //      3) List of edges
        // Using a Vertex you can,
        //      - add Edge to the Vertex
        //      - print all Edges of the Vertex
        template<typename T>
        class Vertex
        {
            public:
                uint32_t _id;   // A unique identifier for each node
                T _data;
                vector<Edge> _edges;
                bool _isVisited;

                Vertex(T data)
                {
                    uint32_t hashVal = std::hash<E>()(data);

                    _id = hashVal;
                    _data = data;
                    _isVisited = false;
                }

                Vertex(uint32_t id, T data) : _id(id),
                                              _data(data),
                                              _isVisited(false) { }

                uint32_t getId() { return _id; }

                // This function adds an Edge to the given vertex
                void addEdgeToVertex(Edge& edge)
                {
                    _edges.push_back(edge);
                }

                // This utility function prints all edges of a Vertex
                void printEdgesOfVertex()
                {
                    cout << "NODE: " << _data << "'s EDGES:" << endl;
                    for(Edge e : _edges)
                    {
                        cout << e.getOrig()._data << "--" << e.getDest()._data << "::" << e.getWeight() << endl;
                    }
                }

                void clearVisited()
                {
                    _isVisited = false;
                }
        };

        // From a Graph class you can,
        //      - add Edge between two vertices
        //      - add a Vertex to the graph
        //      - print all Edges of a Vertex
        //      - print the Graph
    public:
        void printGraphBFS(const E& data);
        void printGraphDFS(const E& data);
        uint32_t getVertexId(const E& vertexData);
        void addEdge(Vertex<E>& orig, Vertex<E>& dest, uint32_t weight);
        void addEdge(E& orig, E& dest, uint32_t weight);
        uint32_t addVertex(E data);
        uint32_t getIdOfVertex(const E& data);
        void printEdges(Vertex<E>& vert);
        void printGraph();
        void clearVisitedGraph();

        // AddEdge() when we have both the Vertices
        // Assumption: Vertex is present
        Vertex<E>* getVertex(const E& data)
        {
            auto itr = _verticesMap.find(getIdOfVertex(data));

            if (itr != _verticesMap.end())
            {
                return &(_vertices[itr->second]);
            }
            else
            {
                return nullptr;
            }
        }
};

// -----------------------------------------------------------------------------------------
//
// AddEdge() when we have both the Vertices
// -----------------------------------------------------------------------------------------
template <typename E>
void
Graph<E>::addEdge(Vertex<E>& orig, Vertex<E>& dest, uint32_t weight)
{
    //DEBUG_MSG("AddEdge(): Orig: " << orig._data << "; Dest: " << dest._data << endl);
    Edge edge1(orig, dest, weight);
    orig.addEdgeToVertex(edge1);

    Edge edge2(dest, orig, weight);
    dest.addEdgeToVertex(edge2);
}

// -----------------------------------------------------------------------------------------
// AddEdge() when we just have the data of Vertices
// -----------------------------------------------------------------------------------------
template <typename E>
void
Graph<E>::addEdge(E& orig, E& dest, uint32_t weight)
{
    addEdge(_vertices[addVertex(orig)], _vertices[addVertex(dest)], weight);
}

// -----------------------------------------------------------------------------------------
// IMP: Add template arguement
// This functions returns the index of the vertex
// -----------------------------------------------------------------------------------------
template <typename E>
uint32_t
Graph<E>::addVertex(E data)
{
    uint32_t hashVal = std::hash<E>()(data);
    auto itr = _verticesMap.find(hashVal);

    if (itr != _verticesMap.end())
    {
        //DEBUG_MSG("Node Already Present at: " << itr->second << endl);
        return itr->second;
    }

    Vertex<E> vert(hashVal, data);
    _vertices.push_back(vert);

    //DEBUG_MSG("Hash Val for: " << data << " : " << hashVal << endl);
    _verticesMap[hashVal] =  _vertices.size() - 1;

    return _vertices.size() - 1;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <typename E>
uint32_t
Graph<E>::getIdOfVertex(const E& data)
{
    return std::hash<E>()(data);
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <typename E>
void
Graph<E>::printEdges(Vertex<E>& vert)
{
    vert.printEdgesOfVertex();
}

// Utility function to print the complete graph
template <typename E>
void
Graph<E>::printGraph()
{
    for (auto vert : _vertices)
    {
        vert.printEdgesOfVertex();
    }
}

// -----------------------------------------------------------------------------------------
// Utility function to clear Visited on each Vertex
// -----------------------------------------------------------------------------------------
template <typename E>
void
Graph<E>::clearVisitedGraph()
{
    for (auto vert : _vertices)
    {
        vert.clearVisited();
    }
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <typename E>
uint32_t
Graph<E>::getVertexId(const E& vertexData)
{
    Vertex<E> v(vertexData);    
    uint32_t vertexId = v.getId();
    return vertexId;
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <typename E>
void
Graph<E>::printGraphBFS(const E& data)
{
    Vertex<E>* v = getVertex(data);
    queue<Vertex<E> *> bfsQueue;

    v->_isVisited = true;
    bfsQueue.push(v);

    while(!bfsQueue.empty())
    {
        Vertex<E>* tmpVert = bfsQueue.front();
        bfsQueue.pop();
        
        cout << "BFS: " << tmpVert->_data << "; " << tmpVert->_edges.size() << endl;
        for (Edge e : tmpVert->_edges)
        {
            // Only if the destination is not visited add it to the queue
            if (!((e.getDest())._isVisited))
            {
                e.getDest()._isVisited = true;
                cout << "\t; Dest: " << e.getDest()._data << endl;
                bfsQueue.push(&e.getDest());
            }
        }
    }
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
template <typename E>
void
Graph<E>::printGraphDFS(const E& data)
{
    Vertex<E>* v = getVertex(data);
    stack<Vertex<E> *> dfsStack;

    v->_isVisited = true;
    dfsStack.push(v);

    while(!dfsStack.empty())
    {
        Vertex<E>* tmpVert = dfsStack.top();
        dfsStack.pop();
        
        cout << "DFS: " << tmpVert->_data << "; " << tmpVert->_edges.size() << endl;
        for (Edge e : tmpVert->_edges)
        {
            if (!((e.getDest())._isVisited))
            {
                e.getDest()._isVisited = true;
                cout << "\t; Dest: " << e.getDest()._data << endl;
                dfsStack.push(&e.getDest());
            }
        }
    }
}

// -----------------------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------------------
int main()
{
    /*
     *      b ----- d ------- f
     *    /       /  \       /
     *  a       /      \    /
     *    \   /         \  /
     *      c ---------- e
     */

    Graph<string> g;
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addVertex("E");
    g.addVertex("F");

    string a1 = "A";
    string b1 = "B";
    g.addEdge(a1, b1, 1);

    string a2 = "A";
    string b2 = "C";
    g.addEdge(a2, b2, 2);

    string a3 = "B";
    string b3 = "D";
    g.addEdge(a3, b3, 3);

    string a4 = "C";
    string b4 = "D";
    g.addEdge(a4, b4, 4);

    string a5 = "C";
    string b5 = "E";
    g.addEdge(a5, b5, 5);

    string a6 = "D";
    string b6 = "E";
    g.addEdge(a6, b6, 6);

    string a7 = "D";
    string b7 = "F";
    g.addEdge(a7, b7, 7);

    string a8 = "E";
    string b8 = "F";
    g.addEdge(a8, b8, 8);

    g.printGraph();

    string bfs1 = "A";
    //g.printGraphBFS(bfs1);
    //g.clearVisitedGraph();

    cout << endl;
    g.printGraphDFS(bfs1);
    g.clearVisitedGraph();

    cout << endl;
    return 0;
}

