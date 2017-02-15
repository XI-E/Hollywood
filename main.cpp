#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include "rlutil.h"

#define NUM_LINES 5  // Number of lines printed in second screen
#define MAX_GUESS 9  // Maximum number of guesses
#define HINT_GUESS 4 // Number of guesses remaining when hint is given

using namespace std;
using namespace rlutil;

char mname[100];
char mname2[100];
char mguess[100];
char guessed[100];
int num_guess = MAX_GUESS;
int status = 0;
int hint_given = 0;

void init();
void paint();
void play();
void frame();
void prt_cntr(string);

int main(void)
{
	cls();

	init();

	while(1)
	{
	   paint();

	   play();
	}

	return 0;
}

void init()
{
	cls();
	cout << "Enter the name of the movie\n";
	cin.getline(mname, 100, '\n');

	for(int i = 0; i < strlen(mname); i++)
	{
		mname2[i] = toupper(mname[i]);

		if(isalpha(mname[i]))
		{
			switch(mname[i])
			{
                case 'A': case 'a':
				case 'E': case 'e':
				case 'I': case 'i':
				case 'O': case 'o':
				case 'U': case 'u':
					mguess[i] = mname[i];
					break;
				default:
					mguess[i] = '_';
			}
		}
		else if(mname[i] == ' ')
		{
			mguess[i] = '/';
		}
		else
		{
			mguess[i] = mname[i];
		}
	}

	mguess[strlen(mname)] = '\0';

	cout << endl;
    prt_cntr("Press any key to continue");
	getch();
	cls();
}

void paint()
{
	cls();

	frame();

	int size;
	int height = rlutil::trows() - 2;
	int width = rlutil::tcols() - 2;

	gotoxy(2,(height - NUM_LINES)/2);

	gotoxy((width - 7) / 2, (height - NUM_LINES)/2);
	string hol = " HOLLYWOOD";

    setColor(LIGHTRED);
    cout << hol.substr(0,(MAX_GUESS-num_guess));

    setColor(WHITE);
    cout << hol.substr((MAX_GUESS-num_guess), hol.length());

	cout << "\n\n";

	size = 2 * strlen(mguess) - 1;
	gotoxy( (width - size)/2 + 2, (height - NUM_LINES + 4)/2);

	for(unsigned k = 0; k < strlen(mguess); k++)
	{
		cout << mguess[k] << ' ';
	}
	cout << "\n\n";

	string s = "Number of guesses remaining: ";
	char ss[17];
	itoa(num_guess, ss, 10);
	s = s.append(ss);
	prt_cntr(s);

	if(status == 1)
	{
		setColor(LIGHTGREEN);
		gotoxy(0,4);
		prt_cntr("YOU WON!!");
		getch();
		exit(0);
	}
	else if(num_guess == 0)
	{
		setColor(LIGHTRED);
		gotoxy(0, 4);
		prt_cntr("YOU LOST!\n");

		string s2 = "The correct answer was ";
        s2 = s2.append(string(mname));
        prt_cntr(s);
		getch();
        exit(0);
	}
}

void play()
{
	char inp;
	do
	{
		inp = getch();
		inp = toupper(inp);
	}
	while(!(inp >= 'A' && inp <= 'z'));

	int num_match = 0;
	{
        for(int i = 0; i < strlen(mname); i++)
        {
            if((int) inp == mname2[i])
            {
                mguess[i] = mname[i];
                num_match++;
            }
        }
	}

	int is_guessed = 0;
	{
        for(int i = 0; i < strlen(guessed); i++)
        {
            if((int)inp == guessed[i])
            {
                is_guessed = 1;
                break;
            }
        }
	}

	if(num_match == 0 && !is_guessed)
	{
		num_guess--;
	}

	int n = 0;
	for(int i = 0; i < strlen(mguess); i++)
	{
		if(mguess[i] == '_')
		{
			n++;
			break;
		}
	}
	if(n == 0)
	{
		status = 1;
	}
    if(is_guessed==0){
        guessed[strlen(guessed)] = (char) inp;
    }
}

void frame()
{
	int height = rlutil::trows();
	int width = rlutil::tcols();

	gotoxy(1,1);
	for(int i = 0; i < width; i++)
	{
		cout << '*';
	}

	for(int j = 2; j <= height - 2; j++)
	{
		gotoxy(1, j); cout << '*';
		gotoxy(width, j); cout << '*';
	}

	gotoxy(1, height - 1);
	for(int k = 0; k < width; k++)
	{
		cout << '*';
	}
}

void prt_cntr(string str){

	int height = rlutil::trows();
	int width = rlutil::tcols();

    cout << '*' << string( (width-str.size())/2, ' ' ) << str << std::endl;
}
