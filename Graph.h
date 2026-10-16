#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include "RoadDetails.h"

using namespace std;

struct weighted {
    int index;
    RoadDetails weight;
    bool operator==(const weighted& other) const { return index == other.index; }
};

template <class t> struct Gnode {
    t vertex;
    list<weighted> Neighbors;
    bool operator==(t v) { return vertex == v; }
};

template <class t, int size> class Graph {

    Gnode<t> array[size];
    bool directed;

public:
    int Vcount;
    Graph() {
        Vcount = 0;
        directed = false;
    }
    Graph(bool x) {
        Vcount = 0;
        directed = x;
    }

    void bfs(int levels[size]) {
        if (Vcount <= 0) {
            return;
        }
        int visited[size] = { 0 };
        queue<int> adjacent;
        int starting = getIndex(array[0].vertex);
        adjacent.push(starting);
        visited[starting] = 1;

        levels[starting] = 0;

        while (!adjacent.empty()) {
            int top = adjacent.front();
            cout << array[top].vertex << "\t";
            adjacent.pop();

            typename list<weighted>::iterator temp = array[top].Neighbors.begin();
            while (temp != array[top].Neighbors.end()) {
                int neighborIndex = temp->index;
                if (visited[neighborIndex] != 1) {
                    visited[neighborIndex] = 1;
                    adjacent.push(neighborIndex);
                    levels[neighborIndex] = levels[top] + 1;
                }
                temp++;
            }
        }

        cout << endl;
    }

    void PrintLevels() {
        int levels[size];
        for (int i = 0; i < size; i++) {
            levels[i] = -1;
        }
        bfs(levels);
        int max = 0;

        for (int i = 0; i < Vcount; i++) {
            if (max < levels[i]) {
                max = levels[i];
            }
        }

        for (int i = 0; i <= max; i++) {
            cout << "\nLevel = " << i << endl;
            for (int j = 0; j < Vcount; j++) {
                if (levels[j] == i) {
                    cout << "\t" << array[j].vertex << "\t";
                }
            …2240 tokens truncated….begin();
                it != array[nextNode].Neighbors.end(); ++it) {
                int v = it->index;
                float weight = it->weight.NonIdealtime();

                if (!visited[v] && distance[nextNode] + weight < distance[v]) {
                    distance[v] = distance[nextNode] + weight;
                    indexes[v] = nextNode;
                    pq.push({ distance[v], v });
                }
            }
        }

        if (distance[b] == 1000000000) {

            return temp;
        }

        int current = b;
        int path[size];
        int count = 0;
        while (current != -1) {
            path[count] = current;
            count++;
            current = indexes[current];
        }

        for (int i = count - 1; i >= 0; i--) {
            int nodeIndex = path[i];
            temp.push_back(array[nodeIndex].vertex);
        }
        return temp;
    }

    void shortest_Path_btw2_vericex(t data, t data2) {

        int a = getIndex(data); 
        int b = getIndex(data2);
        float distance[size];
        bool visited[size];
        int indexes[size];
        for (int i = 0; i < size; i++) {

            distance[i] = 1000000000;
            visited[i] = false;
            indexes[i] = -1;
        }

        distance[a] = 0;

        priority_queue<pair<float, int>, vector<pair<float, int>>,
            greater<pair<float, int>>> pq;
        pq.push({ 0, a });

        while (!pq.empty()) {
            float dist = pq.top().first;
            int nextNode = pq.top().second;
            pq.pop();

            if (visited[nextNode]) continue;
            visited[nextNode] = true;

            for (auto it = array[nextNode].Neighbors.begin();
                it != array[nextNode].Neighbors.end(); ++it) {
                int v = it->index;
                float weight = it->weight.NonIdealtime();

                if (!visited[v] && distance[nextNode] + weight < distance[v]) {
                    distance[v] = distance[nextNode] + weight;
                    indexes[v] = nextNode;
                    pq.push({ distance[v], v });
                }
            }
        }

        if (distance[b] == 1000000000) {
            cout << "No path exists\n";
            return; 
        }

        int current = b;
        int path[size];
        int count = 0;
        while (current != -1) {
            path[count] = current;
            count++;
            current = indexes[current];
        }
        for (int i = count - 1; i >= 0; i--) {
            int nodeIndex = path[i];
            cout << array[nodeIndex].vertex << "\t";
        }
        cout << "\nTotal Travel Cost: " << distance[b] << " units" << endl;
    }

    bool searchVertex(t data) { return getIndex(data) != -1; }

    int getDegree(t data) {
        int a = getIndex(data);
        if (a == -1) {
            cout << "\nVertex does not exist \n";
            return -1;
        } 
        int degree =
            0; 
        degree = array[a].Neighbors.size();
        cout << "\nThe degree of the vertex " << data << " is " << degree << endl;
        return degree;
    }

    void Type() {
        if (directed) {
            cout << "\nThe graph is Directed\n";
        }
        else {
            cout << "\nThe graph is Undirected\n";
        }
    }

    string display_edge_of_index(string s) {
        string x = "";
        int index = getIndex(s);
        if (index == -1) {
            cout << "\nCity not found.\n";
            return x;
        } // Safety
        typename list<weighted>::iterator temp = array[index].Neighbors.begin();
        x += "\nThe vertex ";
        x += array[index].vertex + " has links to \n";
        while (temp != array[index].Neighbors.end()) {
            x += array[temp->index].vertex + "\t";
            x += "length = " + to_string(temp->weight.length) + "\n";
            x += "Current Vehicles = " + to_string(temp->weight.currentVehicles) +
                "\n";
            x += "Signal State = " + to_string(temp->weight.signalState) + "\n";
            x += "Congestion = " + to_string(temp->weight.Congestion()) + "\n";
            temp++;
        }
        return x;
    }
    void Incoming(t target) {
        if (!directed) {
            return;
        }
        int targetIdx = getIndex(target);
        if (targetIdx == -1)
            return;

        cout << "Incoming flights to " << target << ":" << endl;
        for (int i = 0; i < Vcount; i++) {
            typename list<weighted>::iterator temp = array[i].Neighbors.begin();
            while (temp != array[i].Neighbors.end()) {
                if (temp->index == targetIdx) {
                    cout << array[i].vertex << "\t";
                }
                temp++;
            }
        }
    }

    RoadDetails& getEdgeDetails(t data, t data1) {
        int a = getIndex(data);
        int b = getIndex(data1);
        if (a == -1 || b == -1) { 
            throw std::runtime_error("Edge not found: invalid vertex");
        }

        typename list<weighted>::iterator temp = array[a].Neighbors.begin();
        while (temp != array[a].Neighbors.end()) {
            if (temp->index == b) {
                return temp->weight;
            }
            temp++;
        }
        throw std::runtime_error("Edge not found");
    }

    list<RoadDetails*> getEdges(t data, list<RoadDetails*> edges) {

        int index = getIndex(data);
        if (index == -1) {
            return edges;
        }
        for (int i = 0; i < Vcount; i++) {
            typename list<weighted>::iterator temp = array[i].Neighbors.begin();
            while (temp != array[i].Neighbors.end()) {
                if (temp->index == index) {
                    edges.push_back(&(temp->weight));
                }
                temp++;
            }
        }
        return edges;
    }

    float AverageRush() {
        float sum = 0;
        int count = 0;

        for (int i = 0; i < Vcount; i++) {
            typename list<weighted>::iterator temp = array[i].Neighbors.begin();
            while (temp != array[i].Neighbors.end()) {

                sum += temp->weight.Congestion();
                count++;
                temp++;
            }
        }

        if (count == 0)
            return 0.0f;
        return sum / count;
    }

    t getVertexAt(int i) { return array[i].vertex; }

    string printGrapgh() {
        string result = "";
        for (int i = 0; i < Vcount; i++) {
            result += display_edge_of_index(array[i].vertex);
        }
        return result;
    }

    double total_System_Cost() {
        double totalCost = 0;
        for (int i = 0; i < Vcount;
            i++) {
            typename list<weighted>::iterator temp = array[i].Neighbors.begin();
            while (temp != array[i].Neighbors.end()) {

                totalCost += temp->weight.choosing();
                temp++;
            }
        }
        return totalCost;
    }


    string printRoadSnapshot() {
        string result = "";
        for (int i = 0; i < Vcount; i++) {
            typename list<weighted>::iterator temp = array[i].Neighbors.begin();
            while (temp != array[i].Neighbors.end()) {
                if (temp->weight.currentVehicles > 0 || temp->weight.queueCount > 0) {
                    result += "  " + array[i].vertex + " -> " + array[temp->index].vertex;
                    result += " | Vehicles: " + to_string(temp->weight.currentVehicles);
                    result += "/" + to_string((int)temp->weight.capacity);
                    result += " | Queue: " + to_string(temp->weight.queueCount);
                    result += " | Congestion: " +
                        to_string((int)(temp->weight.Congestion() * 100)) + "%";
                    result += " | Signal: " +
                        string(temp->weight.signalState ? "GREEN" : "RED");
                    result += "\n";
                }
                temp++;
            }
        }
        return result;
    }
};
