#include "CGhostHard.h"

CGhostHard::CGhostHard(CData& alldata) : m_LastChar(' '){
    int x, y;
    m_Direction = 8; // first direction is up
    alldata.getGhostIndex(x, y); // assigns coordinates to the ghost from member variable of CData
    m_X = x;
    m_Y = y;
    m_OriginalX = m_X; // saves original coordinates to refresh it after the game is over
    m_OriginalY = m_Y;
}

int CGhostHard::move(const int button, CData & alldata){
    int value = 0;
    int flag = 0;
    int lastX = 0; // to check last coordinates - ghost should not be able to go back
    int lastY = 0;
    int oppositeDirection = 0; // if there is a "dead-end street", turn around
    int pX = 0;
    int pY = 0;
    int vectorX = 0;
    int vectorY = 0;
    alldata.getCPacmanIndex(pX, pY); // to get fresh pacman's coordinates after his every move
    vectorX = m_X - pX; // vector to know the position of the ghost considering to pacman's position (and to know length between them)
    vectorY = m_Y - pY;
    int up = alldata.getBool(m_X, m_Y-1); // to know if there is a free way in the up side
    int down = alldata.getBool(m_X, m_Y+1);
    int left = alldata.getBool(m_X-1, m_Y);
    int right = alldata.getBool(m_X+1, m_Y);
    if(m_Direction == 8){ // check last index and opposite direction if ghost's direction is "up"
        lastX = m_X;
        lastY = m_Y+1;
        oppositeDirection = 2;
    }
    else if(m_Direction == 2){
        lastX = m_X;
        lastY = m_Y-1;
        oppositeDirection = 8;
    }
    else if(m_Direction == 4){
        lastX = m_X+1;
        lastY = m_Y;
        oppositeDirection = 6;
    }
    else{ //m_Direction == 6 
        lastX = m_X-1;
        lastY = m_Y;
        oppositeDirection = 4;
    }
    if(vectorY < 0){ // above the pacman
        if(vectorX < 0){ // left above the pacman
            if(abs(vectorX) < abs(vectorY)){ // if they are more under each other than on the same Y level
                if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
                else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
                else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
                else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
                else { flag = 1; }
            }
            else{ // if they are more on the same Y level than under each other
                if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
                else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
                else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
                else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
                else { flag = 1; }
            }
        }
        else if(vectorX == 0){ // they are above each other
            if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
            else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
            else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
            else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
            else { flag = 1; }
        }
        else{ //vectorX > 0 ... right above the pacman
            if(abs(vectorX) < abs(vectorY)){
                if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
                else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
                else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
                else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
                else { flag = 1; }
            }
            else{
                if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
                else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
                else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
                else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
                else { flag = 1; }
            }
        }
    }
    else if(vectorY == 0){ // they are on the same Y level
        if(vectorX < 0){ // on the left from pacman
            if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
            else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
            else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
            else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
            else { flag = 1; }
        }
        else{ //vectorX > 0 ... on the right from pacman
            if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
            else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
            else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
            else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
            else { flag = 1; }
        }
    }
    else{ //vectorY > 0 ...under the pacman
        if(vectorX < 0){ // left under the pacman
            if(abs(vectorX) < abs(vectorY)){ // if they are more under each other than on the same Y level
                if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
                else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
                else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
                else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
                else { flag = 1; }
            }
            else{ // if they are more on the same Y level than under each other
                if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
                else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
                else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
                else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
                else { flag = 1; }
            }
        }
        else if(vectorX == 0){ // they are above each other
            if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
            else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
            else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
            else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
            else { flag = 1; }
        }
        else{ //vectorX > 0 ...right under the pacman
            if(abs(vectorX) < abs(vectorY)){ // if they are more under each other than on the same Y level
                if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
                else if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
                else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
                else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
                else { flag = 1; }
            }
            else{ // if they are more on the same Y level than under each other
                if(left == 1 && m_X-1 != lastX) { value = moveLeft(alldata); }
                else if(up == 1 && m_Y-1 != lastY) { value = moveUp(alldata); }
                else if(down == 1 && m_Y+1 != lastY) { value = moveDown(alldata); }
                else if(right == 1 && m_X+1 != lastX) { value = moveRight(alldata); }
                else { flag = 1; }
            }
        }
    }
    if(flag == 1){ // if pacman can't go anywhere else than back
        if(oppositeDirection == 8) { value = moveUp(alldata); }
        else if(oppositeDirection == 2) { value = moveDown(alldata); }
        else if(oppositeDirection == 4) { value = moveLeft(alldata); }
        else value = moveRight(alldata);
    }
    return value;
}

int CGhostHard::moveUp(CData& alldata){
    if(alldata.getChar(m_X, m_Y-1) == 'C' || alldata.getChar(m_X, m_Y-1) == 'O'){ // got pacman
        m_Direction = 8;
        return -1;
    }
    else if(alldata.getChar(m_X, m_Y-1) == 'A'){ // on the next index is another ghost - dont move, just turn around
        m_Direction = 2;
        return 0;
    }
    else{ // move
        alldata.changeCharMap(m_Y, m_X, m_LastChar);
        m_LastChar = alldata.getChar(m_X, m_Y-1);
        alldata.changeCharMap(m_Y-1, m_X, 'A');
        m_Direction = 8;
        m_Y--;
        return 0;
    }
}

int CGhostHard::moveDown(CData& alldata){
    if(alldata.getChar(m_X, m_Y+1) == 'C' || alldata.getChar(m_X, m_Y+1) == 'O'){
        m_Direction = 8;
        return -1;
    }
    else if(alldata.getChar(m_X, m_Y+1) == 'A'){
        m_Direction = 8;
        return 0;
    }
    else{
        alldata.changeCharMap(m_Y, m_X, m_LastChar);
        m_LastChar = alldata.getChar(m_X, m_Y+1);
        alldata.changeCharMap(m_Y+1, m_X, 'A');
        m_Direction = 2;
        m_Y++;
        return 0;
    }
}

int CGhostHard::moveLeft(CData& alldata){
    if(alldata.getChar(m_X-1, m_Y) == 'C' || alldata.getChar(m_X-1, m_Y) == 'O'){
        m_Direction = 8;
        return -1;
    }
    else if(alldata.getChar(m_X-1, m_Y) == 'A'){
        m_Direction = 6;
        return 0;
    }
    else{
        alldata.changeCharMap(m_Y, m_X, m_LastChar);
        m_LastChar = alldata.getChar(m_X-1, m_Y);
        alldata.changeCharMap(m_Y, m_X-1, 'A');
        m_Direction = 4;
        m_X--;
        return 0;
    }
}

int CGhostHard::moveRight(CData& alldata){
    if(alldata.getChar(m_X+1, m_Y) == 'C' || alldata.getChar(m_X+1, m_Y) == 'O'){
        m_Direction = 8;
        return -1;
    }
    else if(alldata.getChar(m_X+1, m_Y) == 'A'){
        m_Direction = 4;
        return 0;
    }
    else{
        alldata.changeCharMap(m_Y, m_X, m_LastChar);
        m_LastChar = alldata.getChar(m_X+1, m_Y);
        alldata.changeCharMap(m_Y, m_X+1, 'A');
        m_Direction = 6;
        m_X++;
        return 0;
    }
}

void CGhostHard::takeGhostHome(CData& alldata){ // after every pacman killing - put last char down and transport "home"
    alldata.changeCharMap(m_Y, m_X, m_LastChar);
    m_X = m_OriginalX;
    m_Y = m_OriginalY;
    alldata.changeCharMap(m_Y, m_X, 'A'); // puts ghost gome.
    m_LastChar = ' ';
}
