#include <iostream.h>
#include <conio.h>
#include <process.h>
#include <dos.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define NUM_LINES 5  // Number of lines printed in second screen
#define MAX_GUESS 9  // Maximum number of guesses
#define HINT_GUESS 4 // Number of guesses remaining when hint is given

char mname[100];
char mguess[100];
char guessed[100];
int num_guess = MAX_GUESS;
int status = 0;
int hint_given = 0;

void init();
void paint();
void play();
void frame();

void main()
{
	clrscr();

	init();

	while(1)
	{
	   paint();

	   play();
	}
}

void init()
{
	clrscr();
	cout << "Enter the name of the movie: ";
	cin.getline(mname, 100, '\n');

	for(int i = 0; i < strlen(mname); i++)
	{
		mname[i] = toupper(mname[i]);

		if(mname[i] >= 'A' && mname[i] <= 'Z')
		{
			switch(mname[i])
			{
				case 'A':
				case 'E':
				case 'I':
				case 'O':
				case 'U':
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

	cout << "Press any key to continue";
	getch();
	clrscr();
}

void paint()
{
	clrscr();

	frame();

	int size;
	struct text_info info;
	gettextinfo(&info);
	int height = ( (int) info.screenheight) - 2;
	int width = ( (int) info.screenwidth) - 2;

	gotoxy(2,(height - NUM_LINES)/2);

	gotoxy((width - 9) / 2, wherey());
	char hol[] = "HOLLYWOOD";
	for(int i = 0; i < MAX_GUESS - num_guess; i++)
	{
		textcolor(LIGHTRED);
		cprintf("%c", hol[i]);
	}
	for( ; i < strlen(hol); i++)
	{
		char a = hol[i];
		textcolor(WHITE);
		cprintf("%c", hol[i]);
	}

	cout << "\n\n";

	size = 2 * strlen(mguess) - 1;
	gotoxy( (width - size)/2 + 1, wherey());

	for(i = 0; i < strlen(mguess); i++)
	{
		cout << mguess[i] << ' ';
	}
	cout << "\n\n";

	size = strlen("Number of guesses remaining: ") + 1;
	gotoxy( (width - size)/2 + 1, wherey());
	cout << "Number of guesses remaining: " << num_guess << endl;

	//Providing a hint
	if(num_guess == HINT_GUESS && !hint_given)
	{
		int size = strlen("You are running low on guesses! Take a hint from us");
		gotoxy((width - size)/2, wherey());
		textcolor(LIGHTBLUE);
		cprintf("\nYou are running low on guesses! Take a hint from us\n");
		time_t t;
		srand((unsigned) time(&t));
		int hint_index;

		//Sorting the string array via bubble sort
		char msort[100];
		strcpy(msort, mname);
		int num_swap = 0;
		do
		{
			num_swap = 0;
			for(int i = 0; i < strlen(msort) - 1; i++)
			{
				if(msort[i] > msort[i+1])
				{
					char temp = msort[i];
					msort[i] = msort[i+1];
					msort[i+1] = temp;
					num_swap++;
				}
			}
		}
		while(num_swap != 0);
		////////////////////////

		//Extracting the alphabets used in mname
		int chars_freq[26];
		char chars[26];

		for(int i = 0; i < 26; i++)
		{
			chars_freq[i] = 0;
		}

		for(i = 0; i < strlen(msort); i++)
		{
			char a = msort[i];
			if(a >= 'A' && a <= 'Z')
			{
				int b = (int) (a - 'A');
				chars_freq[b]++;
			}
		}

		int j = 0;
		for(i = 0; i < 26; i++)
		{
			if(chars_freq[i] != 0)
			{
				chars[j] = (char) ('A' + i);
				j++;
			}
		}
		chars[j] = '\0';
		///////////////////////////////////
		int is_good_hint = 0;
		char a;
		do
		{
			hint_index = rand() % strlen(chars);

			a = chars[hint_index];

			for(int i = 0; i < mname[i]; i++)
			{
				if(a == mname[i] && mguess[i] == '_')
				{
					is_good_hint = 1;
					break;
				}
				else if(a == mname[i] && mguess[i] != '_')
				{
					is_good_hint = 0;
					break;
				}
			}
		}
		while(!is_good_hint);

		for (i = 0; i < strlen(mname); i++)
		{
			if(a == mname[i])
			{
				mguess[i] = a;
			}
		}
		hint_given = 1;
		textcolor(WHITE);

		size = strlen("Press any key to continue");
		gotoxy((width - size) / 2, wherey());
		cout << "Press any key to continue";
		getch();

		paint();
	}


	if(status == 1)
	{
		textcolor(LIGHTGREEN);
		size = strlen("YOU WON!!");
		gotoxy((width - size) / 2 + 1,4);
		cprintf("YOU WON!!");
		getch();
		exit(0);
	}
	else if(num_guess == 0)
	{
		textcolor(LIGHTRED);
		size = strlen("YOU LOST!");
		gotoxy((width - size) / 2 + 1, 4);
		cprintf("YOU LOST!\n");

		textcolor(LIGHTRED);
		size = strlen("The correct answer was ") + strlen(mname);
		gotoxy((width - size)/2 + 1, wherey());
		cprintf("The correct answer was %s", &mname);
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
		inp =  toupper(inp);
	}
	while(!(inp >= 'A' && inp <= 'Z'));

	int num_match = 0;
	for(int i = 0; i < strlen(mname); i++)
	{
		if((int) inp == mname[i])
		{
			mguess[i] = mname[i];
			num_match++;
		}
	}

	int is_guessed = 0;
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
	}

	int n = 0;
	for(i = 0; i < strlen(mguess); i++)
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

	guessed[strlen(guessed)] = (char) inp;

}

void frame()
{
	struct text_info info;
	gettextinfo(&info);

	int width = (int) info.screenwidth;
	int height = (int) info.screenheight;

	gotoxy(1,1);
	for(int i = 0; i < width; i++)
	{
		cout << '*';
	}

	for(i = 2; i <= height - 2; i++)
	{
		gotoxy(1, i); cout << '*';
		gotoxy(width, i); cout << '*';
	}

	gotoxy(1, height - 1);
	for(i = 0; i < width; i++)
	{
		cout << '*';
	}
}