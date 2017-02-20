#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <chrono>
#include <random>
#include "rlutil.h"

#define NUM_LINES 5  // Number of lines printed in second screen
#define MAX_GUESS 9  // Maximum number of guesses
#define HINT_GUESS 4 // Number of guesses remaining when hint is given

using namespace std;
using namespace rlutil;

char mname[100];            // Stores actual name of movie
char mname2[100];           // Stores UPPERCASE version of movie name, to validate answers against
char mguess[100];           // Stores currently guessed movie name; Non-guessed characters replaced by '_'
char guessed[100];          // Stores guessed letters
int num_guess = MAX_GUESS;  // Number of guesses/lives provided at start
int status = 0;
int hint_given = 0;

void init();                // Initializes game via user input
void init_auto();           // Initializes game via automatic file read
void paint();               // Re-paints the game UI on call
void play(char = '\0');     // Takes user input and validates it
void frame();               // Draws frame around screen on call
void hint();

void prt_cntr(string);      // Prints given string to center of screen

int main(void)
{
	start:

	cls();
	rlutil::setColor(WHITE);

	cout << "Choose game mode\n\n1. Against COM\n2. Against human\n\nEnter your choice : ";
	char inp = getch();

	switch (inp){
    case '1':
        init_auto();
        break;
    case '2':
        init();
        break;
    default:
        rlutil::setColor(LIGHTRED);
        cout << "\n\nInvalid Choice!! Please try again!!";
        getch();
        goto start;
	}


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
	rlutil::setColor(WHITE);
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

void init_auto()
{
	cls();
	rlutil::setColor(WHITE);

	ifstream movie ("movie.txt", ios_base::in);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::uniform_int_distribution<int> distribution(1,217);

    int line = distribution(generator);

    string mov_inp;

    for(int q = 0; q < line; ++q){
        getline(movie, mov_inp);
    }

    strcpy(mname, mov_inp.c_str());

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
    prt_cntr("Movie chosen! Press any key to continue");
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
    if((MAX_GUESS-num_guess)!=0){
        cout << hol.substr(0,(MAX_GUESS-num_guess+1));
    }
    else{
        cout << ' ';
    }

    setColor(WHITE);
    cout << hol.substr((MAX_GUESS-num_guess+1), hol.length());

	cout << "\n\n";

	size = 2 * strlen(mguess) - 1;
	gotoxy( (width - size)/2 + 2, (height - NUM_LINES + 4)/2);

	for(unsigned k = 0; k < strlen(mguess); k++)
	{
		cout << mguess[k] << ' ';
	}
	cout << "\n\n";

	string s = "Number of guesses remaining: ";
	s = s.append(to_string(num_guess));
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
        prt_cntr(s2);
		getch();
        exit(0);
	}
}

void play(char a)
{
    int n = 0, i = 0, j = 0, k = 0, num_match = 0, is_guessed = 0;
    char inp;
    if(a=='\0'){
        do
        {
            inp = getch();
            inp = toupper(inp);
        }
        while(!(inp >= 'A' && inp <= 'z'));

        switch(inp){
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                goto skipped;
        }
    }
    else{
        a = toupper(a);
        inp = a;
    }

    for(j = 0; j < strlen(mname); j++)
    {
        if((int) inp == mname2[j])
        {
            mguess[j] = mname[j];
            num_match++;
        }
    }

	is_guessed = 0;

    for(i = 0; i < strlen(guessed); i++)
    {
        if((int)inp == guessed[i])
        {
            is_guessed = 1;
            break;
        }
    }

	if(num_match == 0 && !is_guessed)
	{
		num_guess--;
        if(num_guess == HINT_GUESS && hint_given == 0){
            hint();
        }
	}

    for(k = 0; k < strlen(mguess); k++)
    {
        if(mguess[k] == '_')
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
    skipped:
        ;
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

void hint(){
	int r;

	rlutil::setColor(LIGHTBLUE);
	cout << endl;
	prt_cntr("You are running low on guesses! Take a hint from us");
	cout << endl;
	rlutil::setColor(WHITE);
	getch();

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    std::uniform_int_distribution<int> distribution(0,strlen(mname));

	rand:
		r = distribution(generator);
		cout << r;
		if(mguess[r] == '_'){
			play(mname[r]);
			hint_given ++;
		}
		else{
			goto rand;
		}
}

void prt_cntr(string str){

	int height = rlutil::trows();
	int width = rlutil::tcols();

    cout << '*' << string( (width-str.size())/2, ' ' ) << str << std::endl;
}
