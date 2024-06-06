#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
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
};


int main() {

    Graph g;
    g.addEdge(0, 1, 0, 0);
    g.addEdge(1, 2, 0, 0);
    g.addEdge(2, 3, 0, 0);
    g.addEdge(2, 4, 0, 0);

    unordered_map<int, bool> vis;
    unordered_map<int, bool> vis2;
    unordered_map<int, int> parent;
    cout << "Cycle Detection in Undirected Graph using BFS 1: " << g.isCycleUDGBFS(0, vis, parent) << endl;
    cout << "Cycle Detection in Undirected Graph using DFS 1: " << g.isCycleUDGDFS(0, vis2, -1) << endl;
    g.addEdge(3, 4, 0, 0);

    vis.clear();
    vis2.clear();

    cout << "Cycle Detection in Undirected Graph using BFS 2: " << g.isCycleUDGBFS(0, vis, parent) << endl;
    cout << "Cycle Detection in Undirected Graph using DFS 2: " << g.isCycleUDGDFS(0, vis2, -1) << endl;


    return 0;
}

