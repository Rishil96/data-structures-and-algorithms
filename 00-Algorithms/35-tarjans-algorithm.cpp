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

        void tarjansAlgorithm(int src, int parent, int &timer, vector<int>& tin, vector<int>& low, unordered_map<int, bool>& vis) {
            // 1. Visit current node and update timer on both tin and low
            vis[src] = 1;
            tin[src] = timer;
            low[src] = timer;
            timer++;

            // 2. Visit neighbours of source node
            for (auto nbr: adjList[src]) {
                // Avoid going back to the node we just came from
                if (nbr.first == parent) continue;

                // Visit neighbour if not visited
                if (!vis[nbr.first]) {
                    tarjansAlgorithm(nbr.first, src, timer, tin, low, vis);
                    // Update low of source if we can reach source faster from nbr
                    low[src] = min(low[src], low[nbr.first]);
                    // Check bridge
                    if (low[nbr.first] > low[src]) {
                        cout << nbr.first << " --- " << src << " is a bridge." << endl;
                    }
                }
                // Another path possible, update if shorter path found
                else {
                    low[src] = min(low[src], low[nbr.first]);
                }
            }
        }
};

int main() {

    Graph h;
    h.addEdge(0, 1, 1, 0);
    h.addEdge(0, 2, 1, 0);
    h.addEdge(1, 2, 1, 0);
    h.addEdge(0, 3, 1, 0);
    h.addEdge(3, 4, 1, 0);

    int n = 5;
    int timer = 0;
    vector<int> tin(n);
    vector<int> low(n);
    unordered_map<int, bool> vis;
    h.tarjansAlgorithm(0, -1, timer, tin, low, vis);

    return 0;
}