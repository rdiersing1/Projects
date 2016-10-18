#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>

using namespace std;

const bool CLEAR_SCREEN = true;
const int PLAYER1 = 0;
const int PLAYER2 = 1;
const int TOTAL_SHIPS = 5;
const int SUPER_WEPONS = 2;
const int ATOM_BOMB = 8;
const int MACHEEN_GUN = 4;
const int TORPEDO = 6;
const int RADAR = 3;
const int SEA_MINE = 7;

void clearScreen() {
	cout << flush;
	system("CLS");

    return;
}

string stoupper(string &s) {
    //cout << "To upper entered. " << endl;
    for (unsigned int i = 0; i < s.size(); ++i) {
        s.at(i) = toupper(s.at(i));
    }
    //cout << "To upper works string is " << s << endl;
    return s;
}

string printIntro() {
    string cont;
    cout << "Wellcome to Battleship" << endl;
    cout << "Main Menu" << endl << endl;
    cout << "Press Enter to continue " << endl;
    cout << "Press o and then Enter for options" << endl;
    getline(cin, cont);
    clearScreen();
    return cont;
}

string opt() {
    string ans;
    cout << "Which gamemode would you like to play? " << endl 
    << "(type the nuber 1, 2, or 3 followed by pressing the enter key to answer) "<< endl
    << endl << "1. The normal gamemode. " << endl
    << "2. Salvo mode: You have as many attacks per turn as ships you have left. " << endl
    << "3. Superwepons mode: very very fun :D. (dosen't work yet)." << endl << endl;
    getline(cin, ans);
    return ans;
}

bool validPlacementShip(string ship, int size, const vector <char> &board){
    int coord1 = 0;
    int coord2 = 0;
    
    if (ship.size() == 5) {
    coord1 = (static_cast<int>(ship.at(0) - 'A') * 9) + (ship.at(1) - '0') - 1;
    coord2 = (static_cast<int>(ship.at(3) - 'A') * 9) + (ship.at(4) - '0') - 1;
    // cout << (coord2 - coord1) << endl;
    
        if (ship.at(0) >= 'A' &&  ship.at(0) <= 'I' && ship.at(1) >= '1'
        && ship.at(1) <= '9' && ship.at(2) == ' ' && ship.at(3) >= 'A' &&  ship.at(3) <= 'I' &&
        ship.at(4) >= '1' && ship.at(4) <= '9') {
            if (ship.at(0) == ship.at(3)) {
                if ((coord2 - coord1) != size - 1) {
                    // cout << '1';
                    return false;
                }
                
                if (ship.at(1) > ship.at(4)) {
                    for (unsigned int i = 0; i <= coord1 - coord2; ++i) {
                        if (board.at(coord2 + i) != ' ') {
                            // cout << '2';
                            return false;
                        }
                    }
                    return true;
                }
                if (ship.at(4) > ship.at(1)) {
                    for (unsigned int i = 0; i <= coord2 - coord1; ++i) {
                        if (board.at(coord1 + i) != ' ') {
                            // cout << '3';
                            return false;
                        }
                    }
                    return true;
                }
            }
            else if(ship.at(1) == ship.at(4)) {
                // cout <<'9';
                if (static_cast<int>(ship.at(3)) - static_cast<int>(ship.at(0)) != size - 1) {
                    // cout << '8';
                    return false;
                }
                if (ship.at(0) > ship.at(3)) {
                    for (unsigned int i = 0; i <= coord1 - coord2; i+=9) {
                        if (board.at(coord2 + i) != ' ') {
                            // cout << '4';
                            return false;
                        }
                    }
                    return true;
                }
                if (ship.at(3) > ship.at(0)) {
                    for (unsigned int i = 0; i <= coord2 - coord1; i+=9) {
                        if (board.at(coord1 + i) != ' ') {
                            // cout << '5';
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
    }
    // cout <<'6';
    return false;
}

void drawBoard(const vector <char> &board) {
    
    cout << "    1   2   3   4   5   6   7   8   9" << endl
    << "  |---|---|---|---|---|---|---|---|---|" << endl;
    
    for(unsigned int i = 0; i < 9; ++i) {
        
        cout << static_cast <char> ('A' + i);
        
        for(unsigned int j = 0; j < 9; ++j) {
            cout << " | " << board.at((i * 9 ) + j);
        }
        cout << " | ";
        cout << endl;
        cout << "  |---|---|---|---|---|---|---|---|---|" << endl;
    }
    
    
    return;
}

void drawShip(vector <char> &board, string ship, vector <int> &vships) {
    int coord1 = 0;
    int coord2 = 0;
    
    coord1 = (static_cast<int>(ship.at(0) - 'A') * 9) + (ship.at(1) - '0') - 1;
    coord2 = (static_cast<int>(ship.at(3) - 'A') * 9) + (ship.at(4) - '0') - 1;
    
    if (ship.at(0) == ship.at(3)) {
        if (ship.at(1) > ship.at(4)) {
            for (unsigned int i = 0; i <= coord1 - coord2; ++i) {
                board.at(coord2 + i) = '@';
                vships.push_back(coord2 + i);
            }
        }
        else if (ship.at(4) > ship.at(1)) {
            for (unsigned int i = 0; i <= coord2 - coord1; ++i) {
                board.at(coord1 + i) = '@';
                vships.push_back(coord1 + i);
            }
        }
    }
    else if(ship.at(1) == ship.at(4)) {
        if (ship.at(0) > ship.at(3)) {
            for (unsigned int i = 0; i <= coord1 - coord2; i+=9) {
                board.at(coord2 + i) = '@';
                vships.push_back(coord2 + i);
            }
        }
        if (ship.at(3) > ship.at(0)) {
            for (unsigned int i = 0; i <= coord2 - coord1; i+=9) {
                board.at(coord1 + i) = '@';
                vships.push_back(coord1 + i);
            }
        }
    }
    
    return;
}

void printInstructShip() {
    
    cout << "To place a ship type in the coordinate of the front" << endl
    << "of the ship followed by a space and the coordinate of the " << endl
    << "back of the ship" << endl 
    << "For example: A1 A5, or A1 E1 for an Aircraft Carrier" << endl << endl;
    
    return;
}

void PlaceShips(vector <char> &board, int turn, vector <int> &vships) {
    
    string aircraftCarrier;
    string battleship;
    string sub;
    string destryoer;
    string patrol;
    string next;
    bool validPlacement = true;
    
    
    if (turn == PLAYER1) {
        cout << "Player one place your ships: " << endl;
    }
    else {
        cout << "Player two place your ships: " << endl;
    }
    
    printInstructShip();
    
    cout << "Place your Aircraft Carrier: " << endl;
    cout << "Note: the Aircraft Carrier is 5 spaces long" << endl << endl;
    drawBoard(board);
    
    do {
        getline(cin, aircraftCarrier);
        aircraftCarrier = stoupper(aircraftCarrier);
        validPlacement = validPlacementShip(aircraftCarrier, 5, board);
        if (!validPlacement) {
            cout << "That is not a valid ship placement please enter another "
            << "coordinate set." << endl;
        }
    }
    while(!validPlacement);
    
    drawShip(board, aircraftCarrier, vships);
    
    clearScreen();
    
    cout << "Place your Battleship: " << endl;
    cout << "Note: the Battleship is 4 spaces long" << endl << endl;
    drawBoard(board);
    
    do {
        getline(cin, battleship);
        battleship = stoupper(battleship);
        validPlacement = validPlacementShip(battleship, 4, board);
        if (!validPlacement) {
            cout << "That is not a valid ship placement please enter another "
            << "coordinate set." << endl;
        }
    }
    while(!validPlacement);
    
    drawShip(board, battleship, vships);
    
    clearScreen();
    
    cout << "Place your Submarine: " << endl;
    cout << "Note: the Submarine is 3 spaces long" << endl << endl;
    drawBoard(board);
    
    do {
        getline(cin, sub);
        sub = stoupper(sub);
        validPlacement = validPlacementShip(sub, 3, board);
        if (!validPlacement) {
            cout << "That is not a valid ship placement please enter another "
            << "coordinate set." << endl;
        }
    }
    while(!validPlacement) ;
    
    drawShip(board, sub, vships);
    
    clearScreen();
    
    cout << "Place your Destroyer: " << endl;
    cout << "Note: the Destroyer is 3 spaces long" << endl << endl;
    drawBoard(board);
    
    do {
        getline(cin, destryoer);
        destryoer = stoupper(destryoer);
        validPlacement = validPlacementShip(destryoer, 3, board);
        if (!validPlacement) {
            cout << "That is not a valid ship placement please enter another "
            << "coordinate set." << endl;
        }
    }
    while(!validPlacement) ;
    
    drawShip(board, destryoer, vships);
    
    clearScreen();
    
    cout << "Place your Patrol Boat: " << endl;
    cout << "Note: the Patrol Boat is 2 spaces long" << endl << endl;
    drawBoard(board);
    
    do {
        getline(cin, patrol);
        patrol = stoupper(patrol);
        validPlacement = validPlacementShip(patrol, 2, board);
        if (!validPlacement) {
            cout << "That is not a valid ship placement please enter another "
            << "coordinate set." << endl;
        }
    }
    while(!validPlacement) ;
    
    drawShip(board, patrol, vships);
    
    clearScreen();
    cout << "These are your ships; press enter to continue..." << endl << endl;
    drawBoard(board);
    
    getline(cin, next);
    
    clearScreen();
    return;
}

void lookAway(int turn) {
    string cont;
    
    clearScreen();
    if (turn == PLAYER1) {
        cout << "Player two look away player one is about to take his turn." << endl
        << "Player one press enter to continue" << endl;
    }
    else {
        cout << "Player one look away player two is about to take his turn." << endl
        << "Player two press enter to continue" << endl;
    }
    
    getline(cin, cont);
    clearScreen();
    return;
}

bool validMove(const vector <char> &oboard, string move) {
    // cout << "Got to validMove." << endl;
    int coord = 0;    
    if (move.size() != 2) {
        //cout << "Returning false like im supposed to..." << endl;
        return false;
    }
    else if (move.at(0) >= 'A' && move.at(0) <= 'I' && move.at(1) >= '1' && move.at(1) <= '9'){
        coord = (static_cast<int>(move.at(0) - 'A') * 9) + (move.at(1) - '0') - 1;
        if(oboard.at(coord) != 'O' && oboard.at(coord) != 'X' && oboard.at(coord) != 'P') {
            //cout << "Valid move true." << endl;
            return true;
        }
    }
    return false;
}

bool determineIfHit (const vector <char> &boardE, string move) {
    int coord = 0;
    coord = (static_cast<int>(move.at(0) - 'A') * 9) + (move.at(1) - '0') - 1;
    if (boardE.at(coord) == '@') {
        return true;
    }
    return false;
}

int gamestats(const vector <char> &boardA, const vector <char> &boardE,
const vector <int> &shipsA, const vector <int> &shipsE) {
    int airc = 0;
    int batship = 0;
    int su = 0;
    int dest = 0;
    int pat = 0;
    int remainShips = 5;
    
    cout << "Game stats:" << endl << endl;
    cout << "The enemy has sunk: " << endl;
    
    for (unsigned int i = 0; i < 5; ++i) {
        if (boardA.at(shipsA.at(i)) == 'X') {
            ++airc;
        }
    }
    for (unsigned int i = 5; i < 9; ++i) {
        if (boardA.at(shipsA.at(i)) == 'X') {
            ++batship;
        }
    }
    for (unsigned int i = 9; i < 12; ++i) {
        if (boardA.at(shipsA.at(i)) == 'X') {
            ++su;
        }
    }
    for (unsigned int i = 12; i < 15; ++i) {
        if (boardA.at(shipsA.at(i)) == 'X') {
            ++dest;
        }
    }
    for (unsigned int i = 15; i < 17; ++i) {
        if (boardA.at(shipsA.at(i)) == 'X') {
            ++pat;
        }
    }
    if (airc == 5) {
        cout << "Your Aircraft Carrier." << endl;
        --remainShips;
    }
    if (batship == 4) {
        cout << "Your Battleship." << endl;
        --remainShips;
    }
    if (su == 3) {
        cout << "Your Submarine." << endl;
        --remainShips;
    }
    if (dest == 3) {
        cout << "Your Destroyer." << endl;
        --remainShips;
    }
    if (pat == 2) {
        cout << "Your Patrol Boat." << endl;
        --remainShips;
    }
    if (airc != 5 && batship != 4 && su != 3 && dest != 3 && pat != 2) {
        cout << "None of your ships!" << endl;
    }
    
    airc = 0, batship = 0, su = 0, dest = 0, pat = 0;
    
    cout << endl << "You have sunk: " << endl;
    
    for (unsigned int i = 0; i < 5; ++i) {
        if (boardE.at(shipsE.at(i)) == 'X') {
            ++airc;
        }
    }
    for (unsigned int i = 5; i < 9; ++i) {
        if (boardE.at(shipsE.at(i)) == 'X') {
            ++batship;
        }
    }
    for (unsigned int i = 9; i < 12; ++i) {
        if (boardE.at(shipsE.at(i)) == 'X') {
            ++su;
        }
    }
    for (unsigned int i = 12; i < 15; ++i) {
        if (boardE.at(shipsE.at(i)) == 'X') {
            ++dest;
        }
    }
    for (unsigned int i = 15; i < 17; ++i) {
        if (boardE.at(shipsE.at(i)) == 'X') {
            ++pat;
        }
    }
    if (airc == 5) {
        cout << "Their Aircraft Carrier." << endl;
    }
    if (batship == 4) {
        cout << "Their Battleship." << endl;
    }
    if (su == 3) {
        cout << "Their Submarine." << endl;
    }
    if (dest == 3) {
        cout << "Their Destroyer." << endl;
    }
    if (pat == 2) {
        cout << "Their Patrol Boat." << endl;
    }
    if (airc != 5 && batship != 4 && su != 3 && dest != 3 && pat != 2) {
        cout << "No enemy ships." << endl;
    }
    
    return remainShips;
}
void weponstats(int weponPts) {
    cout << "You have a total of " << weponPts << " wepon points." << endl
    << "1: Atom Bomb (aboard Aicraft Carrier) :  cost - " << ATOM_BOMB << " " << endl
    << "2: Macheen gun (aboard Battleship):      cost - " << MACHEEN_GUN << " " << endl
    << "3: Torpedo (aboard Submarine):           cost - " << TORPEDO << " " << endl
    << "4: Sea Mine (aboard Destroyer):          cost - " << SEA_MINE << " " << endl
    << "5: Radar (aboard Patrol Boad):           cost - " << RADAR << " " << endl << endl
    << "To fire a special wepon type the number of the wepon " << endl
    << "before the coordinates, for example 4A7 to fire a radar at A7." << endl
    << "Enter w followed by enter to see the wepons manual. " << endl << endl;
}

void weponsManual() {
    cout << "For an atom bomb type in a coordinate. " << endl
    << "For a macheen gun type in two coordinates 5 spaces apart" << endl
    << "For a torpedo only type in a row or collum number " << endl
    << "For a Sea Mine type in a coordinate, it will float untill it hits something " << endl
    << "For a Radar type in a coordinat, it will regester a miss if there is noting and " << endl
    << "if it registers a '*' there may be a ship in the area. " << endl;
    return;
}

void normturn(vector <char> &boardA, vector <char> &boardE, vector <char> &oboard,
vector <int> &shipsA, vector <int> &shipsE) {
    string move;
    bool validM = true;
    bool hit = false;
    int coord = 0;
    string next;
    
    gamestats(boardA, boardE, shipsA, shipsE); 
    
    cout << endl << "The enemy seas: " << endl << endl;
    drawBoard(oboard);
    cout << endl << endl;
    cout << "Your ships: " << endl;
    drawBoard(boardA);
    cout << endl << "Make your move: ";
    do {
        getline(cin, move);
        move = stoupper(move);
        cout << "merp" << endl;
        validM = validMove(oboard, move);
        if (!validM) {
            cout << "That was an incorrect move, try again." << endl;
        }
    }
    while (!validM);
    
    clearScreen();
    coord = (static_cast<int>(move.at(0) - 'A') * 9) + (move.at(1) - '0') - 1;
    hit = determineIfHit(boardE, move);
    if (hit) {
        oboard.at(coord) = 'X';
        boardE.at(coord) = 'X';
    }
    else {
        oboard.at(coord) = 'O';
        boardE.at(coord) = 'O';
    }
    
    gamestats(boardA, boardE, shipsA, shipsE); 
    
    cout << "The enemy seas: " << endl << endl;
    drawBoard(oboard);
    cout << endl << endl;
    cout << "Your ships: " << endl;
    drawBoard(boardA);
    
    if (hit) {
        cout << "HIT!" << endl;
    }
    else {
        cout << "miss" << endl;
    }
    
    cout << endl << "Press enter to continue..." << endl;
    getline(cin, next);
    return;
}

bool validSuperMove(const vector <char> &oboard, string move, int weponPts) {
    int coord = 0;
    
    if (move.size() == 2) {
        //cout << "Size is 2" << endl;
        if (move.at(0) >= 'A' && move.at(0) <= 'I' && move.at(1) >= '1' && move.at(1) <= '9'){
            coord = (static_cast<int>(move.at(0) - 'A') * 9) + (move.at(1) - '0') - 1;
            if(oboard.at(coord) != 'O' && oboard.at(coord) != 'X') {
                return true;
            }
        }
        if ((move.at(0) >= '1' && move.at(0) <= '5') && ((move.at(1) >= '1' && move.at(1) <= '9'))) {
            if (move.at(1) >= 'A' && move.at(1) <= 'I') {
                coord = static_cast<int>('A' - move.at(1)) * 9;
                if (oboard.at(coord) == 'X') {
                    coord = coord + 9;
                    if (oboard.at(coord) == 'X') {
                        return false;
                    }
                }
            }
            else if (move.at(1) >= '1' && move.at(1) <= '9') {
                coord = move.at(1) - '0';
                if (oboard.at(coord) == 'X') {
                    coord = coord + 72;
                    if (oboard.at(coord) == 'X') {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    if (move.size() == 3) {
        //out << "Size is 3" << endl;
        if (move.at(0) >= '1' && move.at(0) <= '5' && move.at(1) >= 'A' && move.at(1) <= 'I'
        && move.at(2) >= '1' && move.at(2) <= '9' ) {
            //cout << "Move headder valid." << endl;
            if ((move.at(0) == '1' && weponPts < 6) || (move.at(0) == '2' && weponPts < 4)
            || (move.at(0) == '3' && weponPts < 5) || (move.at(0) == '4' && weponPts < 7)
            || (move.at(0) == '5' && weponPts < 3)) {
                return false;
            }
            //cout << "Wepon valid." << endl;
            return true;
        }
    }
    if (move.size() == 6) {
        if (move.at(0) != '2') {
            return false;
        }
        //cout << "Changing move" << endl;
        move.erase(0, 1);
        //cout << "Your move is: " << move << ":3" << endl;
        if (validPlacementShip(move, 5, oboard)) {
            //cout << "returning true" << endl;
            return true;
        }
    }
    return false;
}

bool fire (vector <char> &boardE, vector <char> &oboard, int coord, bool &hit) {
    
    bool hitn = false; 
    
    if (!(coord > 81) && !(coord < 0)) {
        if (boardE.at(coord) == '@') {
            if (!hit) {
                hit = true;
            }
            hitn = true;
        }
        if (hitn) {
            oboard.at(coord) = 'X';
            boardE.at(coord) = 'X';
        }
        else {
            oboard.at(coord) = 'O';
            boardE.at(coord) = 'O';
        }
    }

    return hit;
}

void radar(vector <char> &oboard, vector <char> &boardE, int coord) {
    
    if (rand() % 8 == 5) {
        oboard.at(coord) = '*';
    }
    else if (boardE.at(coord) == '@') {
        oboard.at(coord) = '*';
    }
    else {
        oboard.at(coord) = 'O';
        boardE.at(coord) = 'O';
    }
    
    return;
}
void superTurn(vector <char> &boardA, vector <char> &boardE, vector <char> &oboard,
vector <int> &shipsA, vector <int> &shipsE, int &weponPts) {
    
    string move;
    bool validM = true;
    bool hit = false;
    int coord = 0;
    int coord2 = 0;
    string next;
    int weponUsed = 9;
    
    weponstats(weponPts);
    gamestats(boardA, boardE, shipsA, shipsE); 
    
    cout << endl << "The enemy seas: " << endl << endl;
    drawBoard(oboard);
    cout << endl << endl;
    cout << "Your ships: " << endl;
    drawBoard(boardA);
    cout << endl << "Make your move: ";
    do {
        getline(cin, move);
        move = stoupper(move);
        if (move == "M") {
            weponsManual();
            validM = false;
        }
        else {
            validM = validSuperMove(oboard, move, weponPts);
            if (!validM) {
                cout << "That was an incorrect move, try again." << endl;
            }
        }
    }
    while (!validM);
    
    if (move.at(0) >= '1' && move.at(0) <= '5') {
        weponUsed = move.at(0) - '0';
        if (weponUsed == 1) {
            weponPts = weponPts - 6;
        }
        else if (weponUsed == 2) {
            weponPts = weponPts - 4;
        }
        else if (weponUsed == 3) {
            weponPts = weponPts - 5;
        }
        else if (weponUsed == 4) {
            weponPts = weponPts - 7;
        }
        else {
            weponPts = weponPts - 3;
        }
    }
    
    clearScreen();
    
    if (weponUsed == 9) {
        coord = (static_cast<int>(move.at(0) - 'A') * 9) + (move.at(1) - '0') - 1;
        hit = determineIfHit(boardE, move);
        //cout << "got to wepon 9 if statement" << endl;
        if (hit) {
            oboard.at(coord) = 'X';
            boardE.at(coord) = 'X';
        }
        else {
            //cout << "Got to else statement" << endl;
            oboard.at(coord) = 'O';
            boardE.at(coord) = 'O';
        }
    }
    
    if (weponUsed == 1) {
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 1;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0');
        cout << coord << endl;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 2;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') + 9;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') + 7;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') + 8;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 11;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 9;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 10;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0')  - 17;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 21;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') + 15;
        fire(boardE, oboard, coord, hit);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') + 19;
        fire(boardE, oboard, coord, hit);
        
    }
    
    if (weponUsed == 2) {
        int coord1 = 0;
        int coord2 = 0;
        int tempcoord = 0;
        cout << "Move is " << move << endl;
        
        coord1 = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 1;
        coord2 = (static_cast<int>(move.at(4) - 'A') * 9) + (move.at(5) - '0') - 1;
        
        if (move.at(1) == move.at(4)) {
            cout << "Mgun first if statement" << endl;
            if (move.at(2) > move.at(5)) {
                for (unsigned int i = 0; i <= coord1 - coord2; ++i) {
                    tempcoord = coord2 + i;
                    fire(boardE, oboard, tempcoord, hit);
                }
            }
            else if (move.at(5) > move.at(2)) {
                for (unsigned int i = 0; i <= coord2 - coord1; ++i) {
                    tempcoord = coord1 + i;
                    fire(boardE, oboard, tempcoord, hit);
                }
            }
        }
        else if(move.at(2) == move.at(5)) {
            if (move.at(1) > move.at(4)) {
                cout << "Mgun second if statement" << endl;
                for (unsigned int i = 0; i <= coord1 - coord2; i+=9) {
                    tempcoord = coord2 + i;
                    cout << tempcoord << endl;
                    fire(boardE, oboard, tempcoord, hit);
                }
            }
            if (move.at(4) > move.at(1)) {
                for (unsigned int i = 0; i <= coord2 - coord1; i+=9) {
                    tempcoord = coord1 + i;
                    fire(boardE, oboard, tempcoord, hit);
                }
            }
        }
        cout << "Not entering anything" << endl;
    }
    
    if (weponUsed == 3) {
        if (move.at(1) >= '1' && move.at(1) <= '9') {
            int i = 0;
            coord = (move.at(1) - '0') - 1;
            if ((boardE.at(coord) == 'X') || (boardE.at(coord) == 'O')) {
                coord = coord + 72;
                do {
                    coord = (move.at(1) - '0') - 1 - i;
                    fire(boardE, oboard, coord, hit);
                    i += 9;
                }
                while (!hit && coord < 81);
            }
            else {
                do {
                    coord = (move.at(1) - '0') - 1 + i;
                    fire(boardE, oboard, coord, hit);
                    i += 9;
                }
                while (!hit && coord < 81);
            }
        }
        else if (move.at(1) >= 'A' && move.at(1) <= 'I') {
            int j = 0;
            coord = (move.at(1) - 'A') * 9;
            if ((boardE.at(coord) == 'X') || (boardE.at(coord) == 'O')) {
                coord = coord + 9;
                do {
                    int temp = (move.at(1) - 'A') * 9;
                    coord = temp + j;
                    fire(boardE, oboard, coord, hit);
                    --j;
                }
                while (!hit && j < 9);
            }
            else {
                do {
                    int temp = (move.at(1) - 'A') * 9;
                    coord = temp + j;
                    fire(boardE, oboard, coord, hit);
                    ++j;
                }
                while (!hit && j < 9);
            }
        }
    }
    
    if (weponUsed == 5) {
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 1;
        radar(oboard, boardE, coord);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0');
        radar(oboard, boardE, coord);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 2;
        radar(oboard, boardE, coord);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') - 10;
        radar(oboard, boardE, coord);
        coord = (static_cast<int>(move.at(1) - 'A') * 9) + (move.at(2) - '0') + 8;
        radar(oboard, boardE, coord);
    }
    
    gamestats(boardA, boardE, shipsA, shipsE); 
    
    cout << "The enemy seas: " << endl << endl;
    drawBoard(oboard);
    cout << endl << endl;
    cout << "Your ships: " << endl;
    drawBoard(boardA);
    
    if (hit) {
        cout << "HIT!" << endl;
    }
    else if (weponUsed == 5) {
        cout << "Radar Enforced" << endl;
    }
    else {
        cout << "miss" << endl;
    }
    
    cout << endl << "Press enter to continue..." << endl;
    getline(cin, next);
    
    return;
}

void salvoTurn(vector <char> &boardA, vector <char> &boardE, vector <char> &oboard,
vector <int> &shipsA, vector <int> &shipsE) {
    
    string move;
    bool validM = true;
    bool hit = false;
    int coord = 0;
    string next;
    int numShots = 0;
    int numShipsRemain = 0;
    int numP; 
    
    clearScreen();
    
    cout << "Salvo Mode" << endl << endl;
    numShipsRemain = gamestats(boardA, boardE, shipsA, shipsE); 
    numShots = numShipsRemain;
    
    cout << endl << "The enemy seas: " << endl << endl;
    drawBoard(oboard);
    cout << endl << endl;
    cout << "Your ships: " << endl;
    drawBoard(boardA);
    cout << endl << "Make your move: you have " << numShots << " missiles left. " << endl;
    
    do {
        getline(cin, move);
        move = stoupper(move);
        validM = validMove(oboard, move);
        if (!validM) {
            cout << "That was an incorrect move, try again." << endl;
        }
        else {
            
            coord = (static_cast<int>(move.at(0) - 'A') * 9) + (move.at(1) - '0') - 1;
            cout << "Coord: " << coord << endl;
            oboard.at(coord) = 'P';
        
            --numShots;
            
            clearScreen();
            
            numShipsRemain = gamestats(boardA, boardE, shipsA, shipsE); 
            
            cout << endl << "The enemy seas: " << endl << endl;
            drawBoard(oboard);
            cout << endl << endl;
            cout << "Your ships: " << endl;
            drawBoard(boardA);
            cout << endl << "Make your move: you have " << numShots << " left. " << endl;
        }
        
    }
    while (!validM || numShots > 0);
    
    for (unsigned int i = 0; i < oboard.size(); ++i) {
        if (oboard.at(i) == 'P') {
            if (boardE.at(i) == ' ') {
                oboard.at(i) = 'O';
                boardE.at(i) = 'O';
            }
            else {
                oboard.at(i) = 'X';
                boardE.at(i) = 'X';
                hit = true;
            }
        }
    }
    
    clearScreen();
    
    gamestats(boardA, boardE, shipsA, shipsE); 
    
    cout << "The enemy seas: " << endl << endl;
    drawBoard(oboard);
    cout << endl << endl;
    cout << "Your ships: " << endl;
    drawBoard(boardA);
    
    if (hit) {
        cout << "HIT!" << endl;
    }
    else {
        cout << "miss" << endl;
    }
    
    cout << endl << "Press enter to continue..." << endl;
    getline(cin, next);
    
    return;
}

bool gamewon(const vector <char> &boardo) {
    int count = 0;
    for (unsigned int i = 0; i < boardo.size(); ++i) {
        if(boardo.at(i) == 'X') {
            ++count;
        }
    }
    if(count == 17) {
        return true;
    }
    return false;
}

int main() {
    
   vector <char> boardP1(81, ' ');
   vector <char> boardoP1(81, ' ');
   vector <char> boardP2(81, ' ');
   vector <char> boardoP2(81, ' ');
   vector <int> shipsP1;
   vector <int> shipsP2;
   int weponPtsP1 = 0;
   int weponPtsP2 = 0;
    
   int shipsleftP1 = 5;
   int shipsleftP2 = 5;
   bool won = false;
   int turn = PLAYER1;
   string o;
   string options = "1";
   srand(time(0));
   
   clearScreen();
   o = printIntro();
   if (o == "o") {
       options = opt();
   }
   lookAway(turn);
   PlaceShips(boardP1, turn, shipsP1);
   turn = PLAYER2;
   lookAway(turn);
   PlaceShips(boardP2, turn, shipsP2);
   turn = PLAYER1;
   
   if (options == "3") {
       do {
           lookAway(turn);
           cout << "Superwepons mode: " << endl;
           if (turn == PLAYER1) {
               cout << "Player 1" << endl;
               superTurn(boardP1, boardP2, boardoP1, shipsP1, shipsP2, weponPtsP1);
               won = gamewon(boardoP1);
               turn = PLAYER2;
               ++weponPtsP1;
           }
           else {
               cout << "Player 2" << endl;
               superTurn(boardP2, boardP1, boardoP2, shipsP2, shipsP1, weponPtsP2);
               won = gamewon(boardoP2);
               turn = PLAYER1;
               ++weponPtsP2;
           }
       }
       while(!won);
   }
   
   else if (options == "2") {
       cout << "Salvo mode: " << endl;
       do {
           lookAway(turn);
           if (turn == PLAYER1) {
               cout << "Player 1" << endl;
               salvoTurn(boardP1, boardP2, boardoP1, shipsP1, shipsP2);
               won = gamewon(boardoP1);
               turn = PLAYER2;
           }
           else {
               cout << "Player 2" << endl;
               salvoTurn(boardP2, boardP1, boardoP2, shipsP2, shipsP1);
               won = gamewon(boardoP2);
               turn = PLAYER1;
           }
       }
       while (!won);
       
   }
   
   else {
       do {
           lookAway(turn);
           if (turn == PLAYER1) {
               cout << "Player 1" << endl;
               normturn(boardP1, boardP2, boardoP1, shipsP1, shipsP2);
               won = gamewon(boardoP1);
               turn = PLAYER2;
           }
           else {
               cout << "Player 2" << endl;
               normturn(boardP2, boardP1, boardoP2, shipsP2, shipsP1);
               won = gamewon(boardoP2);
               turn = PLAYER1;
           }
       }
       while(!won);
   }
   
   
   clearScreen();
   if (turn == PLAYER1) {
       cout << "Congradulations Player 2 you win!!" << endl;
   }
   else {
       cout << "Congradulations Player 1 you win!!" << endl;
   }
   
    return 0;
}