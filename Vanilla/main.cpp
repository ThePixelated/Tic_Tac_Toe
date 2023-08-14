#include <iostream>
#include <stdlib.h>
#include <conio.h>

int cursor_axis = 4;     // The cursor coordinate
bool state_move = true;  // the value of state_move determined the Xs and Os

void cursor_movement(int usr_input, char grid[]) {
    if (cursor_axis > 2 && usr_input == int('w') || usr_input == int('W')) {                // Upward movement
        cursor_axis -= 3;
    }
    else if (!(cursor_axis % 3 == 0) && usr_input == int('a') || usr_input == int('A')) {   // Leftward movement
        cursor_axis -= 1;
    }
    else if (cursor_axis < 6 && usr_input == int('s') || usr_input == int('S')) {           // Downward movement
        cursor_axis += 3;
    }
    else if (!((cursor_axis + 1) % 3 == 0) && usr_input == int('d') || usr_input == int('D')) {  // Rightward movement
        cursor_axis += 1;
    }

    if (grid[cursor_axis] == ' ' && (usr_input == 13 || usr_input == 32)) {  // Selecting cell input
        if (state_move) {
            grid[cursor_axis] = 'X';
            state_move = false;
        } else {
            grid[cursor_axis] = 'O';
            state_move = true;
        }
    }
}

// Displaying the whole ui
// -----------------------
void DisplayGrid(char grid[]) {
    bool stepped_text_box = true;  // stepped_text_box is making sure that the text "Current box type" is not
    char cursor = 177;             // get printed everytime and only once

    std::cout << "=================\n";
    for (int i = 0; i < 9; i++) {
        if (i == cursor_axis) std::cout << "|| " << cursor << " ";
        else std::cout << "|| " << grid[i] << " ";

        // Column devided
        if (i > 0 && ((i + 1) % 3) == 0) {
            std::cout << "||";

            if (stepped_text_box) {
                std::cout << "  Current box type:\n";
            } else std::cout << "\n";

            if (i < 8) std::cout << "-----------------";

            if (stepped_text_box) {
                stepped_text_box = false;
                std::cout << "          " << grid[cursor_axis] << '\n';
            } else if (!stepped_text_box && i < 8) std::cout << "\n";
        }
    } std::cout << "=================\n";
}

// Tile Check
// ----------
int empty_check(char grid[]) {  // Checking if the board is still empty or not, then decide whether is draw or not
    bool empty_grid = false;

    for (int i = 0; i < 9; i++) {
        if (grid[i] == ' ') {
            empty_grid = true;
            return -2;
        }
    }

    if (!empty_grid) return -1;

    return -2;
}

int win_check(char grid[]) {  // Checking is there any win chance 
    // Horizontal Check [Checking each columns]
    for (int i = 0; i < 7; i += 3) {
        if (grid[i] != ' ' && (grid[i] == grid[i + 1]) && (grid[i + 1] == grid[i + 2])) {
            if (grid[i] == 'X') return 1;
            else return 0;
        }
    }

    // Vertical Check [Checking each rows]
    for (int i = 0; i < 3; i++) {
        if (grid[i] != ' ' && (grid[i] == grid[i + 3]) && (grid[i + 3] == grid[i + 6])) {
            if (grid[i] == 'X') return 1;
            else return 0;
        }
    }

    // Diagonal Check [Checking all the possibility of diagonal move]
    for (int i = 0; i < 3; i += 2) {
        int temp;
        (i ? temp = 2 : temp = 4);

        // Combine cross check
        if (grid[i] != ' ' && (grid[i] == grid[i + temp]) && (grid[i + temp] == grid[i + temp * 2])) {
            if (grid[i] == 'X') return 1;
            else return 0;
        }
    }

    return -2;
}

int tile_check(char grid[]) {  // Checking the status of the board
    int temp = win_check(grid);
    if (temp == 0 || temp == 1) return temp;
    else if (empty_check(grid) == -1) return -1;

    return -2;
}

// Generating the board
// --------------------
char* generate_grid() {
    char* grid = new char[9];

    for (int i = 0; i < 9; i++) grid[i] = ' ';

    return grid;
}

int main() {
    char* grid = generate_grid();
    system("cls");

    while (true) {
        DisplayGrid(grid);

        int usr_input = getch();
        if (usr_input == int('e') || usr_input == int('E')) break;

        cursor_movement(usr_input, grid);
        int check_sys = tile_check(grid);

        switch (check_sys) {  // Board check
            case -1: 
                std::cout << "  It's a draw !!\n ";
                return 0;
            case 0: 
                std::cout << "  Player O WIN!!\n ";
                return 0;
            case 1: 
                std::cout << "  Player X WIN!!\n ";
                return 0;
        }
        
        system("cls");
    }

    return 0;
}