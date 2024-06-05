#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
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
};

int main() {

    Graph g;
    g.addEdge(0, 1, 5, 1);
    g.addEdge(1, 2, 3, 1);
    g.addEdge(1, 5, 8, 1);
    g.addEdge(2, 3, 7, 1);
    g.addEdge(2, 4, 2, 1);
    g.addEdge(3, 4, 11, 1);
    g.addEdge(5, 6, 1, 1);
    g.addEdge(6, 8, 9, 1);
    g.addEdge(8, 7, 9, 1);

    g.print();
    cout << "\nBFS: ";
    unordered_map<int, bool> v1;
    g.bfs(0, v1);
    
    cout << "\nDFS: ";
    unordered_map<int, bool> v2;
    g.dfs(0, v2);

    return 0;
}