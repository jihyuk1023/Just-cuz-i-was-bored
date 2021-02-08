#include <iostream>
#include <string>
#include <time.h>
#define LINEHEIGT 5
#define WORDLENGTH 7
// https://calvinjmkim.tistory.com/31 //
using namespace std;

typedef struct strc_digit{
    string line[LINEHEIGT][WORDLENGTH]; 
    // * * * *
    // *     *
    // * * * *
    // *     *
    // * * * *
} digit;

struct tm * get_time(void);
void display(struct tm *);
strc_digit number(int);

int main(){
    int clk;

    while(true){
        display(get_time());
        
        for(clk = get_time()->tm_sec ; ; )
        	if (clk != get_time()->tm_sec) break;
        	else		                continue;
    }
    return 0;
}

struct tm * get_time(void){
    time_t curTime = time(NULL);
    struct tm *pLocal = localtime(&curTime);
    if (pLocal == NULL) cout << "Failed to convert the current time" << endl;
    return pLocal;
}

void display(struct tm *pLocal){
    printf("%04d-%02d-%02d  %02d:%02d:%02d\n",  
    pLocal->tm_year + 1900, pLocal->tm_mon + 1, pLocal->tm_mday,  
    pLocal->tm_hour, pLocal->tm_min, pLocal->tm_sec);

    int hour2 = pLocal -> tm_hour / 10;
    int hour1 = pLocal -> tm_hour - hour2 * 10;
    int min2 = pLocal -> tm_min / 10;
    int min1 = pLocal -> tm_min - min2 * 10;
    int sec2 = pLocal -> tm_sec / 10;
    int sec1 = pLocal -> tm_sec - sec2 * 10;

    strc_digit am_pm2 = (pLocal -> tm_hour < 12) ? number('A') : number('P');
    strc_digit am_pm1 = number('M');
    strc_digit colon = number(':');
    strc_digit digit[6] = {number(sec1), number(sec2), number(min1), number(min2), number(hour1), number(hour2)};
 
    for (int line = 0; line < LINEHEIGT; line++){
        cout << 
        *am_pm2.line[line] << "   " << *am_pm1.line[line] << "         " <<
        *digit[5].line[line] << "   " << *digit[4].line[line] << " " << *colon.line[line] << " " <<
        *digit[3].line[line] << "   " << *digit[2].line[line] << " " << *colon.line[line] << " " << 
        *digit[1].line[line] << "   " << *digit[0].line[line]
        << endl;
    }
}

strc_digit number(int n){

    digit zero;
    *zero.line[0] = {"* * * *"};
    *zero.line[1] = {"*     *"};
    *zero.line[2] = {"*     *"};
    *zero.line[3] = {"*     *"};
    *zero.line[4] = {"* * * *"};

    digit one;
    *one.line[0] = {"   *   "};
    *one.line[1] = {"   *   "};
    *one.line[2] = {"   *   "};
    *one.line[3] = {"   *   "};
    *one.line[4] = {"   *   "};

    digit two;
    *two.line[0] = {"* * * *"};
    *two.line[1] = {"      *"};
    *two.line[2] = {"* * * *"};
    *two.line[3] = {"*      "};
    *two.line[4] = {"* * * *"};

    digit three;
    *three.line[0] = {"* * * *"};
    *three.line[1] = {"      *"};
    *three.line[2] = {"* * * *"};
    *three.line[3] = {"      *"};
    *three.line[4] = {"* * * *"};

    digit four;
    *four.line[0] = {"*     *"};
    *four.line[1] = {"*     *"};
    *four.line[2] = {"* * * *"};
    *four.line[3] = {"      *"}; 
    *four.line[4] = {"      *"}; 
     
    digit five; 
    *five.line[0] = {"* * * *"};
    *five.line[1] = {"*      "};
    *five.line[2] = {"* * * *"};
    *five.line[3] = {"      *"};
    *five.line[4] = {"* * * *"};

    digit six;
    *six.line[0] = {"* * * *"};
    *six.line[1] = {"*      "};
    *six.line[2] = {"* * * *"};
    *six.line[3] = {"*     *"};
    *six.line[4] = {"* * * *"};

    digit seven;
    *seven.line[0] = {"* * * *"};
    *seven.line[1] = {"      *"};
    *seven.line[2] = {"      *"};
    *seven.line[3] = {"      *"};
    *seven.line[4] = {"      *"};

    digit eight;
    *eight.line[0]= {"* * * *"};
    *eight.line[1]= {"*     *"};
    *eight.line[2]= {"* * * *"};
    *eight.line[3]= {"*     *"};
    *eight.line[4] = {"* * * *"};

   digit nine;
    *nine.line[0] = {"* * * *"};
    *nine.line[1] = {"*     *"};
    *nine.line[2] = {"* * * *"};
    *nine.line[3] = {"      *"};
    *nine.line[4] = {"* * * *"};

    digit A;
    *A.line[0] = {" * * * "};
    *A.line[1] = {"*     *"};
    *A.line[2] = {"* * * *"};
    *A.line[3] = {"*     *"};
    *A.line[4] = {"*     *"};

    digit P;
    *P.line[0] = {"* * *  "};
    *P.line[1] = {"*     *"};
    *P.line[2] = {"* * *  "};
    *P.line[3] = {"*      "};
    *P.line[4] = {"*      "};

    digit M;
    *M.line[0] = {"*     *"};
    *M.line[1] = {"* * * *"};
    *M.line[2] = {"*  *  *"};
    *M.line[3] = {"*     *"};
    *M.line[4] = {"*     *"};

    digit COLON;
    *COLON.line[0] = {"       "};
    *COLON.line[1] = {"   *   "};
    *COLON.line[2] = {"       "};
    *COLON.line[3] = {"   *   "};
    *COLON.line[4] = {"       "};

    switch (n)
    {
    case 0:        return zero;       break;    
    case 1:        return one;        break;
    case 2:        return two;        break;
    case 3:        return three;      break;
    case 4:        return four;       break;
    case 5:        return five;       break;
    case 6:        return six;        break;
    case 7:        return seven;      break;
    case 8:        return eight;      break;
    case 9:        return nine;       break;

    case 58:       return COLON;      break;
    case 65:       return A;          break;
    case 77:       return M;          break;
    case 80:       return P;          break;
    default:       return zero;       break;
    }
}



