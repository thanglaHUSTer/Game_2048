#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

const int SIZE = 4;

int board[SIZE][SIZE];

void init() {
    srand(time(NULL)); // Khởi tạo bộ sinh số ngẫu nhiên với giá trị seed là thời gian hiện tại
    for(int i=0; i<SIZE; i++) { // Lặp qua các hàng của bảng
        for(int j=0; j<SIZE; j++) { // Lặp qua các cột của bảng
            board[i][j] = 0;  //Đặt giá trị ban đầu của mỗi ô trong bảng là 0
        }
    }

    int x1 = rand() % SIZE; // Chọn vị trí ngẫu nhiên cho ô thứ nhất
    int y1 = rand() % SIZE;

    int x2 = rand() % SIZE; // Chọn vị trí ngẫu nhiên cho ô thứ hai
    int y2 = rand() % SIZE;
    while(x2 == x1 && y2 == y1) { // Nếu 2 ô trùng nhau, tạo lại các vị trí mới cho đến khi không còn trùng nhau nữa 
        x2 = rand() % SIZE;
        y2 = rand() % SIZE;
    }
    board[x1][y1] = 2; // Đặt giá trị 2 cho ô thứ nhất
    board[x2][y2] = 2; // Đặt giá trị 2 cho ô thứ hai  
}

void printBoard() {
    cout << endl;
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
void moveTiles(int x, int y, int dx, int dy) {
    if(board[x][y] == 0) { // Nếu ô hiện tại không có giá trị, không thể di chuyển
        return;
    }
    int i = x + dx;
    int j = y + dy;
    while(i >= 0 && i < SIZE && j >= 0 && j < SIZE) { // Duyệt qua các ô từ vị trí hiện tại cho đến cuối bảng hoặc gặp ô không trống
        if(board[i][j] == 0) { // Nếu ô đích trống, di chuyển ô hiện tại đến ô đó
            board[i][j] = board[i-dx][j-dy];
            board[i-dx][j-dy] = 0;
            i += dx; // Di chuyển đến ô tiếp theo
            j += dy;
        } else if(board[i][j] == board[i-dx][j-dy]) { // Nếu ô đích có cùng giá trị với ô hiện tại, ghép 2 ô lại với nhau
            board[i][j] *= 2;
            board[i-dx][j-dy] = 0; // Xóa ô hiện tại khỏi bảng
            return; // Trả về giá trị true để thông báo việc ghép ô đã thành công
        } else { // Nếu ô đích không trống và khác giá trị với ô hiện tại, không thể di chuyển
            return;
        }
    }
}

void moveUp() {
    for(int j=0; j<SIZE; j++) {
        for(int i=1; i<SIZE; i++) {
            moveTiles(i, j, -1, 0);            
        }
    }
}

void moveDown() {
    for(int j=0; j<SIZE; j++) {
        for(int i=SIZE-2; i>=0; i--) {
            moveTiles(i, j, 1, 0);
        }
    }
}

void moveLeft() {
    for(int i=0; i<SIZE; i++) {
        for(int j=1; j<SIZE; j++) {
            moveTiles(i, j, 0, -1);
        }
    }
}

void moveRight() {
    for(int i=0; i<SIZE; i++) {
        for(int j=SIZE-2; j>=0; j--) {
            moveTiles(i, j, 0, 1);
        }
	}
}

bool isGameOver() {
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            if(board[i][j] == 0) {
                return false;
            }
            if(i > 0 && board[i][j] == board[i-1][j]) {
                return false;
            }
            if(j > 0 && board[i][j] == board[i][j-1]) {
                return false;
            }
        }
    }
    return true;
}

int main(){
	init();
	printBoard();	
	while(!isGameOver()){
		cout << "Enter move A/D: left/right, W/S: up/down! ";
	    char move = getch();	    
	    switch(move){
	        case 'W':
	        case 'w':
	            moveUp();
	            break;
	        case 'S':
	        case 's':
	            moveDown();
	            break;
	        case 'A':
	        case 'a':
	            moveLeft();
	            break;
	        case 'D':
	        case 'd':
	            moveRight();
	            break;
	        default:
	        	break;
	    }
	    int x = rand() % SIZE;
	    int y = rand() % SIZE;
	    while(board[x][y] != 0) {
	        x = rand() % SIZE;
	        y = rand() % SIZE;
	    }
	    board[x][y] = 2;
	    system("cls");
	    printBoard();
	}	
	cout << "Game over!" << endl;
	return 0;
}
