#include <iostream>
#include <unordered_map>
#include <list>
#include <stack>
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

        void topologicalSortDFS(int src, stack<int> &topo, unordered_map<int, bool> &visited) {
            // 1. Visit source
            visited[src] = 1;

            // 2. Traverse all neighbours
            for (auto nbr: adjList[src]) {
                if (!visited[nbr.first]) {
                    topologicalSortDFS(nbr.first, topo, visited);
                }
            }

            // 3. Add source in topological sort stack
            topo.push(src);
        }

        void dfs(int src, unordered_map<int, bool>& visited, unordered_map<int, list<int>> &reverseAdjList) {
            // Visit source
            cout << src << " ";
            visited[src] = 1;

            // Visit all unvisited neighbours
            for (auto nbr: reverseAdjList[src]) {
                if (!visited[nbr]) {
                    dfs(nbr, visited, reverseAdjList);
                }
            }
        }

        int kosaRajuAlgorithmSCC(int n) {
            // 1. Initialize stack for topo sort, visited map and reverse adjList to save the reverse directions between nodes
            stack<int> topoSort;
            unordered_map<int, bool> vis;
            unordered_map<int, list<int>> reverseAdjList;

            // 2. Get topological sort in stack
            for (int i=0; i<n; i++) {
                if (!vis[i]) {
                    vis[i] = 1;
                    topologicalSortDFS(i, topoSort, vis);
                }
            }

            // 3. Create Reverse adjacency list 
            for (auto node: adjList) {
                for (auto nbr: node.second) {
                    reverseAdjList[nbr.first].push_back(node.first);
                }
            }

            // 4. DFS Traversal with tracking of SCC
            int count = 0;
            vis.clear();

            while (!topoSort.empty()) {
                int topNode = topoSort.top(); topoSort.pop();

                if (!vis[topNode]) {
                    cout << "SCC " << count + 1 << " :- ";
                    vis[topNode] = 1;
                    count++;
                    dfs(topNode, vis, reverseAdjList);
                    cout << endl;
                }
            }

            cout << "\nCount of Strongly Connected Components: ";
            return count;
        }
};

int main() {

    Graph g;
    g.addEdge(0, 1, 1, 1);
    g.addEdge(1, 2, 1, 1);
    g.addEdge(2, 3, 1, 1);
    g.addEdge(3, 0, 1, 1);
    g.addEdge(2, 4, 1, 1);
    g.addEdge(4, 5, 1, 1);
    g.addEdge(5, 6, 1, 1);
    g.addEdge(6, 4, 1, 1);
    g.addEdge(6, 7, 1, 1);

    g.print();
    cout << endl << g.kosaRajuAlgorithmSCC(8) << endl;

    return 0;
}