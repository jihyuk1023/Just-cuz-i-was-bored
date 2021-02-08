#include <iostream>
#include <time.h>
#include <cmath>
#include <string>
#include <windows.h>

#define LENGTH 31
#define HALF LENGTH/2

using namespace std;
const double PI = 3.1415926;

typedef struct __time_to_rad__
{
    double sec_rad;
    double min_rad;
    double hour_rad;
}time_to_rad;

struct tm * get_time(void);
time_to_rad calc_angle(struct tm *);
void display(time_to_rad);

int main(){
    
    int clk;
    while(true){
        display(calc_angle(get_time()));
        
        Sleep(500);
        system("cls");
//        for(clk = get_time()->tm_sec ; ; )
//        	if (clk != get_time()->tm_sec)  break;
//        	else                         continue;
    }
    return 0;
}

struct tm * get_time(void){
    time_t curTime = time(NULL);
    struct tm *pLocal = localtime(&curTime);
    if (pLocal == NULL) cout << "Failed to convert the current time" << endl;
    return pLocal;
}

time_to_rad calc_angle(struct tm *pLocal){
    
    time_to_rad RADIAN;

    RADIAN.sec_rad = pLocal->tm_sec * 2*PI/60;
    RADIAN.min_rad = pLocal->tm_min * 2*PI/60;
    RADIAN.hour_rad = pLocal->tm_hour * 2*PI/12 + (pLocal->tm_min * 2*PI/60)/12;
    return RADIAN;
}

void display(time_to_rad RADIAN){
    char clock[LENGTH][LENGTH];
    // 2nd dimension array initialization
    for(int y = 0; y < LENGTH; y++)
        for(int x = 0; x < LENGTH; x++)
        	if (x == 0 || x == LENGTH - 1 || y == 0 || y == LENGTH - 1)
        		clock[y][x] = '+';
        	else if (x == 1 && y == HALF)
        		clock[y][x] = '9';
        	else if (x == LENGTH - 2 && y == HALF)
        		clock[y][x] = '3';
			else if (x == HALF + 1 && y == 1)
        		clock[y][x-1] = '1', clock[y][x] = '2';
			else if (x == HALF && y == LENGTH - 2)
        		clock[y][x] = '6';			
        	else
            	clock[y][x] = ' ';    	
        
	double sec_rad = RADIAN.sec_rad;
    double sec_x = sin(sec_rad);
    double sec_y = -cos(sec_rad);

	double min_rad = RADIAN.min_rad;
    double min_x = sin(min_rad);
    double min_y = -cos(min_rad);
	
	double hour_rad = RADIAN.hour_rad;
    double hour_x = sin(hour_rad);
    double hour_y = -cos(hour_rad);
    
    // insert second, minute, hour coordinate points to 2nd dimension array.
    for(int i = 0; i <= HALF; i++){
        clock[int(sec_y * i) + HALF][int(sec_x * i) + HALF] = '.';
        if (i < HALF)
        	clock[int(min_y * i) + HALF][int(min_x * i) + HALF] = '*';
        if (i < HALF - 2)
        	clock[int(hour_y * i) + HALF][int(hour_x * i) + HALF] = 'o';
    }

	// display the array.
    for(int y = 0; y < LENGTH; y++){
        for(int x = 0; x < LENGTH; x++){
            cout << clock[y][x] << " ";
        }
        cout << endl;
    }
}


