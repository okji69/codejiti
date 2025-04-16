#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;

const int N = 9;
char maze[N][N];
bool visited[N][N];
int parentX[N][N], parentY[N][N];

int dx[] = {0, 0, 2, -2};
int dy[] = {2, -2, 0, 0};
int mx[] = {1, -1, 0, 0};
int my[] = {0, 0, 1, -1};

void initMaze() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            maze[i][j] = '#';
            visited[i][j] = false;
        }
}

void shuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void dfs(int x, int y) {
    visited[x][y] = true;
    maze[x][y] = '.';

    int dirs[4] = {0, 1, 2, 3};
    shuffle(dirs, 4);

    for (int i = 0; i < 4; i++) {
        int dir = dirs[i];
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx > 0 && ny > 0 && nx < N - 1 && ny < N - 1 && !visited[nx][ny]) {
            maze[x + dx[dir] / 2][y + dy[dir] / 2] = '.';
            dfs(nx, ny);
        }
    }
}

bool bfs(int sx, int sy, int ex, int ey) {
    bool vis[N][N] = {false};
    queue<int> qx, qy;
    qx.push(sx);
    qy.push(sy);
    vis[sx][sy] = true;
    parentX[sx][sy] = -1;
    parentY[sx][sy] = -1;

    while (!qx.empty()) {
        int x = qx.front(); qx.pop();
        int y = qy.front(); qy.pop();

        if (x == ex && y == ey)
            break;

        for (int i = 0; i < 4; i++) {
            int nx = x + mx[i];
            int ny = y + my[i];

            if (nx >= 0 && ny >= 0 && nx < N && ny < N && maze[nx][ny] == '.' && !vis[nx][ny]) {
                qx.push(nx);
                qy.push(ny);
                vis[nx][ny] = true;
                parentX[nx][ny] = x;
                parentY[nx][ny] = y;
            }
        }
    }

    if (!vis[ex][ey]) return false;

    int cx = ex, cy = ey;
    while (cx != -1 && cy != -1) {
        maze[cx][cy] = '*';
        int px = parentX[cx][cy];
        int py = parentY[cx][cy];
        cx = px;
        cy = py;
    }

    return true;
}

void printMaze() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << maze[i][j];
        cout << endl;
    }
}

int main() {
    srand(time(0));
    initMaze();
    dfs(1, 1);

    int startX = 1, startY = 1;
    int endX = N - 2, endY = N - 2;

    cout << "\nGenerated Maze:\n";
    printMaze();

    if (bfs(startX, startY, endX, endY)) {
        cout << "\nPath from START (*) to END (*) marked below:\n";
        printMaze();
    } else {
        cout << "\nNo path found from START to END.\n";
    }

    return 0;
}
