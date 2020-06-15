#include <iostream>
#include <ncurses.h>
#include <unistd.h> //usleep


int ncolors = 7; //7 diff colors
int W_HEIGHT, W_WIDTH; //width and height of the terminal

struct dvd_logo{
public: 
    const int width = 31, height = 9;
    int x = 1, y = 1, xdir = 1, ydir = 1, cc = 1; //cc: color_counter

    const bool logo [9][31] = {
            {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0},
            {0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0},
            {0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1},
            {1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0},
            {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
            {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0}
    };
    

    void print(){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                wmove(stdscr ,y+i, x+j);
                if(logo[i][j]){
                    addch(ACS_CKBOARD);
                }else{
                    addch(' '); 
                }
            }      
        }
    }
    void move(){
        if( x == 0 || x+width == W_WIDTH ){
            xdir *= -1;
            collision();
        }
        if( y == 0 || y+height == W_HEIGHT ){
            ydir *= -1;
            collision();
        }

        x+=xdir;
        y+=ydir;
    }
    void collision(){ //called when the logo collided with the border
        if(cc == ncolors+1) cc = 1;

        if(cc)
            //need to attr off the prev color if its not the first
            attroff(COLOR_PAIR(cc%ncolors-1));
        
        attron(COLOR_PAIR(cc%ncolors));
        refresh();
        cc++;
    }

};

void init_colors(){
    start_color();

    /*
        COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7
    */

    //id, fg, bg
    init_pair(1, 1, 0);
    init_pair(2, 2, 0);
    init_pair(3, 3, 0);
    init_pair(4, 4, 0);
    init_pair(5, 5, 0);
    init_pair(6, 6, 0);
    init_pair(7, 7, 0);

}


int main(){

    initscr();
    noecho();
    raw();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);
    getmaxyx(stdscr, W_HEIGHT, W_WIDTH);

    init_colors();

    dvd_logo dl;

    int c;
    int y = 0, x = 0;

    while( (c = getch() != 27)){
        erase();

        dl.move();
        dl.print();

        refresh();
        usleep(200000);

    }
    endwin();
    return 0;
}