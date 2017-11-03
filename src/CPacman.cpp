#include "CPacman.h"

CPacman::CPacman(const CData & alldata) : m_PacmanLook(0){
    m_Direction = 5; // first direction is nowhere - sitting duck :)
    int rows = alldata.getRows();
    int columns = alldata.getColumns();
    char ** charmap = alldata.getCharMap();
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(charmap[i][j] == 'C'){ // finds pacman in a map
                m_X = j;
                m_Y = i;
                m_OriginalX = m_X;
                m_OriginalY = m_Y;
                return;
            }
        }
    }
}

int CPacman::move(const int button, CData & alldata){
    int value = 0;
    if(button == KEY_UP){ // if arrow up was pushed
        value = moveUp(alldata);
    }
    else if(button == KEY_DOWN){
        value = moveDown(alldata);
    }
    else if(button == KEY_LEFT){
        value = moveLeft(alldata);
    }
    else if(button == KEY_RIGHT){
        value = moveRight(alldata);
    }
    else if(button == 112){ // 112 is number for 'p' char - if user wants to pause the game
        value = -2;
    }
    else{ // nothing was pushed - continue with the same direction
        if(m_Direction == 5){
            value = 0;
        }
        else if(m_Direction == 8){
            value = moveUp(alldata);
        }
        else if(m_Direction == 2){
            value = moveDown(alldata);
        }
        else if(m_Direction == 4){
            value = moveLeft(alldata);
        }
        else{ // direction == 6
            value = moveRight(alldata);
        }
    }
    return value;
}

int CPacman::moveUp(CData & alldata){
    char up = ' ';
    if(alldata.getBool(m_X, m_Y-1) == 0){ // here is a barrier - can't go on, stops here
        m_Direction = 5;
        return 0;
    }
    else{ // here you can go (in bool map is 1)
        m_Direction = 8;
        up = alldata.getChar(m_X, m_Y-1);
        if(up == '.' || up == '@'){ // if pacman goes on food
            alldata.changeCharMap(m_Y, m_X, ' ');
            if(m_PacmanLook % 2 == 0){
                alldata.changeCharMap(m_Y-1, m_X, 'C'); // pacman looks as a 'C'
            }
            else{//m_PacmanLook % 2 == 1
                alldata.changeCharMap(m_Y-1, m_X, 'O');
            }
            m_Y--;
            m_PacmanLook++;
            if(up == '@') { return 10; } // 10 points for bonus food
            else { return 1; } // 1 point for normal food
        }
        else if(up == ' '){ // if there has been food already eaten
            alldata.changeCharMap(m_Y, m_X, ' ');
            alldata.changeCharMap(m_Y-1, m_X, 'C');
            m_Y--;
            return 0;
        }
        else{ // pacman touches the ghost
            return -1;
        }
    }
}

int CPacman::moveDown(CData & alldata){
    char down = ' ';
    if(alldata.getBool(m_X, m_Y+1) == 0){
        m_Direction = 5;
        return 0;
    }
    else{
        m_Direction = 2;
        down = alldata.getChar(m_X, m_Y+1);
        if(down == '.' || down == '@'){
            alldata.changeCharMap(m_Y, m_X, ' ');
            if(m_PacmanLook % 2 == 0){
                alldata.changeCharMap(m_Y+1, m_X, 'C');
            }
            else{//m_PacmanLook % 2 == 1
                alldata.changeCharMap(m_Y+1, m_X, 'O');
            }
            m_Y++;
            m_PacmanLook++;
            if(down == '@') { return 10; }
            else { return 1; }
        }
        else if(down == ' '){
            alldata.changeCharMap(m_Y, m_X, ' ');
            alldata.changeCharMap(m_Y+1, m_X, 'C');
            m_Y++;
            return 0;
        }
        else{
            return -1;
        }
    }
}
    
int CPacman::moveLeft(CData & alldata){
    char left = ' ';
    if(alldata.getBool(m_X-1, m_Y) == 0){
        m_Direction = 5;
        return 0;
    }
    else{
        m_Direction = 4;
        left = alldata.getChar(m_X-1, m_Y);
        if(left == '.' || left == '@'){
            alldata.changeCharMap(m_Y, m_X, ' ');
            if(m_PacmanLook % 2 == 0){
                alldata.changeCharMap(m_Y, m_X-1, 'C');
            }
            else{//m_PacmanLook % 2 == 1
                alldata.changeCharMap(m_Y, m_X-1, 'O');
            }
            m_X--;
            m_PacmanLook++;
            if(left == '@') { return 10; }
            else { return 1; }
        }
        else if(left == ' '){
            alldata.changeCharMap(m_Y, m_X, ' ');
            alldata.changeCharMap(m_Y, m_X-1, 'C');
            m_X--;
            return 0;
        }
        else{
            return -1;
        }
    }
}
    
int CPacman::moveRight(CData & alldata){
    char right = ' ';
    if(alldata.getBool(m_X+1, m_Y) == 0){
        m_Direction = 5;
        return 0;
    }
    else{
        m_Direction = 6;
        right = alldata.getChar(m_X+1, m_Y);
        if(right == '.' || right == '@'){
            alldata.changeCharMap(m_Y, m_X, ' ');
            if(m_PacmanLook % 2 == 0){
                alldata.changeCharMap(m_Y, m_X+1, 'C');
            }
            else{//m_PacmanLook % 2 == 1
                alldata.changeCharMap(m_Y, m_X+1, 'O');
            }
            m_X++;
            m_PacmanLook++;
            if(right == '@') { return 10; }
            else { return 1; }
        }
        else if(right == ' '){
            alldata.changeCharMap(m_Y, m_X, ' ');
            alldata.changeCharMap(m_Y, m_X+1, 'C');
            m_X++;
            return 0;
        }
        else{ 
            return -1;
        }
    }
}

void CPacman::refreshIndex(){
    m_X = m_OriginalX;
    m_Y = m_OriginalY;
    m_Direction = 5;
}

void CPacman::givePacmanIndex(CData & alldata) const{
    alldata.changeCPacmanIndex(m_X, m_Y);
}
