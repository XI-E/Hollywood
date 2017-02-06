#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

//////////////////////

void paint();
void printhollywood(int);
void check(char);

//////////////////////

char ans[100], current[100], ans2[100], done[100];
int life = 9, stat = 0;

void main(){

	clrscr();

		// Holly Bolly

		Init:

		cout << "Enter movie name : ";
		cin.getline(ans, 100, '\n');

		for(int i=0; i<100; i++){
			if(ans[i]>64 && ans[i]<127){
				current[i] = '_';
			}

			switch(ans[i]){
				case 'A':	case 'a':
				case 'E':   case 'e':
				case 'I':   case 'i':
				case 'O':   case 'o':
				case 'U':   case 'u':
				case ' ':   case '\0':
					current[i] = ans[i];

			}

			if(ans[i]>32 && ans[i]<65){
				current[i] = ans[i];
			}
		}

		for(int l=0; l<100; l++){
			ans2[l] = tolower(ans[l]);
		}

		paint();

	getch();
}

void check(char an){				// an = given answer
	int k = 0, i, p;

	switch(an){
		case 'a': case 'e':
		case 'i': case 'o':
		case 'u': case ' ':
		case '\n':
			goto skipped;
	}

	for(p=0; p<100; p++){
		if(an==done[p]){
			goto skipped;
		}
		if(done[p]=='\0'){
			done[p] = an;
			break;
		}
	}

	for(i=0; i<100; i++){
		if(an==ans2[i]){
			current[i] = ans[i];
			k++;
			cout << k;
		}
	}
	if(k==0){
		life--;
	}
	if(life==4)
	{
		randomize();
		int R;
		do
		{
			R=random(strlen(ans));
		}while( ans2[R]=='a'|| ans2[R]=='e'||
				  ans2[R]=='i'|| ans2[R]=='o'||
				  ans2[R]=='u'|| ans2[R]==' ');

		current[R]=ans[R];
	}
	skipped:
	stat = 0;
	for(int j=0; j<100; j++){
		if(current[j]==ans[j]){
			stat++;
		}
	}
}

void paint(){
	clrscr();

	char lol, lol2;

	printhollywood(life);
	
	cout << "\nCurrent lives : " << life << "\n\nCurrent Status\t\t";

	for(int i=0; i<101; i++){
		if(current[i]!='\0'){
			cout << current[i] << ' ';
		}
		else{
			break;
		}
	}

	if(life<1){
		cout << "\n\nYou fail!!";
		cout << "\nCorrect answer is\t\t";
		for(int i=0; i<100; i++){
			if(ans[i]!='\0'){
				cout << ans[i];
			}
			else{
				break;
			}
		}
		goto exit;
	}
	else if(stat==100){
		cout << "\n\nCongrats! You won!!";
		goto exit;
	}

	cout << "\n\nEnter next character(s) : \n";

	lol = getch();
	lol2 = tolower(lol);

	check(lol2);

	paint();

	exit:
	;
}

void printhollywood(int life)
{
	char holly[]="HOLLYWOOD";
	for(int i=0; i<9-life; i++)
	{
		holly[i]='_';
	}
	gotoxy(16, 1);
	puts(holly);
}
