#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <ctime>
using namespace std;

int N; // Size of the maze (N x N)
vector<vector<char>> maze;

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] != '1');
}

void generateRandomMaze() {
    maze = vector<vector<char>>(N, vector<char>(N, '0'));
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int random =rand()%2;
            maze[i][j]=(random==0)?'0':'1';
            }
        }
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
        bool found = false;
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY) && distance[newX][newY] == distance[x][y] - 1) {
                x = newX;
                y = newY;
                maze[x][y] = 'P';
                found = true;
                break;
            }
        }

        // If no valid move is found, mark the cell with "-"
        if (!found) {
            break;
        }
    }

    // Mark walls with "-"
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (maze[i][j] == '1' || maze[i][j] == '0') {
                maze[i][j] = '-';
            }
        }
    }

    // Print the maze with the path
    cout << "Solved Maze is:" << endl;
    maze[0][0] = 'P';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    cout << "Enter 0 to generate a random maze, or 1 to input the maze manually: ";
    int choice;
    cin >> choice;

    if (choice == 0) {
        cout << "Enter the size of the maze (N): ";
        cin >> N;
        generateRandomMaze();
    } else if (choice == 1) {
        cout << "Enter the size of the maze (N): ";
        cin >> N;
        maze = vector<vector<char>>(N, vector<char>(N, '0'));

        cout << "Enter the maze (0 for open path, 1 for wall):" << endl;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> maze[i][j];
            }
        }
    }

    findShortestPath(N - 1, N - 1);

    return 0;
}
