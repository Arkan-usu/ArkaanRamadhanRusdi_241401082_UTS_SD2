#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjList;  // Adjacency list dengan pair (neighbor, weight)

public:
    Graph(int V) {
        numVertices = V;
        adjList.resize(numVertices);
    }

    void addEdge(int i, int j, int weight) {
        // i dan j dikurang satu supaya sesuai dengan indeks 0-based
        i--;
        j--;
        if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
            adjList[i].push_back({j, weight});
            adjList[j].push_back({i, weight});  // Karena graf tidak berarah
        } else {
            cout << "Indeks simpul tidak valid." << endl;
        }
    }

    void printAdjList() {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << char('A' + i) << " -> ";
            for (auto& p : adjList[i]) {
                cout << char('A' + p.first) << "(" << p.second << ") ";
            }
            cout << endl;
        }
    }

    // ----- BAGIAN DFS -----
    void dfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        vector<string> order;
        cout << "PENJELAJAHAN PARUL (DFS dari A)" << endl;

        dfsUtil(startVertex, visited, order);

        for (size_t i = 0; i < order.size(); ++i) {
            cout << order[i];
            if (i < order.size() - 1) cout << "-> ";
        }
        cout << endl << endl;
    }

    void dfsUtil(int currentVertex, vector<bool>& visited, vector<string>& order) {
        visited[currentVertex] = true;
        order.push_back(string(1, 'A' + currentVertex));

        for (auto& p : adjList[currentVertex]) {
            int neighbor = p.first;
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited, order);
            }
        }
    }

    // ----- BAGIAN BFS -----
    void bfs(int startVertex, int endVertex) {
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1);
        vector<int> dist(numVertices, -1);
        queue<int> q;

        // Tandai simpul awal sudah dikunjungi dan masukkan ke antrian
        visited[startVertex] = true;
        q.push(startVertex);
        parent[startVertex] = -1;
        dist[startVertex] = 0;

        cout << "Breadth-First Traversal (dari vertex " << startVertex << "):" << endl;

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << char('A' + currentVertex) << " ";  // Cetak huruf A-E

            for (auto& p : adjList[currentVertex]) {
                int neighbor = p.first;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    parent[neighbor] = currentVertex;
                    dist[neighbor] = dist[currentVertex] + 1;
                }
            }
        }
        cout << endl;

        // Reconstruct path otomatis
        vector<int> path;
        int current = endVertex;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());

        // Hitung total jarak
        int totalJarak = 0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            for (auto& p : adjList[u]) {
                if (p.first == v) {
                    totalJarak += p.second;
                    break;
                }
            }
        }

        // Nama kafe
        vector<string> kafeNama = {"Warung Kopi Pak Harry", "Kedai Coding IKLC", "Catfe Alya", "Studio Fasilkom-TI", "Wi-Fi Gratis Sejagat"};

        cout << "JALUR TERCEPAT PARUL (BFS):" << endl;
        cout << kafeNama[path[0]] << " (A)" << endl;
        for (size_t i = 1; i < path.size(); ++i) {
            int u = path[i-1];
            int v = path[i];
            int bobot = 0;
            for (auto& p : adjList[u]) {
                if (p.first == v) {
                    bobot = p.second;
                    break;
                }
            }
            cout << bobot << "m" << endl;
            cout << kafeNama[path[i]] << " (" << char('A' + path[i]) << ")" << endl;
        }

        // Output jalur 
        cout << "Jalur terpendek: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << char('A' + path[i]);
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "Total langkah: " << (path.size() - 1) << " edge" << endl;
        cout << "Total jarak: " << totalJarak << " meter" << endl;
    }
};

int main() {
    Graph g(5);  // 5 kafe: A B C D E

    // Tambah edge dengan bobot sesuai soal
    g.addEdge(1, 3, 2);  // A-C (2) 
    g.addEdge(1, 2, 4);  // A-B (4) 
    g.addEdge(2, 4, 3);  // B-D (3)
    g.addEdge(3, 4, 1);  // C-D (1)
    g.addEdge(4, 5, 5);  // D-E (5)

    // Cetak adjacency list untuk melihat representasi graf
    g.printAdjList();
    cout << endl;

    // DFS dari A (index 0)
    g.dfs(0);

    // BFS dari A ke E (0 ke 4)
    g.bfs(0, 4);

    return 0;
}
