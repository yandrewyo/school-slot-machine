// base code file

#include "Andrew.h"

//using namespace std;

void drawTexts() {
    string title = "SLOT MACHINE";
    gotoxy(40 - title.length()/2 + 1, 3);
    cout << title;

    string instructions = "Instructions: Press ENTER to stop and spin, Q to quit. 50 cents per spin.";
    gotoxy(40 - instructions.length()/2, 5);
    cout << instructions;
    string jackpots = "Jackpots: 2 of a kind = $0.50, 3 of a kind = $3, ALL 7's = $10";
    gotoxy(40 - jackpots.length()/2, 6);
    cout << jackpots;
}

void updatePurse(float money) {
    string purse = "Money: $" + to_string(money).substr(0, to_string(money).find(".")+3);
    gotoxy(40-purse.length()/2, 8);
    cout << "Money: $" << to_string(money).substr(0, to_string(money).find(".")+3);
}

void drawSlots(bool first) {
    string num = "99";
    float money = 5;
    string values[3];
    string msg;
    while (true) {
        system("clear");
        drawFramedBox(1,1,80,24,'*');

        drawFramedBox(8, 15, 5, 5, '*');
        drawFramedBox(38, 15, 5, 5, '*');
        drawFramedBox(68, 15, 5, 5, '*');

        updatePurse(money);
        drawTexts();

        if (!first) {
            money -= 0.5;
            money = floor(money*100+0.5)/100;
            updatePurse(money);
            while (!kbhit()) {
                for (int i = -30; i <= 30; i+=30) {
                    num = to_string(random(9));
                    values[(i+30)/30] = num;
                    gotoxy(40-num.length()/2+i, 17);
                    cout << "  ";
                    gotoxy(40-num.length()/2+i, 17);
                    cout << num;
                }
                gotoxy(1,1);
            }
            getch();
            if (values[0] == values[1] && values[1] == values[2]) {
                if (values[0] == "7") {
                    msg = "ALL 7'S!!! (+$10)";
                    gotoxy(40-msg.length()/2, 10);
                    cout << msg;
                    money += 10;
                    money = floor(money*100+0.5)/100;
                    updatePurse(money);
                } else {
                    msg = "THREE OF A KIND!!! (+$3)";
                    gotoxy(40-msg.length()/2, 10);
                    cout << msg;
                    money += 3;
                    money = floor(money*100+0.5)/100;
                    updatePurse(money);
                }
            } else {
                if (values[0] == values[1] || values[1] == values[2] || values[0] == values[2]) {
                    msg = "TWO OF A KIND!!! (+$0.50)";
                    gotoxy(40-msg.length()/2, 10);
                    cout << msg;
                    money += 0.50;
                    money = floor(money*100+0.5)/100;
                    updatePurse(money);
                }
            }
            if (getch() == 'q' || money <= 0) {
                break;
            }
        } else {
            getch();
            first = false;
        }
    }
}

int main()
{
    srand(time(NULL));
    drawSlots(true);
}
