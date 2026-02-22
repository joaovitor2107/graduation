#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;


int a = 0;
int b = 1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;


vector<int>dijkstra(const vector<vector<pair<int,int>>>& adj, int start){

    vector<int>unvisited;
    for(int i = 0; i < adj.size();i++){
        unvisited.push_back(i);
    }

    vector<int>dist(adj.size(), INT_MAX);

    dist[start] = 0;

    while(!unvisited.empty()){
        int n;
        int aux =INT_MAX;
        for(auto i : unvisited){
            if(dist[i] < aux){
                aux = dist[i];
                n = i;
            }
        }

        unvisited.erase(remove(unvisited.begin(), unvisited.end(), n), unvisited.end());
        //aux.first -> adj elements
        //aux.second -> distance to this element

        for(auto elem : adj[n]){
            int temp = elem.second;
            temp += dist[n];
            if(temp < dist[elem.first]) dist[elem.first] = temp;
        }

    }

    return dist;
}

void addEdge(vector<vector<pair<int,int>>>& adj, int node1, int node2, int w){
    adj[node1].push_back({node2, w});
    adj[node2].push_back({node1, w});
}

int main(){
    vector<vector<pair<int,int>>> adj(6);

    addEdge(adj, a, b, 2);
    addEdge(adj, a, d, 8);
    addEdge(adj, b, d, 5);
    addEdge(adj, b, e, 6);
    addEdge(adj, d, e, 3);
    addEdge(adj, d, f, 2);
    addEdge(adj, e, c, 9);
    addEdge(adj, e, f, 1);
    addEdge(adj, f, c, 3);

    vector<int> dist = dijkstra(adj, a);
    for (int elem : dist) {
        cout << elem << " ";
    }

    return 0;
}
