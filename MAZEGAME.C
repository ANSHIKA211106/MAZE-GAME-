#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>   // for getch()

#define SIZE 9       // Maze size

char maze[SIZE][SIZE];
int px = 1, py = 1;   // Player position
int totalMoves = 0;

// DFS generation variables
typedef struct { int x, y; } Position;
Position stack[500];
int top = -1;

// Directions
int dx[] = {-2, 2, 0, 0};
int dy[] = {0, 0, -2, 2};

void push(int x, int y) {
    stack[++top].x = x;
    stack[top].y = y;
}

Position pop() { return stack[top--]; }

void shuffle() {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = dx[i]; dx[i] = dx[r]; dx[r] = temp;
        temp = dy[i]; dy[i] = dy[r]; dy[r] = temp;
    }
}

// Maze generator
void generateMaze() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            maze[i][j] = '#';

    push(1, 1);
    maze[1][1] = 'S';

    while (top != -1) {
        Position current = pop();
        int x = current.x, y = current.y;

        shuffle();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx > 0 && nx < SIZE - 1 && ny > 0 && ny < SIZE - 1 && maze[nx][ny] == '#') {
                maze[nx][ny] = '.';
                maze[(x + nx) / 2][(y + ny) / 2] = '.';
                push(x, y);
                push(nx, ny);
                break;
            }
        }
    }

    maze[SIZE - 2][SIZE - 2] = 'E';  // Exit
}

// Show maze
void printMaze() {
    system("cls"); // clears the screen
    printf("\n--- MAZE GAME (W A S D to move, Reach E to win) ---\n\n");
    printf("Moves: %d\n\n", totalMoves);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == px && j == py)
                printf("P "); // Player
            else
                printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

// Main game loop
int main() {
    srand(time(NULL));
    generateMaze();

    px = 1; py = 1;

    while (1) {
        printMaze();
        printf("\n Random Maze Generator & Escape Game (STACK)\n");
       printf("W=Up | S=Down | A=Left | D=Right | U=Undo\n\n");

        char move = getch();  // read single key

        int newx = px, newy = py;

        if (move == 'w' || move == 'W') newx--;
        if (move == 's' || move == 'S') newx++;
        if (move == 'a' || move == 'A') newy--;
        if (move == 'd' || move == 'D') newy++;

        if (maze[newx][newy] != '#') {
            px = newx;  
            py = newy;
            totalMoves++;
        }

        if (maze[px][py] == 'E') {
            printMaze();
            printf("\n YOU WIN! Total Moves = %d \n", totalMoves);
            break;
        }
    }

    return 0;
}
