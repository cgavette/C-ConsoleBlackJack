//Cameron Gavette
//“I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else’s work as my own.”
#include <iostream>
#include <ctime>
#include <iomanip>
#include <windows.h>

//Prototypes for functions
using namespace std;
void gotoxy(int, int);
char suit(int);
int value(int);
char picture(int);
void calc_tot(int[], int, int);
void Deal_Two_Cards(int[], int[], int[]);
int Another_Card(int[], int[], int, int);
void finish_dealer(int[], int[], int);
void win_lose_tie(int[], int[]);
void setcolor_green();
void setcolor_red();
void setcolor_black();
void output_card(char, char, int);

/*function to set the color of the game board and call over
functions to play the gamme along with asking if the user
would like to play again and play sound*/
int main()
{
	char restart;
	int bet[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
	do
	{
		Beep(900, 200);				//beep letting the user know the game started
		system("cls");
		system("color 27");
		int cards[52], picked[52] = { 0 }, i, Tot[8] = { 0 }, j;
		srand(time(NULL));
		for (i = 0; i < 52; i++)	//for loop to create a shuffled deck of cards
		{
			do
			{
				cards[i] = rand() % 52;
			} while (picked[cards[i]] != 0);
			picked[cards[i]] = 1;
			cout << cards[i] << endl;
		}
		Deal_Two_Cards(cards, Tot, bet);	//call function to print first 2 cards
		j = 16;
		for (int n = 1; n < 8; n++)	//for loop that runs through another card function for each player
		{
			Beep(750, 200);	//sound notifying the next player
			j = Another_Card(cards, Tot, n, j);
		}
		/*call function to the dealer sound
		notifying that the dealer has finished call function
		to determine win / lose/or tie sound notifying end of game*/
		finish_dealer(cards, Tot, j);
		Beep(650, 100);
		win_lose_tie(Tot, bet);
		Beep(900, 350);
		cout << "Would you like to play another game? (y/n): ";
		cin >> restart;
	} while (restart == 'y' || restart == 'Y');

	system("pause");
	return 0;
}

/*function to place cursor in a specific area on console*/
void gotoxy(int h, int w)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE != hConsole)
	{
		COORD pos = { h, w };
		SetConsoleCursorPosition(hConsole, pos);
	}
	return;
}

/*determine the suit of a card*/
char suit(int i)
{
	char c;
	c = char(i / 13 + 3);
	return c;
}

/*function to determine the value of a card*/
int value(int i)
{
	int r;
	if (i % 13 == 0)
		r = 1;
	else if (i % 13 > 9)
		r = 10;
	else
		r = i % 13 + 1;
	return r;
}

/*function to determine character for card*/
char picture(int i)
{
	char c = ' ';
	if (i % 13 == 0)
		c = 'A';
	else if (i % 13 == 10)
		c = 'J';
	else if (i % 13 == 11)
		c = 'Q';
	else if (i % 13 == 12)
		c = 'K';

	return c;
}

/*function that calculates user's total*/
void calc_tot(int T[], int v, int p)
{
	T[p] = T[p] + v;
	return;
}

/*function to print first 2 cards for each plaer this function also clears screen for start of round*/
void Deal_Two_Cards(int cards[], int Tot[], int bet[])
{
	int i, row = 1, v, k = 1;
	char c, s;
	setcolor_green();
	cout << right;
	system("cls");
	cout << setw(8) << "Dealer" << setw(8) << "P1" << setw(8) << "P2" << setw(8) <<
		"P3" << setw(8) << "P4" << setw(8) << "P5" << setw(8) << "P6" << setw(8) << "P7" <<
		endl;
	gotoxy(0, row);
	cout << setw(8) << "???";
	for (i = 1; i < 16; i++)
	{
		if (i == 8)
			row++;
		s = suit(cards[i]);
		v = value(cards[i]);
		c = picture(cards[i]);
		gotoxy(k % 8 * 8, row);
		output_card(c, s, v);
		calc_tot(Tot, v, k % 8);
		gotoxy(k % 8 * 8, 18);
		cout << setw(8) << Tot[k % 8];
		gotoxy(k % 8 * 8, 16);
		cout << left << setw(6) << "Tok = " << left << setw(2) << bet[k / 2] << right;
		k++;
	}
}

/*function that prompts the user to choose to draw another
card or pass for the round If a user busts then their turn is over*/
int Another_Card(int cards[], int tot[], int n, int count)
{
	char c, s, choice;
	int x, v, cardrow = 3;

	s = suit(cards[count]);
	v = value(cards[count]);
	c = picture(cards[count]);
	cout << right;
	gotoxy(n % 8 * 8, cardrow);
	cout << setw(7) << "Hit?";
	gotoxy(0, 19);

	while (true)
	{
		cout << "Would player " << n << " like to hit? (y/n):  ";
		cout << "\b";
		cin.sync();
		cin >> choice;
		if (choice == 'y')
		{
			s = suit(cards[count]);
			v = value(cards[count]);
			c = picture(cards[count]);
			gotoxy(n % 8 * 8, cardrow);
			output_card(c, s, v);

			calc_tot(tot, v, n % 8);
			gotoxy(n % 8 * 8, 18);
			cout << setw(8) << tot[n % 8];
			count++;
			cardrow++;
			gotoxy(n % 8 * 8, cardrow);
			cout << setw(7) << "Hit?";
			gotoxy(0, 19);
			if (tot[n % 8] == 21)
			{
				break;
			}
			if (tot[n % 8] > 21)
			{
				cout << right << setw(8);
				gotoxy(n % 8 * 8, 17);
				cout << "Bust!";
				break;
			}
		}
		else if (choice == 'n')
		{
			gotoxy(0, 19);
			break;
		}
		else
		{
			gotoxy(0, 19);
		}
	}
	gotoxy(n % 8 * 8, cardrow);
	cout << setw(8) << "\b";
	cardrow = 3;
	gotoxy(0, 19);
	cout << endl;

	return count;
}

/*function that finishes the dealers hand if the dealer is at 17 or over then function returns*/
void finish_dealer(int cards[], int tot[], int count)
{
	int i, v, row = 1, draws = 0;
	char c, s;
	s = suit(cards[0]);
	v = value(cards[0]);
	c = picture(cards[0]);

	do
	{
		gotoxy(0, row);
		output_card(c, s, v);
		calc_tot(tot, v, 0 % 8);
		gotoxy(0 % 8 * 8, 18);
		cout << setw(8) << tot[0 % 8];
		row = (3 + draws);
		draws++;

		s = suit(cards[(count)]);
		v = value(cards[(count)]);
		c = picture(cards[(count)]);
		count++;
	} while (tot[0 % 8] < 17);
	gotoxy(0, 19);

	return;
}

/*function to determine if each player has won, lost, or tied function also adjusts the betting score for all player/dealer*/
void win_lose_tie(int tot[], int bet[])
{
	for (int n = 1; n < 8; n++)
	{
		if (tot[n % 8] > 21)
		{
			cout << right << setw(8);
			gotoxy(n % 8 * 8, 17);
			cout << "Bust!";
			bet[n] = (bet[n] - 1);
			gotoxy((n * 2) % 8 * 8, 16);
			cout << left << setw(6) << "Tok = " << left << setw(2) << bet[n - 1] << right;
		}
		else if (tot[n % 8] > tot[0 % 8] && tot[n % 8] < 22)
		{
			cout << right << setw(8);
			gotoxy(n % 8 * 8, 17);
			cout << "Win!";
			bet[n] = (bet[n] + 1);
			gotoxy((n * 2) % 8 * 8, 16);
			cout << left << setw(6) << "Tok = " << left << setw(2) << bet[n] << right;
		}
		else if (tot[n % 8] < tot[0 % 8] && tot[0 % 8] < 22)
		{
			cout << right << setw(8);
			gotoxy(n % 8 * 8, 17);
			cout << "Lose.";
			bet[n] = (bet[n] - 1);
			gotoxy((n * 2) % 8 * 8, 16);
			cout << left << setw(6) << "Tok = " << left << setw(2) << bet[n] << right;
		}
		else if (tot[n % 8] == tot[0 % 8] && tot[n % 8] < 22)
		{
			cout << right << setw(8);
			gotoxy(n % 8 * 8, 17);
			cout << "Tie.";
			gotoxy((n * 2) % 8 * 8, 16);
			cout << left << setw(6) << "Tok = " << left << setw(2) << bet[n] << right;
		}
		else if (tot[0 % 8] > 21 && tot[n % 8] < 22)
		{
			cout << right << setw(8);
			gotoxy(n % 8 * 8, 17);
			cout << "Win!";
			bet[n] = (bet[n] + 1);
			gotoxy((n * 2) % 8 * 8, 16);
			cout << left << setw(6) << "Tok = " << left << setw(2) << bet[n] << right;
		}
	}
	gotoxy(0, 19);

	return;
}

/*function to set the output text to white with a green background*/
void setcolor_green()
{
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 47);
	return;
}

/*function to set the text to red with a white background*/
void setcolor_red()
{
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 252);
	return;
}

/*function to turn the text to black with a white background*/
void setcolor_black()
{
	HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 240);
	return;
}

/*key function that is called to print a said value and suit for playing card*/
void output_card(char c, char s, int v)
{
	if (c != ' ')
	{
		cout << setw(7) << c;
		if (s == 3 || s == 4)
		{
			setcolor_red();
			cout << setw(1) << s;
			setcolor_green();
		}
		else
		{
			setcolor_black();
			cout << setw(1) << s;
			setcolor_green();
		}
	}
	else
	{
		cout << setw(7) << v;
		if (s == 3 || s == 4)
		{
			setcolor_red();
			cout << setw(1) << s;
			setcolor_green();
		}
		else
		{
			setcolor_black();
			cout << setw(1) << s;
			setcolor_green();
		}
	}
	return;
}