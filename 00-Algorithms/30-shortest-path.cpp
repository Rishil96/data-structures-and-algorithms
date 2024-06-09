#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Graph
{
    unordered_map<int, list<pair<int, int>>> adjList;

    public:
        void addEdge(int u, int v, int wt, bool isDirected) {
            adjList[u].push_back({v, wt});
            if (!isDirected) {
                adjList[v].push_back({u, wt});
            }
        }

        void print() {
            for (auto item: adjList) {
                int u = item.first;
                auto edges = item.second;

                cout << u << " => ";
                for (auto edge: edges) {
                    cout << "(" << edge.first << ", " << edge.second << "), ";
                }
                cout << endl;
            }
        }

        void bfs(int src, unordered_map<int, bool> &vis) {
            // 1. Add source node in queue
            queue<int> q;
            q.push(src);
            vis[src] = 1;
            
            // 2. Run while loop till queue is empty
            while (!q.empty()) {
                // 3. Get front node of queue and visit it
                int frontNode = q.front();
                q.pop();
                cout << frontNode << " ";
                // 4. Visit all the neighbours of front node if not visited
                for (auto nbr: adjList[frontNode]) {
                    if (!vis[nbr.first]) {
                        vis[nbr.first] = 1;
                        q.push(nbr.first);

                    }
                }
            }
        }

        void dfs(int src, unordered_map<int, bool> &vis) {
            
            // 1. Visit the source node
            cout << src << " ";
            vis[src] = 1;

            // 2. Visit the neighbours of src node if not visited
            for (auto nbr: adjList[src]) {
                if (!vis[nbr.first]) {
                    vis[nbr.first] = 1;
                    dfs(nbr.first, vis);
                }
            }
        }

        bool isCycleUDGBFS(int src, unordered_map<int, bool> &vis, unordered_map<int, int> &parent) {
            // 1. Initialize queue and add source in queue and mark visited and set parent to -1
            queue<int> q;
            q.push(src);
            vis[src] = 1;
            parent[src] = -1;

            // 2. Perform BFS till we visit all elements or till we find a cycle
            while (!q.empty()) {
                int frontNode = q.front(); q.pop();
                
                // 3. Loop through neighbours of frontNode
                for (auto nbr: adjList[frontNode]) {
                    // If current neighbour is not visited, mark visited and set parent to front node and add it in queue to visit via BFS
                    if (!vis[nbr.first]) {
                        vis[nbr.first] = 1;
                        parent[nbr.first] = frontNode;
                        q.push(nbr.first);
                    }
                    else {
                        // If current neighbour is the parent of frontNode then we are fine 
                        // but if not it means cycle is present as we reached current neighbour twice and not from its parent
                        if (parent[frontNode] != nbr.first) return true;
                    }
                }
            }

            return false;
        }

        bool isCycleUDGDFS(int src, unordered_map<int, bool> &vis, int parent) {
            // 1. Mark current node as visited
            vis[src] = true;

            // 2. Loop through current node's neighbours
            for (auto nbr: adjList[src]) {
                // If neighbour is not visited go visit it
                if (!vis[nbr.first]) {
                    return isCycleUDGDFS(nbr.first, vis, src);
                }
                // If neighbour is visited and it is not the parent of source, it means cycle is present and neighbour was visited twice from different nodes.
                else if (nbr.first != parent){
                    return true;
                }
            }

            return false;
        }

        bool isCycleDGDFS(int src, unordered_map<int, bool> &vis, unordered_map<int, bool>& dfsVis) {

            // 1. Visit the source node and add it in DFS Recursive stack mapper dfsVis
            vis[src] = 1;
            dfsVis[src] = 1;

            // 2. Loop through all neighbours of source
            for (auto nbr: adjList[src]) {
                
                // If neighbour is not visited, visit it by calling dfs
                if (!vis[nbr.first]) {                    
                    // Call recursion and check if cycle is found and return true if yes
                    bool ans = isCycleDGDFS(nbr.first, vis, dfsVis);
                    if (ans) return true;
                }
                else {
                    // If current neighbour is visited and is also is Recursive call stack , it means cycle is present
                    if (dfsVis[nbr.first]) return true;
                }
            }

            // Once dfs is completed for source node, mark it as false
            dfsVis[src] = 0;

            // Return false if no cycle found
            return false;
        }

        // Topological Sort DFS
        void topoSortDFS(int src, unordered_map<int, bool>& vis, stack<int> &topo) {
            // 1. Visit the source node
            vis[src] = 1;

            // 2. Visit all the neighbours of source node
            for (auto nbr: adjList[src]) {
                if (!vis[nbr.first]) topoSortDFS(nbr.first, vis, topo);
            }

            // 3. Add source node in topo stack after all neighbours are visited
            topo.push(src);

            return ;
        }

        // Topological Sort BFS
        void topoSortBFS(int n) {
            // 1. Calculate the indegree of each node which will tell us how many nodes are dependent on that node.
            unordered_map<int, int> indegree;

            for (auto item: adjList) {
                int u = item.first;
                auto edges = item.second;

                for (auto edge: edges) {
                    int v = edge.first;
                    int wt = edge.second;

                    // Increment indegree of v as v is dependent on u
                    indegree[v]++;
                }
            }

            // 2. Add all nodes with indegree 0 in queue
            queue<int> q;
            for (int i=0; i<n; i++) if (indegree[i] == 0) q.push(i);

            // 3. BFS Traversal
            while (!q.empty()) {
                // Get front node from queue
                int frontNode = q.front(); q.pop();

                // Front node is independent so add it in ans stack/print it
                cout << frontNode << " ";

                // Since frontNode is visited, remove its dependency from all of its neighbour nodes
                for (auto nbr: adjList[frontNode]) {
                    indegree[nbr.first]--;
                    // Add neighbour in queue if indegree is 0
                    if (indegree[nbr.first] == 0) q.push(nbr.first);
                }
            }
        }

        // Shortest Path BFS
        vector<int> shortestPathBFS(int src, int dst) {
            // 1. Initialize variables
            vector<int> path;
            queue<int> q;
            unordered_map<int, bool> vis;
            unordered_map<int, int> parent;

            // 2. Add source in queue to start BFS
            q.push(src);
            vis[src] = 1;
            parent[src] = -1;
            
            // 3. BFS
            while (!q.empty()) {
                // 3a. Get front node from queue
                int frontNode = q.front(); q.pop();

                // 3b. Check if front node is our destination and if yes break
                if (frontNode == dst) break;

                // 3c. Visit all the non-visited neighbours of front node and mark their parents as front node
                for (auto nbr: adjList[frontNode]) {
                    if (!vis[nbr.first]) {
                        vis[nbr.first] = 1;
                        parent[nbr.first] = frontNode;
                        q.push(nbr.first);
                    }
                }
            }

            while (dst != parent[src]) {
                path.insert(path.begin(), dst);
                dst = parent[dst];
            }

            return path;
        }

        void topologicalSortDFS(int src, unordered_map<int, bool>& visited, stack<int>& ans) {
            
            visited[src] = 1;

            for (auto nbr: adjList[src]) {
                if (!visited[nbr.first]) {
                    topologicalSortDFS(nbr.first, visited, ans);
                }
            }

            ans.push(src);

            return ;
        }

        void shortestPathDFS(int dst, stack<int>& topOrder, int n) {
            // Create distance vector to add shortest distance of from all nodes to destination
            vector<int> dist(n, INT_MAX);

            // Get source node and set distance of its neighbours
            int src = topOrder.top(); topOrder.pop();
            dist[src] = 0;
            if (dist[src] != INT_MAX) {
                for (auto nbr: adjList[src]) {
                    if (dist[src] + nbr.second < dist[nbr.first]) {
                        dist[nbr.first] = dist[src] + nbr.second;
                    }
                }
            }

            // Set distance of all nodes in topological order stack
            while (!topOrder.empty()) {
                int topElement = topOrder.top(); topOrder.pop();

                if (dist[topElement] != INT_MAX) {
                    for (auto nbr: adjList[topElement]) {
                        if (dist[topElement] + nbr.second < dist[nbr.first]) {
                            dist[nbr.first] = dist[topElement] + nbr.second;
                        }
                    }
                }
            }

            for (int i=0; i<dist.size(); i++) {
                if (i == dst)
                    cout << "Ans " << i << " -> " << dist[i] << endl;
                else
                    cout << i << " -> " << dist[i] << endl;
            }
        }

};

int main() {

    Graph g;
    g.addEdge(0, 1, 1, 0);
    g.addEdge(0, 2, 1, 0);
    g.addEdge(0, 3, 1, 0);
    
    g.addEdge(1, 4, 1, 0);
    g.addEdge(2, 5, 1, 0);
    g.addEdge(3, 6, 1, 0);

    g.addEdge(4, 5, 1, 0);
    g.addEdge(6, 5, 1, 0);

    vector<int> path = g.shortestPathBFS(0, 5);
    cout << "Shortest Path BFS: ";
    for (auto node: path) cout << node << " -> ";
    cout << endl;

    Graph h;
    h.addEdge(0, 1, 5, 1);
    h.addEdge(0, 2, 3, 1);
    h.addEdge(2, 1, 2, 1);
    h.addEdge(1, 3, 3, 1);
    h.addEdge(2, 3, 5, 1);
    h.addEdge(2, 4, 6, 1);
    h.addEdge(4, 3, 1, 1);

    unordered_map<int, bool> isVisited;
    stack<int> topOrder;
    h.topologicalSortDFS(0, isVisited, topOrder);
    h.shortestPathDFS(3, topOrder, 5);

    return 0;
}