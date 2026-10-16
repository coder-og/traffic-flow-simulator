#include "Simulator.h"
#include <cmath>
#include <stdexcept>
void check(bool ok, const char* message) { if (!ok) throw std::runtime_error(message); }
int main() {
    Graph<std::string, 10> graph(true);
    graph.insertVertex("A"); graph.insertVertex("B"); graph.insertVertex("C");
    graph.makeEdge(0, 1, 10, 10, 5);
    graph.makeEdge(1, 2, 10, 10, 5);
    graph.makeEdge(0, 2, 100, 10, 5);
    auto path = graph.shortest_Path_btw2_vericex_returing_list("A", "C");
    check(path == std::list<std::string>({"A", "B", "C"}), "Dijkstra route");
    check(graph.shortest_Path_btw2_vericex_returing_list("missing", "C").empty(), "Invalid vertex");
    auto& road = graph.getEdgeDetails("A", "B");
    const float free = road.NonIdealtime();
    road.vehicleEntersRoad();
    check(road.NonIdealtime() >= free, "Congestion must not reduce travel time");
    for (int i = 0; i < 20; ++i) road.vehicleEntersRoad();
    check(road.currentVehicles == 5, "Capacity bound");
    TrafficSignal signal;
    check(!signal.canSwitch(0, 0), "Minimum green time");
    signal.Timer(true, 3);
    check(!signal.canSwitch(0, 0), "Empty queues");
    signal.Timer(true, 6);
    check(signal.canSwitch(0, 0), "Maximum green time");
    Simulator<std::string, 100> simulator;
    simulator.setupNetwork();
    check(simulator.getMap()->getVertex() == 11, "Included network has eleven cities");
    std::cout << "PASS: routing, capacity, signal limits, network setup\n";
}
