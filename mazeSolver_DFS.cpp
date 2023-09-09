#include <iostream>
#include <vector>
using namespace std;

const int N = 5; // Size of the maze (N x N)
vector<vector<char>> maze(N, vector<char>(N, '0')); // Initialize a 2D maze

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == '0');
}

bool solveMaze(int x, int y) {
    if (x == N - 1 && y == N - 1) {
        maze[x][y] = 'P'; // Mark the exit cell with 'P'
        return true;
    }

    if (isValid(x, y)) {
        maze[x][y] = 'P';

        if (solveMaze(x + 1, y) || solveMaze(x - 1, y) || solveMaze(x, y + 1) || solveMaze(x, y - 1)) {
            return true;
        }

        // If no path is found, backtrack and mark the cell as '0' again
        maze[x][y] = '0';
        return false;
    }

    return false;
}

int main() {
    cout << "Enter the maze (0 for open path, 1 for wall):" << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
        }
    }

    if (solveMaze(0, 0)) {
        cout << "Solved Maze is:" << endl;

        // Print the solved maze
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
