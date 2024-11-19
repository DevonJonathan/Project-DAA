# Dijkstra Algorithm For Vehicle Navigation By Considering Intersection

## Overview
This project is about creating a simple vehicle navigation system using **Dijkstra's Algorithm**. The main idea is to find the shortest route between two intersections, while taking into account both the distance and the time it takes to get through intersections. We use a dataset that has different intersection points with their coordinates (latitude and longitude). The system works by building a graph of these intersections, which makes the route calculation realistic and efficient.

The graph is made up of intersections as **nodes** and roads between them as **edges**. Unlike the usual shortest path algorithms, this project adds an **intersection cost** to simulate the effect of going through intersections, making the estimated travel times more accurate.

## Features
- **Dataset Loading**: Loads data from a CSV file (`Intersection_Points_Final.csv`). Each data point is an intersection with details like latitude, longitude, and the location name.
- **Graph Representation**: Uses an adjacency list to represent the graph, where nodes are connected based on how close they are (e.g., less than 2 km away).
- **Dijkstra's Algorithm**: Finds the shortest path between two places, considering both the travel distance and the time spent at intersections.
- **Interactive Input**: Users can type in starting and ending locations, and the program will find the shortest route.
- **Output Details**:
  - **Shortest Distance**: Shows the calculated distance between the start and end points.
  - **Number of Intersections**: Displays how many intersections are passed.
  - **Estimated Travel Time**: Calculates the travel time based on road distances and time at intersections.
  - **Route Details**: Prints out the route step-by-step with location names.

## Algorithm Overview
The algorithm uses **Dijkstra's shortest path** approach, with a few extra features:
- The **nodes** are intersections, and the **edges** are roads between them.
- A **cost per intersection** is added to simulate the time it takes for a car to go through an intersection.
- The **distance** between nodes is calculated using an approximation based on latitude and longitude.

The graph is built using an **unordered map** of adjacency lists, and a **priority queue** helps find the next closest node to visit.

The time complexity of Dijkstra's algorithm in this project is **O((V + E) log V)**, where **V** is the number of intersections (nodes) and **E** is the number of roads (edges). This is because of the use of a priority queue for efficient selection of nodes.

## How to Run
1. **Prerequisites**: Make sure you have a C++ compiler like GCC installed.
2. **Dataset**: Put `Intersection_Points_Final.csv` in the root folder.
3. **Compile and Run**:
   ```sh
   g++ -o vehicle_navigation vehicle_navigation.cpp
   ./vehicle_navigation
   ```
4. **User Input**: Enter the starting and destination locations.

## Example Usage
```
Enter starting location: Main Street
Enter destination location: Central Park

Starting Location: Main Street
Destination Location: Central Park
Shortest Distance: 3.45 km
Number of intersections passed: 5
Travel Time: 15 minutes
Route: Node 0 (Main Street) -> Node 2 (First Avenue) -> Node 5 (Central Park)
```
To see the details about the street's names please visit [https://opendata.newwestcity.ca/datasets/newwestcity::intersection-points/about](https://opendata.newwestcity.ca/datasets/newwestcity::intersection-points/explore?location=49.204174%2C-122.878729%2C13.03&showTable=true)

 
---

Thanks for checking out this project! We hope it helps you learn more about graph algorithms and vehicle routing in a practical way.

