# Traffic Flow Simulator

C++17 teaching simulator with a raylib dashboard. It models an abstract directed network of eleven Pakistani cities, congestion-dependent road costs, Dijkstra routing, vehicle queues and adaptive signals. City labels are illustrative; this is not a calibrated real-world transport model.

## Build and run

Requirements: C++17 compiler, CMake 3.16+, and **raylib 5.5** installed with its CMake package. `packages.config` records the original raylib 5.5 NuGet dependency for Visual Studio. The portable CMake target avoids machine-specific IDE paths.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
mkdir -p run
cd run
../build/traffic_simulator
```

For a Visual Studio multi-configuration build use `..\build\Release\traffic_simulator.exe`. If CMake cannot find raylib, pass `-Draylib_DIR=/path/to/raylib/lib/cmake/raylib`. Build raylib from its official source if a package is unavailable: https://github.com/raysan5/raylib/tree/5.5

The actual entry point is **`Graphics.cpp`**. `Project_DSA.cpp` contains commented-out code. The dashboard starts full-screen; Escape closes it. Outputs are written to the current directory, so a separate `run/` directory preserves the historical sample logs in the repository.

## Code map

| File | Role |
|---|---|
| `Graph.h` | Adjacency lists, weighted routing, graph utilities |
| `RoadDetails.h` | Capacity, queues and BPR-style travel cost |
| `TrafficSignal.h` | Minimum/maximum green time and switching decisions |
| `vehicle.h` | Vehicle route, current road, travel state |
| `Manger.h` | Movement, rerouting, signals and metrics (`Manager` class) |
| `Simulator.h` | Builds the eleven-city network and initial traffic |
| `Graphics.cpp` | Dashboard and graphical simulation loop |

Road travel cost is `(length / max_speed) * (1 + a * (vehicles / capacity)^b)`.
Signals consider queue/congestion cost and waiting time. This is a heuristic; no globally optimal traffic solution is claimed.

## Scenario and output

`Simulator::addMassiveTraffic()` currently creates **50,000** randomized vehicles using a time-based seed. Its old console labels mentioning 10,000/3,500 are stale. For a smaller demonstration, change that loop bound. The GUI injects extra traffic every 50 ticks until tick 1500. Network parameters are source constants; `map.txt` is output, not an input map.

Outputs: `metrics.csv`, `performance_metrics.txt`, `car_timings.txt`, `map.txt`. Existing committed outputs are historical samples; they are not a benchmark for the current default. In particular, the earlier 30-vehicle README results cannot be reproduced from the current default configuration.

## Tests

No raylib/display is needed for core checks:

```sh
cmake -S . -B build-core -DBUILD_GUI=OFF
cmake --build build-core
ctest --test-dir build-core --output-on-failure
```

Checks cover a known shortest path, invalid vertex handling, road capacity, signal timing and the included network. CI also builds the GUI against raylib 5.5. These checks do not establish that every vehicle completes a heavy simulation.

## Current limitations

- The GUI advances travel time by 0.1 per tick; the alternate `Manager::physics()` uses 2.0, while several output labels say ticks. Compare only runs with the same execution path; do not treat these as measured real-world times.
- The network currently has duplicate parallel links for several city pairs, while `getEdgeDetails()` returns the first matching link. Edge identity needs redesign before treating parallel-route metrics as reliable.
- Route recalculation and queue accounting need broader end-to-end stress tests. The current tests cover components, not a correctness proof of the traffic model.
- The random scenario is not seeded for reproducible benchmark comparison, and the GUI has no fixed maximum duration.

The included report files describe the coursework. Add a recording and seeded experiment results after validating the scenario. No license has been selected for the repository.
