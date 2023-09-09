#include <iostream>
#include <vector>
#include <queue>
#include<limits.h>
using namespace std;

const int N = 5; // Size of the maze (N x N)
vector<vector<char>> maze(N, vector<char>(N, '0')); // Initialize a 2D maze

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == '0');
}

void findShortestPath(int startX, int startY) {
    vector<vector<int>> distance(N, vector<int>(N, INT_MAX)); // Initialize distance array with a large value
    queue<pair<int, int>> q; // Initialize a queue for BFS

    int dx[] = {1, -1, 0, 0}; // Possible movements in x direction
    int dy[] = {0, 0, 1, -1}; // Possible movements in y direction

    q.push({startX, startY});
    distance[startX][startY] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY) && distance[newX][newY] == INT_MAX) {
                distance[newX][newY] = distance[x][y] + 1;
                q.push({newX, newY});
            }
        }
    }

        
    // Trace back the path and mark with "P"
    int x = 0, y = 0;
    while (x != startX || y != startY) {
        bool found = false;  // Add a flag to check if a valid move is found
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY) && distance[newX][newY] == distance[x][y] - 1) {
                x = newX;
                y = newY;
                maze[x][y] = 'P';
                found = true;  // Valid move found
                break;
            }
        }
        
        // If no valid move is found, mark the cell with "-"
        if (!found) {
            maze[x][y] = '-';
            break;
        }
    }

    // ...
    // Print the maze with the path
    cout << "Solved Maze is:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Enter the maze (0 for open path, 1 for wall):" << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
        }
    }

    findShortestPath(N - 1, N - 1); // End position is (N-1, N-1)

    return 0;
}
