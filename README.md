# Scotland-Yard

# **Scotland Yard Game**

A digital recreation of the classic detective game **Scotland Yard**, featuring a graphical interface powered by **Python (Pygame)** and game logic implemented in **C++**. This project demonstrates the integration of Python and C++ using file-based communication for real-time updates.

---
![scyard](https://github.com/user-attachments/assets/d3f4d7a2-ecc9-44d2-b8d7-eea29316b8f5)


## **Features**
- 🎨 **Graphical Map Interface**:
  - Nodes represent locations on the map.
  - Edges denote possible paths between locations.
  - Dynamic player position visualization.
- 🕵️ **Detectives vs. Mr. X**:
  - Mr. X moves stealthily across the map.
  - Detectives collaborate to catch Mr. X.
- 🔄 **Real-Time Updates**:
  - Python and C++ interact through shared files to synchronize game state.
- 📂 **Customizable Graph**:
  - Easily modify the game map by updating the graph structure.

---

## **Tech Stack**
### **1. Python (Pygame)**:
- Responsible for:
  - Rendering the map, nodes, edges, and player movements.
  - Displaying the game's outcome.

### **2. C++**:
- Implements:
  - Game rules and logic.
  - Movement updates for Mr. X and detectives.
  - Winning conditions.

### **3. File Communication**:
- Shared files enable Python and C++ to exchange data seamlessly.

---

## **Setup and Installation**
### **Prerequisites**:
- Python 3.8+ with **Pygame** installed.
- C++ compiler (e.g., g++).
- Required project files:
  - `positions.txt`, `detective_positions.txt`, `mrx_position.txt`, `game_result.txt`.

### **Steps**:
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/scotland-yard
   cd scotland-yard

2. Install the dependencies:
   ```bash
   pip install pygame

3. Compile:
   ```bash
   g++ -o game GameVersion2.cpp

4. Run:
   ```bash
   ./game
