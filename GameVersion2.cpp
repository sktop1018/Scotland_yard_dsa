#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib> // For system command
#include <thread>  // For sleep_for
#include <chrono>  // For chrono::milliseconds

using namespace std;

int mrx;
vector<int> detective(3); // Detective vertices
int n = 50;
const int INF = numeric_limits<int>::max();
int TICKETS = 12;
int REVEAL = 4;
vector<vector<int>> graph(n); // Graph
vector<int> degree(n);
vector<int> mrxmoves;

struct tickets { // Tickets structure
    int taxi = TICKETS;
    int bus = 0;
    int subway = 0;
} Detective[3];

void show_tickets(int i) {
    cout << "Tickets : " << Detective[i].taxi << endl;
}

void turn(int i) {
    Detective[i].taxi--;
    return;
}

int findDistance(int start, int end) {
    if (start == end)
        return 0;
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), -1); // Initialize all distances to -1
    queue<int> q;

    q.push(start);
    visited[start] = true;
    distance[start] = 0;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        if (currentNode == end) {
            return distance[currentNode];
        }

        for (int neighbor : graph[currentNode]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
                distance[neighbor] = distance[currentNode] + 1;
            }
        }
    }
    return -1;
}

void MrX_Decisions() {
    float disAvg = 0;
    int bestNext = -1;
    float maxDisAvg = -1;

    for (int x : graph[mrx]) {
        disAvg = (findDistance(x, detective[0]) + findDistance(x, detective[1]) + findDistance(x, detective[2])) / 3.0;
        if (disAvg > maxDisAvg) {
            maxDisAvg = disAvg;
            bestNext = x;
        }
    }

    if (bestNext != -1) {
        mrx = bestNext;
    }
    mrxmoves.push_back(mrx);
    return;
}

void make_graph() {
    // Create an initial fully connected subgraph for the first few nodes (ensuring connectivity)
    for (int i = 0; i < 3; i++) {
        degree[i] = 3; // Start with a higher degree for these nodes
        for (int j = 0; j < 3; j++) {
            if (i != j) {
                graph[i].push_back(j); // Connect the first 3 nodes to each other
                degree[j]++;
            }
        }
    }

    // Now connect the rest of the nodes
    int r1, r2;
    for (int i = 3; i < n; i++) {
        retry:
        // Randomly choose two nodes to connect
        r1 = rand() % i;
        r2 = rand() % i;

        // Ensure that both nodes have less than the max degree of 4 and are not the same node
        if (degree[r1] > 4 || degree[r2] > 4 || r1 == r2)
            goto retry;

        // Add the connection to the graph
        degree[i] = 2;
        degree[r1]++;
        degree[r2]++;

        graph[i].push_back(r1);
        graph[i].push_back(r2);
        graph[r1].push_back(i);
        graph[r2].push_back(i);
    }
    return;
}


void print_graph() {
    for (int i = 0; i < n; i++) {
        cout << "FOR VERTEX " << i << " : ";
        for (int neighbor : graph[i])
            cout << neighbor << " ";
        cout << endl;
    }
}

int caught() {
    return (mrx == detective[0] || mrx == detective[1] || mrx == detective[2]);
}

void log_detective_positions() {
    ofstream outfile("detective_positions.txt");
    if (outfile.is_open()) {
        // outfile << "Detective: ";
        for (int i = 0; i < 3; i++) {
            outfile << detective[i] << " ";  // Write the detective positions
        }
        outfile.close();
    }
}

void log_mrx_position() {
    ofstream outfile("mrx_position.txt");
    if (outfile.is_open()) {
        // outfile << "Detective: ";
        outfile << mrx;  // Write the detective positions
        outfile.close();
    }
}
void make_move() {
    int t;
    for (int i = 0; i < 3; i++) {
        cout << "POSSIBLE MOVES for " << i << " : ";
        for (int nei : graph[detective[i]])
            cout << " " << nei;
        cout << endl;
        t = detective[i];
        show_tickets(i);
        cout << "Your Move : ";
        again:
        cin >> detective[i];
        if (find(graph[t].begin(), graph[t].end(), detective[i]) == graph[t].end()) {
            cout << "Taxi doesn't go to " << detective[i] << ". Try again : ";
            goto again;
        }
        log_detective_positions();
        turn(i);
    }
}

void log_positions() {
    ofstream outfile("positions.txt");
    if (outfile.is_open()) {
        outfile << mrx << endl;  // MrX position (if needed)
        for (int i = 0; i < 3; i++) {
            outfile << detective[i] << " ";
        }
        outfile << endl;

        // Output the graph structure (nodes and edges)
        for (int i = 0; i < n; i++) {
            outfile << i << ": ";
            for (int neighbor : graph[i]) {
                outfile << neighbor << " ";
            }
            outfile << endl;
        }
        outfile.close();
    }
}

void save_graph_to_file() {
    ofstream outfile("graph_data.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < n; i++) {
            outfile << i << ": ";
            for (int neighbor : graph[i]) {
                outfile << neighbor << " ";
            }
            outfile << endl;
        }
        outfile.close();
    }
}


int main() {
    ofstream mrxposition("mrx_position.txt");
    int flag = 0;
    ofstream resultFile("game_result.txt");
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "WELCOME TO SCOTLAND YARD GAME !!!" << endl;
    cout << "You along with 2 other detectives are on a mission to find Mr. X." << endl;

    make_graph();
    save_graph_to_file();
    print_graph();

    for (int i = 0; i < 3; i++) {
        bool uniquePosition = false;
        while (!uniquePosition) {
            detective[i] = rand() % 50; // Assign a random position
            uniquePosition = true;

            // Check if the position is already occupied by any other detective
            for (int j = 0; j < i; j++) {
                if (detective[i] == detective[j]) {
                    uniquePosition = false;
                    break;
                }
            }
        }
        cout << "Starting Position of Detective " << i << " : " << detective[i] << endl;
    }


    log_detective_positions();  // Log detective positions to file

    mrx = rand() % 50;
    mrxmoves.push_back(mrx);

    // Launch Python Graphics
    std::system("python3 graphics.py &");

    log_positions();

    while (Detective[0].taxi > 0) {
        if (Detective[0].taxi % REVEAL == 0 && Detective[0].taxi != TICKETS){
            log_mrx_position();
            cout << "Alert! Mr. X has been located at: " << mrx << endl;
        }
        make_move();
        log_positions();

        if (caught()) {
            flag = 1;
            cout << "Congratulations! You caught Mr. X" << endl;
            resultFile << "Mr. X was caught!" << endl;
            break;
        }

        MrX_Decisions();
        log_positions();
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Pause to sync with graphics
    }

    if (!flag) {
        cout << "Mr. X escaped!" << endl;
        resultFile << "Mr. X escaped!" << endl;
    }

    cout << "Mr. X's Moves: ";
    for (size_t i = 0; i < mrxmoves.size(); i++)
        cout << (i > 0 ? " -> " : "") << mrxmoves[i];
    cout << endl;

    return 0;
}
