#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
// □■▩
#define SPACE 0 // "  "
#define WHITE 1 // □
#define BLACK 2 // ■
#define GRAY  3 // ▩
#define xFrame 12
#define yFrame 20
using namespace std;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //커서숨기기 함수
typedef struct POSITION{int y; int x;} POS; 
typedef struct strc_block{
	char name;
	POS position;
	POS pivot;
	int rotation;
	int xLength;
	int yLength;
	int square[4][4];
	
}block;
/* -------- 	Functions 		-------- */
void setcursortype(CURSOR_TYPE c);
void setcolor(unsigned short text, unsigned short back);
int title(int& hit);
void gameover(block BLOCK, bool next);
void setFrame(void);
int (* delete_block_from_display(block BLOCK, int (*display)[xFrame]))[xFrame];
int (* insert_block_to_display(block BLOCK, int (*display)[xFrame]))[xFrame];
POS rotatePivot(block BLOCK, bool isLeft);
bool rotation_possible_checker(block BLOCK);
block rotate_block(block BLOCK);
bool vertical_move_checker(block BLOCK);
bool horizontal_move_checker(block BLOCK, bool isLeft);
int long_vertical_move_checker(block BLOCK);
block control(block & BLOCK);
void draw(int (*display)[xFrame]);
block INIT_SQUARE(block & BLOCK);
block get_block(char Char);
int line_checker(void);
void line_eraser(int decimal_encoding);
char generate_random_char(void);
void change_block_color(block &);
/* ------------------------------------- */

/* --------	Global Variables 	-------- */
int display[yFrame][xFrame] = {{0}};
int score;
/* ------------------------------------- */

/* -------- 	Main Function 	-------- */
int main(){
	block BLOCK = get_block('J');
	setFrame();
	bool next = false;
	int once_hit = 0;
	int is_erasable;
	
	while(1){
		title(once_hit);
		
		if(next = !vertical_move_checker(BLOCK)){
			while (kbhit()) getch(); // erase key inputs in buffer
			change_block_color(BLOCK);
			insert_block_to_display(BLOCK, display);
			
			gameover(BLOCK, next);
			
			do{
				line_eraser(is_erasable = line_checker());
			}while(is_erasable != 0);

			BLOCK = get_block(generate_random_char()); 
		}	
		control(BLOCK);		
		insert_block_to_display(BLOCK, display);
		draw(display);	
	}
	return 0;
}
/* ------------------------------------- */

/* --------	set the color of texts -------- */
void setcolor(unsigned short text, unsigned short back){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
/* ------------------------------------- */

void setFrame(void){
	/*----------------------------------------------------------------------------------------------------------------*/
	// Left Frame //
	block FRAME_L1 = get_block('l');	block FRAME_L2 = get_block('l');	block FRAME_L3 = get_block('l');
	block FRAME_L4 = get_block('l');	block FRAME_L5 = get_block('l');
	FRAME_L1.position.y = 0;	FRAME_L2.position.y = 4;	FRAME_L3.position.y = 8;
	FRAME_L4.position.y = 12;	FRAME_L5.position.y = 16;
	/*----------------------------------------------------------------------------------------------------------------*/
	// Right Frame //
	block FRAME_R1 = get_block('r');	block FRAME_R2 = get_block('r');	block FRAME_R3 = get_block('r');
	block FRAME_R4 = get_block('r');	block FRAME_R5 = get_block('r');	
	FRAME_R1.position.y = 0;	FRAME_R2.position.y = 4;	FRAME_R3.position.y = 8;
	FRAME_R4.position.y = 12;	FRAME_R5.position.y = 16;
	/*----------------------------------------------------------------------------------------------------------------*/
	// Bottom Frame //
	block FRAME_B1 = get_block('b');	block FRAME_B2 = get_block('b');	block FRAME_B3 = get_block('b');
	FRAME_B1.position.x = 0;	FRAME_B2.position.x = 4;	FRAME_B3.position.x = 8;
	/*----------------------------------------------------------------------------------------------------------------*/
	// Display the Frames //
	insert_block_to_display(FRAME_L1, display);		insert_block_to_display(FRAME_L2, display);		insert_block_to_display(FRAME_L3, display);
	insert_block_to_display(FRAME_L4, display);		insert_block_to_display(FRAME_L5, display);
	insert_block_to_display(FRAME_R1, display);		insert_block_to_display(FRAME_R2, display);		insert_block_to_display(FRAME_R3, display);
	insert_block_to_display(FRAME_R4, display);		insert_block_to_display(FRAME_R5, display);
	insert_block_to_display(FRAME_B1, display);		insert_block_to_display(FRAME_B2, display);		insert_block_to_display(FRAME_B3, display);
	/*----------------------------------------------------------------------------------------------------------------*/
}
/* ------------------------------------- */

/* -------- loops infinitely untill key is hit -------- */
int title(int& hit){
	setcursortype(NOCURSOR);
	if(!hit){
			for(int cnt; !(hit = kbhit()); cnt++ ){
				if(cnt%20 == 0) setcolor(rand()%15 + 1, 0);
				
				if(cnt%20 < 10) printf("☆ ★ ☆ ★ ☆ ★ ☆\n");
				else 			printf("                     \n");
				
				printf("    T E T R I S\n");
				printf("\npress any key to play!!\n");
				
				if(cnt%20 < 10) printf("☆ ★ ☆ ★ ☆ ★ ☆\n");
				else			 printf("                     \n");
				
				printf("\n-------------------------------------------------------------------");
				printf("\n Q : Rotation    W: Shift    E : Rotation");
				printf("\n A : Left        S : Drop    D : Right        SPACEBAR : Hard Drop");
				printf("\n-------------------------------------------------------------------");
				Sleep(40);
				system("cls");
				hit++;
		}
		getch();
	}
	setcolor(15, 0);
	return hit; 
}
/* ------------------------------------- */

/* -------- check if top row is full -------- */
void gameover(block BLOCK, bool next){
	char YN;
	
	for(int x = 1; x < xFrame - 1; x++)
		if(display[0][x] == BLACK){
			for(;;){
				setcursortype(NOCURSOR);
				printf("GAME OVER!\n");
				printf("Your score : %d \n", score);
				printf("Play again? : Y / N \n");
				Sleep(40);
				system("cls");
				if(kbhit()){
					if((YN = getch()) == 'y'){
						score = 0;
						for(int y = 0; y < yFrame; y++)
							for(int x = 0; x < xFrame; x++)
								display[y][x] = SPACE;
						BLOCK = get_block('J');
						setFrame();
						next = false;
						break;
					}
					else if(YN = 'n')
						exit(0);
				}	
			}
		}
}
/* ------------------------------------- */

/* -------- insert a block to the display array -------- */
int (* insert_block_to_display(block BLOCK, int (*display)[xFrame]))[xFrame]
{			
	for(int Y = 0; Y < 4; Y++)
		for(int X = 0; X < 4; X++)
			if(BLOCK.square[Y][X] != SPACE)
				display[Y + BLOCK.position.y][X + BLOCK.position.x] = BLOCK.square[Y][X];
	return display; // return type of "display" is *(*)[12]
}
/* ------------------------------------- */

/* -------- delete a block from the display array -------- */
int (* delete_block_from_display(block BLOCK, int (*display)[xFrame]))[xFrame]
{		
	for(int Y = 0; Y < 4; Y++)
		for(int X = 0; X < 4; X++)
			if(BLOCK.square[Y][X] == WHITE)
				display[Y + BLOCK.position.y][X + BLOCK.position.x] = SPACE;
	
	return display; // return type of "display" is *(*)[12]
}
/* ------------------------------------- */

/* -------- rotate a block's pivot -------- */
POS rotatePivot(block BLOCK, bool isLeft){
	POS Pivot;
	if(isLeft){
		if(BLOCK.pivot.y == 1 && BLOCK.pivot.x == 1)	  Pivot = {2, 1};
		else if(BLOCK.pivot.y == 1 && BLOCK.pivot.x == 2) Pivot = {1, 1};
		else if(BLOCK.pivot.y == 2 && BLOCK.pivot.x == 2) Pivot = {1, 2};
		else if(BLOCK.pivot.y == 2 && BLOCK.pivot.x == 1) Pivot = {2, 2};
	}
	else{
		if(BLOCK.pivot.y == 1 && BLOCK.pivot.x == 1)	  Pivot = {1, 2};
		else if(BLOCK.pivot.y == 1 && BLOCK.pivot.x == 2) Pivot = {2, 2};
		else if(BLOCK.pivot.y == 2 && BLOCK.pivot.x == 2) Pivot = {2, 1};
		else if(BLOCK.pivot.y == 2 && BLOCK.pivot.x == 1) Pivot = {1, 1};
	}
	return Pivot;
}
/* ------------------------------------- */

/* -------- check if rotation is possible ------- */
bool rotation_possible_checker(block BLOCK){
	int rotated_y, rotated_x;
	if(BLOCK.rotation == -1){ 		
        // check if left rotation is possible
        for(int y = 0; y < 4; y++)
            for(int x = 0; x < 4; x++){
            	rotated_y = BLOCK.position.y + (x);
        		rotated_x = BLOCK.position.x + (3 - y);
                if(BLOCK.square[y][x] == WHITE)
                    if((rotated_y > yFrame - 1) || (rotated_y < 0 ) || (rotated_x > xFrame - 1) || (rotated_x < 0) ||
						display[rotated_y][rotated_x] == BLACK || display[rotated_y][rotated_x] == GRAY)
                    	return false;
            }
    }
    else if(BLOCK.rotation == 1){
    	// check if right rotation is possible
        for(int y = 0; y < 4; y++)
            for(int x = 0; x < 4; x++){
            	rotated_y = BLOCK.position.y + (x);
        		rotated_x = BLOCK.position.x + (3 - y);
                if(BLOCK.square[y][x] == WHITE)
                    if((rotated_y > yFrame - 1) || (rotated_y < 0 ) || (rotated_x > xFrame - 1) || (rotated_x < 0) ||
						display[rotated_y][rotated_x] == BLACK || display[rotated_y][rotated_x] == GRAY)
                    	return false;
            }
	}
	delete_block_from_display(BLOCK, display);
	
	return true;
}
/* ------------------------------------- */

/* -------- rotate a block	-------- */
block rotate_block(block BLOCK){
	if(BLOCK.name == 'O') return BLOCK; // block "O" has rotation symmetry.
		
	block rotatedBlock;
	rotatedBlock.name = BLOCK.name;
	rotatedBlock.xLength = BLOCK.yLength;
	rotatedBlock.yLength = BLOCK.xLength;
	POS blockPivot, rotatedBlockPivot;
	// left rotation //	
	if(BLOCK.rotation == -1){ 		
        for(int y = 0; y < 4; y++)
			for(int x = 0; x < 4; x++)
				rotatedBlock.square[y][x] = BLOCK.square[x][3-y];
				
		rotatedBlock.rotation = BLOCK.rotation + 1;
		rotatedBlock.pivot = rotatePivot(BLOCK, true);
		int dx = rotatedBlock.pivot.x - BLOCK.pivot.x;
		int dy = rotatedBlock.pivot.y - BLOCK.pivot.y;		

		rotatedBlock.position.x = BLOCK.position.x - dx;
		rotatedBlock.position.y = BLOCK.position.y - dy;
	}
	// right rotation //
	else if (BLOCK.rotation == 1) { 
		for(int y = 0; y < 4; y++)
			for(int x = 0; x < 4; x++)
				rotatedBlock.square[y][x] = BLOCK.square[3-x][y];

		rotatedBlock.rotation = BLOCK.rotation - 1;
		rotatedBlock.pivot = rotatePivot(BLOCK, false);
		int dx = rotatedBlock.pivot.x - BLOCK.pivot.x;
		int dy = rotatedBlock.pivot.y - BLOCK.pivot.y;
		
		rotatedBlock.position.x = BLOCK.position.x- dx;
		rotatedBlock.position.y = BLOCK.position.y- dy;		
	}
		
	return rotatedBlock;
}
/* ------------------------------------- */

/* -------- if the block can move vertically, then returns TRUE -------- */
bool vertical_move_checker(block BLOCK){
	bool OK = true;
	delete_block_from_display(BLOCK, display);
	for(int Y = 0; Y < 4; Y++){
		for(int X = 0; X < 4; X++){
			if(BLOCK.square[Y][X] == WHITE)
				if( display[Y + BLOCK.position.y + 1][X + BLOCK.position.x] == GRAY)
					OK = false;
				else if(display[Y + BLOCK.position.y + 1][X + BLOCK.position.x] == BLACK)
					OK = false;
		}
	}
	return OK;
}
/* ------------------------------------- */

int long_vertical_move_checker(block BLOCK){
	insert_block_to_display(BLOCK, display);
	int y_min = yFrame - 2;
	int return_value;
	for(int Y = 0; Y < 4; Y++)
		for(int X = 0; X < 4; X++)
			if(BLOCK.square[Y][X] == WHITE)
				for(int delta_y = yFrame - 2; display[delta_y][X + BLOCK.position.x] != SPACE
				|| display[delta_y - 1][X + BLOCK.position.x] != SPACE || display[delta_y - 2][X + BLOCK.position.x] != SPACE; delta_y--)
					if(y_min > delta_y) y_min = delta_y;

	delete_block_from_display(BLOCK, display);
	return (return_value = y_min - 4) > BLOCK.position.y ? return_value : BLOCK.position.y ;
}

/* -------- if the block can move horizontally, then returns TRUE -------- */
bool horizontal_move_checker(block BLOCK, bool isLeft){
	bool OK = true;
	for(int Y = 0; Y < 4; Y++)
		for(int X = 0; X < 4; X++)
			if (BLOCK.square[Y][X] == WHITE)
			 if( isLeft && (display[Y + BLOCK.position.y][X + BLOCK.position.x - 1] == GRAY || display[Y + BLOCK.position.y][X + BLOCK.position.x - 1] == BLACK))
			 	OK = false;
			else if( !isLeft && (display[Y + BLOCK.position.y][X + BLOCK.position.x + 1] == GRAY || display[Y + BLOCK.position.y][X + BLOCK.position.x + 1] == BLACK))
			 	OK = false;
	return OK;			
}
/* ------------------------------------- */

/* -------- control a block	-------- */
block control(block &BLOCK){
	if(vertical_move_checker(BLOCK)){
		delete_block_from_display(BLOCK, display);	
		BLOCK.position.y++;
		if (kbhit()){
			switch(char key = getch()){
				case 'w':
						BLOCK.position.y--;	
					break;
				case 's':
					if(vertical_move_checker(BLOCK))
						BLOCK.position.y++;	
					break;
				case 'a':
					if(horizontal_move_checker(BLOCK, true))
						BLOCK.position.x--;	
					break;	
				case 'd':
					if(horizontal_move_checker(BLOCK, false))
						BLOCK.position.x++;	
					break;
				case 'q': //left rotation
					if(horizontal_move_checker(BLOCK, true))
						BLOCK.rotation--;
					break;
				case 'e': //right rotation
					if(horizontal_move_checker(BLOCK, false))
						BLOCK.rotation++;
					break;
				case ' ':
					BLOCK.position.y = long_vertical_move_checker(BLOCK);
					while(vertical_move_checker(BLOCK))
						BLOCK.position.y++;	
                    break;   	
			}
		}
	}
	
	if(BLOCK.rotation && rotation_possible_checker(BLOCK)) BLOCK = rotate_block(BLOCK);
	return BLOCK;
}
/* ------------------------------------- */

/* -------- draw the display array and shows the score -------- */
void draw(int (*display)[xFrame]){
	setcursortype(NOCURSOR);
	
	for(int Y = 0; Y < yFrame; Y++){
		for(int X = 0; X < xFrame; X++)
			if(display[Y][X] == SPACE)
				printf("  ");
			else if(display[Y][X] == WHITE)
				printf("□");
            else if(display[Y][X] == BLACK)
                printf("■");
            else if(display[Y][X] == GRAY)
                printf("▩");
		printf("\n");
	}
	
	printf("\n ★☆  SCORE : %d  ☆★\n", score);
	printf("\n-------------------------------------------------------------------");
	printf("\n Q : Rotation    W: Shift    E : Rotation");
	printf("\n A : Left        S : Drop    D : Right        SPACEBAR : Hard Drop");
	printf("\n-------------------------------------------------------------------");
	int sleeptime = (300 - 10 * score) > 0 ? (300 - 10 * score) : 10;
	Sleep(sleeptime);
	system("cls");	
}
/* ------------------------------------- */

/* -------- checks if the horizontal line is full, and then encodes the information of full floors -------- */
int line_checker(void){
	int checked_floor;
	int decimal_encoding = 0;
	const int negative = -1;
	
	for(int Y = yFrame - 2; Y > 0; Y--){
		checked_floor = (yFrame - 2) - Y + 1;	//starts from bottom floor(1 st), and goes upto top floor(yFrame - 2 th)
	
		for(int X = 1; X < xFrame - 1; X++){
			if (display[Y][X] == SPACE){	
				checked_floor = negative;
			}
		}
		
		if(checked_floor > 0){
			decimal_encoding = decimal_encoding + pow(10, checked_floor - 1);
			score++;
		}
	}
	
	return decimal_encoding;
}
/* ------------------------------------- */

/* -------- decodes the information about full floors, and then deletes them -------- */
void line_eraser(int decimal_encoding){
	if(decimal_encoding > -1){
		for(int y = yFrame - 2; y > 0; y--, decimal_encoding /= 10){
			if(decimal_encoding % 10 == 1){	
				for(int Y = y; Y > 0; Y--)
					for(int X = 1; X < xFrame - 1; X++)
						display[Y][X] = display[Y-1][X];		
			}
		}
	}
}
/* ------------------------------------- */

/* -------- initialize square array -------- */
block INIT_SQUARE(block & BLOCK){
	for(int Y = 0; Y < 4; Y++)
		for(int X = 0; X < 4; X++)
			BLOCK.square[Y][X] = 0;
	return BLOCK;		
}
/* ------------------------------------- */

/* -------- generate a random charactor for the next block -------- */
char generate_random_char(void){
	srand(time(0));
	int num = rand()%7;
	
	switch(num){
		case 0 : return 'I'; break;
		case 1 : return 'J'; break;
		case 2 : return 'L'; break;
		case 3 : return 'O'; break;
		case 4 : return 'S'; break;
		case 5 : return 'T'; break;
		case 6 : return 'Z'; break;
		default : return 'J'; break;
	}	
}
/* ------------------------------------- */

/* -------- change the color of block -------- */
void change_block_color(block &BLOCK){
	for(int Y = 0; Y < 4; Y++)
		for(int X = 0; X < 4; X++)
			if(BLOCK.square[Y][X] == WHITE)
				BLOCK.square[Y][X] = BLACK;
}
/* ------------------------------------- */

/* -------- generates a block -------- */
block get_block(char Char){
	
	block I;
	I.name = 'I';
	I.position = {0, xFrame/2 -2};
	I.pivot = {1, 1};
	I.rotation = 0;
	I.xLength = 1;
	I.yLength = 4;
	INIT_SQUARE(I);
	I.square[0][1] = WHITE;	//	□
	I.square[1][1] = WHITE;	//	□
	I.square[2][1] = WHITE;	//	□
	I.square[3][1] = WHITE;	//	□

	block J;
	J.name = 'J';
	J.position = {0, xFrame/2 -2};
	J.pivot = {1, 1};
	J.rotation = 0;
	J.xLength = 2;
	J.yLength = 3;
	INIT_SQUARE(J);
	J.square[0][1] = WHITE;	//	  □
	J.square[1][1] = WHITE;	//	  □
	J.square[2][1] = WHITE;	//	□□
	J.square[2][0] = WHITE;
	
	block L;
	L.name = 'L';
	L.position = {0, xFrame/2 -2};
	L.pivot = {1, 1};
	L.rotation = 0;
	L.xLength = 2;
	L.yLength = 3;
	INIT_SQUARE(L);
	L.square[0][0] = WHITE;	//	□□
	L.square[0][1] = WHITE;	//	  □
	L.square[1][1] = WHITE;	//    □
	L.square[2][1] = WHITE;
	
	block O;
	O.name = 'O';
	O.position = {0, xFrame/2 -2};
	O.pivot = {1, 1};
	O.rotation = 0;
	O.xLength = 2;
	O.yLength = 2;
	INIT_SQUARE(O);
	O.square[0][0] = WHITE;	//	□ □
	O.square[0][1] = WHITE;	//	□ □
	O.square[1][0] = WHITE;
	O.square[1][1] = WHITE;
	
	block S;
	S.name = 'S';
	S.position = {0, xFrame/2 -2};
	S.pivot = {1, 1};
	S.rotation = 0;
	S.xLength = 2;
	S.yLength = 3;
	INIT_SQUARE(S);
	S.square[0][0] = WHITE;	//	□ 
	S.square[1][0] = WHITE;	//	□ □  
	S.square[1][1] = WHITE;	//     □
	S.square[2][1] = WHITE;
	
	block T;
	T.name = 'T';
	T.position = {0, xFrame/2 -2};
	T.pivot = {1, 1};
	T.rotation = 0;
	T.xLength = 2;
	T.yLength = 3;
	INIT_SQUARE(T);
	T.square[0][1] = WHITE;	//    □
	T.square[1][0] = WHITE;	//	□□
	T.square[1][1] = WHITE;  //	  □
	T.square[2][1] = WHITE;

	block Z;
	Z.name = 'Z';
	Z.position = {0, xFrame/2 -2};
	Z.pivot = {1, 1};
	Z.rotation = 0;
	Z.xLength = 2;
	Z.yLength = 3; 
	INIT_SQUARE(Z);
	Z.square[0][1] = WHITE;	//		□
	Z.square[1][0] = WHITE;	//	 □ □
	Z.square[1][1] = WHITE;	//   □
	Z.square[2][0] = WHITE;
	
	block frame_left;
	frame_left.position.x = 0;
	frame_left.position.y = 0;
	frame_left.xLength = 1;
	frame_left.yLength = 4;
	INIT_SQUARE(frame_left);
	frame_left.square[0][0] = GRAY;	//	■
	frame_left.square[1][0] = GRAY;	//	■
	frame_left.square[2][0] = GRAY;	//	■
	frame_left.square[3][0] = GRAY;	//	■
	
	block frame_right;
	frame_right.position.x = xFrame - 4;
	frame_right.position.y = 0;
	frame_right.xLength = 1;
	frame_right.yLength = 4;
	INIT_SQUARE(frame_right);
	frame_right.square[0][3] = GRAY;	//	■
	frame_right.square[1][3] = GRAY;	//	■
	frame_right.square[2][3] = GRAY;	//	■
	frame_right.square[3][3] = GRAY;	//	■

	block frame_bottom;
	frame_bottom.position.x = 0;
	frame_bottom.position.y = yFrame - 4;
	frame_bottom.xLength = 1;
	frame_bottom.yLength = 4;
	INIT_SQUARE(frame_bottom);
	frame_bottom.square[3][0] = GRAY;	//	■
	frame_bottom.square[3][1] = GRAY;	//	■
	frame_bottom.square[3][2] = GRAY;	//	■
	frame_bottom.square[3][3] = GRAY;	//	■	
		
	switch(Char){
		case 'I' : return I; break;
		case 'J' : return J; break;
		case 'L' : return L; break;
		case 'O' : return O; break;
		case 'S' : return S; break;
		case 'T' : return T; break;
		case 'Z' : return Z; break;
		case 'l' : return frame_left; break;
		case 'r' : return frame_right; break;
		case 'b' : return frame_bottom; break;
		default  : return S; break;
	}
}
/* ------------------------------------- */

/* -------- sets the type of cursor -------- */
void setcursortype(CURSOR_TYPE c){
     CONSOLE_CURSOR_INFO CurInfo;
 
     switch (c) {
     case NOCURSOR:
          CurInfo.dwSize=1;
          CurInfo.bVisible=FALSE;
          break;
     case SOLIDCURSOR:
          CurInfo.dwSize=100;
          CurInfo.bVisible=TRUE;
          break;
     case NORMALCURSOR:
          CurInfo.dwSize=20;
          CurInfo.bVisible=TRUE;
          break;
     }
     SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
/* -------- 		END		 -------- */




