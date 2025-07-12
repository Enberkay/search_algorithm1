# Search Algorithms - Complete Collection

This repository contains implementations of various search algorithms categorized into two main types: **Uninformed Search** and **Informed Search**.

## Repository Structure

```
search_algorithm1/
├── README.md                    # Comprehensive overview
├── uninformed_search/           # 6 blind search algorithms
│   ├── linear_search.cpp
│   ├── binary_search.cpp
│   ├── breadth_first_search.cpp
│   ├── depth_first_search.cpp
│   ├── uniform_const_search.cpp
│   └── iterative_deepening_depth_first_search.cpp
└── informed_search/             # 4 heuristic search algorithms
    ├── a_star_search.cpp
    ├── greedy_best_first_search.cpp
    ├── bidirectional_search.cpp
    └── ida_star_search.cpp
```

## Algorithm Categories

### 1. Uninformed Search (Blind Search)
Algorithms that do not use any heuristic or prior knowledge about the problem structure. They explore the search space systematically without any guidance.

**Location**: `uninformed_search/` folder

#### Array Search Algorithms
| Algorithm | File | Description | Time Complexity | Best For |
|-----------|------|-------------|-----------------|----------|
| Linear Search | `linear_search.cpp` | Searches array sequentially from left to right | O(n) | Unsorted arrays |
| Binary Search | `binary_search.cpp` | Divides array in half repeatedly | O(log n) | Sorted arrays |

#### Graph/Tree Search Algorithms
| Algorithm | File | Description | Time Complexity | Best For |
|-----------|------|-------------|-----------------|----------|
| Breadth-First Search (BFS) | `breadth_first_search.cpp` | Explores level by level using queue | O(V + E) | Shortest path (unweighted) |
| Depth-First Search (DFS) | `depth_first_search.cpp` | Explores deep paths using recursion/stack | O(V + E) | Complete exploration, cycle detection |
| Uniform Cost Search (UCS) | `uniform_const_search.cpp` | BFS with weighted edges using priority queue | O(E log V) | Shortest path (weighted) |
| Iterative Deepening DFS (IDS) | `iterative_deepening_depth_first_search.cpp` | DFS with increasing depth limits | O(b^d) | Memory-efficient shortest path |

### 2. Informed Search (Heuristic Search)
Algorithms that use heuristic functions to guide the search towards the goal more efficiently.

**Location**: `informed_search/` folder

| Algorithm | File | Description | Time Complexity | Best For |
|-----------|------|-------------|-----------------|----------|
| A* Search | `a_star_search.cpp` | Uses f(n) = g(n) + h(n) with priority queue | O(E log V) | Optimal path finding |
| Greedy Best-First Search | `greedy_best_first_search.cpp` | Uses only heuristic h(n) | O(E log V) | Fast but not always optimal |
| Bidirectional Search | `bidirectional_search.cpp` | Searches from both start and goal | O(b^(d/2)) | Faster than unidirectional |
| IDA* Search | `ida_star_search.cpp` | A* with iterative deepening | O(b^d) | Memory-efficient A* |

## Key Differences

### Uninformed vs Informed Search

| Aspect | Uninformed Search | Informed Search |
|--------|-------------------|-----------------|
| **Heuristic Usage** | No heuristic function | Uses heuristic h(n) |
| **Search Efficiency** | Systematic but may be slow | Guided and typically faster |
| **Optimality** | May not find optimal path | Often finds optimal path |
| **Memory Usage** | Varies by algorithm | Generally higher |
| **Implementation** | Simpler to implement | More complex with heuristics |

### Array vs Graph Search

| Type | Data Structure | Algorithms | Use Cases |
|------|----------------|------------|----------|
| **Array Search** | Linear data structures | Linear, Binary | Database queries, list operations |
| **Graph Search** | Connected nodes/vertices | BFS, DFS, A*, etc. | Pathfinding, AI, network analysis |

## Algorithm Selection Guide

### For Array Operations
- **Unsorted array**: Use Linear Search
- **Sorted array**: Use Binary Search (much faster)

### For Graph Problems
- **Shortest path (unweighted)**: Use BFS
- **Complete exploration**: Use DFS
- **Shortest path (weighted)**: Use UCS or A*
- **Memory constraints**: Use IDS or IDA*
- **Bidirectional search**: Use Bidirectional Search

### For AI/Game Problems
- **Pathfinding with heuristics**: Use A*
- **Fast but approximate**: Use Greedy Best-First
- **Memory-efficient optimal**: Use IDA*

## Complexity Analysis

### Time Complexity
| Algorithm | Best Case | Average Case | Worst Case |
|-----------|-----------|--------------|------------|
| Linear Search | O(1) | O(n) | O(n) |
| Binary Search | O(1) | O(log n) | O(log n) |
| BFS | O(1) | O(V + E) | O(V + E) |
| DFS | O(1) | O(V + E) | O(V + E) |
| UCS | O(1) | O(E log V) | O(E log V) |
| A* | O(1) | O(E log V) | O(E log V) |

### Space Complexity
| Algorithm | Space Complexity | Notes |
|-----------|------------------|-------|
| Linear Search | O(1) | Constant extra space |
| Binary Search | O(1) | Constant extra space |
| BFS | O(V) | Queue size |
| DFS | O(V) | Stack/recursion depth |
| UCS | O(V) | Priority queue |
| A* | O(V) | Priority queue |

## Implementation Notes

### Common Data Structures Used
- **Queue**: BFS, Bidirectional Search
- **Stack/Recursion**: DFS, IDS
- **Priority Queue**: UCS, A*, Greedy Best-First
- **Hash Set/Array**: Visited tracking

### Key Concepts
- **Heuristic Function h(n)**: Estimates distance to goal
- **Cost Function g(n)**: Actual cost from start to current node
- **Evaluation Function f(n)**: f(n) = g(n) + h(n) for A*
- **Admissible Heuristic**: Never overestimates true cost
- **Consistent Heuristic**: h(n) ≤ cost(n,n') + h(n') for all neighbors

## Usage Examples

Each algorithm file contains:
- Complete C++ implementation
- Detailed comments explaining the logic
- Example usage with sample data
- Complexity analysis
- Comparison with other algorithms

## Compilation and Running

All files are written in C++ and can be compiled using:
```bash
# For uninformed search algorithms
cd uninformed_search
g++ -o algorithm_name algorithm_name.cpp
./algorithm_name

# For informed search algorithms
cd informed_search
g++ -o algorithm_name algorithm_name.cpp
./algorithm_name
```

## Contributing

Feel free to add more search algorithms or improve existing implementations. Please maintain the same documentation style and include complexity analysis.

## Navigation

- **Uninformed Search Algorithms**: See `uninformed_search/` folder
- **Informed Search Algorithms**: See `informed_search/` folder
- **Main README**: This file provides overview and comparisons

