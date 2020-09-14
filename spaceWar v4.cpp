#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include <conio.h>
using namespace std;

typedef struct ene
{
	COORD part[11];
}ene;

void setPos(COORD a)// set cursor 
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}
void setPos(int i, int j)// set cursor
{
	COORD pos = { i, j };
	setPos(pos);
}
void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0)

{

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);

}

void drawRow(int y, int x1, int x2, char ch)
{
	setColor(7, 1);
	setPos(x1, y);
	for (int i = 0; i <= (x2 - x1); i++)
		cout << ch;
}
void drawCol(int x, int y1, int y2, char ch)
{
	setColor(7, 1);
	int y = y1;
	while (y != y2 + 1)
	{
		setPos(x, y);
		cout << ch;
		y++;
	}
}
void drawFrame(COORD a, COORD  b, char row, char col)
{
	drawRow(a.Y, a.X + 1, b.X - 1, row);
	drawRow(b.Y, a.X + 1, b.X - 1, row);
	drawCol(a.X, a.Y + 1, b.Y - 1, col);
	drawCol(b.X, a.Y + 1, b.Y - 1, col);
}
void drawFrame(int x1, int y1, int x2, int y2, char row, char col)
{
	COORD a = { x1, y1 };
	COORD b = { x2, y2 };
	drawFrame(a, b, row, col);
}
void printUI()
{
	drawFrame(0, 0, 100, 49, '=', '|');
	drawFrame(100, 0, 139, 49, '-', '|');
}

void printmenu()
{
	setColor(14,1);
	char title1[] = "   _____ _____        _____ ________          __     _____  ";
	
	char title2[] = "  / ____|  __ \\ /\\   / ____|  ____\\ \\        / /\\   |  __ \\ ";
	
	char title3[] = " | (___ | |__) /  \\ | |    | |__   \\ \\  /\\  / /  \\  | |__) |";
	
	char title4[] = "  \\___ \\|  ___/ /\\ \\| |    |  __|   \\ \\/  \\/ / /\\ \\ |  _  / ";
	
	char title5[] = "  ____) | |  / ____ \\ |____| |____   \\  /\\  / ____ \\| | \\ \\ ";
	
	char title6[] = " |_____/|_| /_/    \\_\\_____|______|   \\/  \\/_/    \\_\\_|  \\_\\";
	
	char title7[] = "                                                            ";
	for (int seq = 0; seq < strlen(title1); seq++)
	{
		Sleep(25);
		setPos(20+seq, 7);
		std::cout << title1[seq]; 
		setPos(20+seq, 8);
		std::cout << title2[seq]; 
		setPos(20+seq, 9);
		std::cout << title3[seq]; 
		setPos(20+seq, 10);
		std::cout << title4[seq]; 
		setPos(20+seq, 11);
		std::cout << title5[seq]; 
		setPos(20+seq, 12);
		std::cout << title6[seq]; 
		setPos(20+seq, 13);
		std::cout << title7[seq];
		
	}
	setPos(40, 28);
	cout << "Press any key to start";
	setPos(40, 32);
	cout << "   WASD       move";
	setPos(40, 34);
	cout << "   SPACE      shot";
	setPos(40, 36);
	cout << "   ESC        exit";
	

	setPos(110, 45);
	cout << "Made by link 3am";
	setPos(110, 46);
	cout << "C4 studio";
	if (_getch() == 27)
	{
		system("cls");
		exit(1);
	}
	else
	{
		system("cls");
		printUI();
	}
}


class gameFlash
{
public:
	unsigned int HP;
	int score = 0;
	COORD Core = { 50, 45 };//player core 0 position
	COORD position[8];//player part
	COORD beam[15];
	ene enemyA[13]; //= { 50,-1 };
	void playerPart(COORD Core);
	void printPlayer(COORD Core);
	void clsPlayer(COORD Core);
	void setBeam();
	void beamMove();
	//void clsBeam();
	void printEnemyA();
	void enemyaMove();
	void setEnemyA();
	void playerHit();
	void enemyHit();
	void flash();
	void endScene();
	void shipShow();
};
void gameFlash::endScene()
{

	printUI();
	Sleep(500);
	getchar;
	setColor(15, 1);
	char title1[] = "   _____          __  __ ______    ______      ________ _____  ";

	char title2[] = "  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ";

	char title3[] = " | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |";

	char title4[] = " | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ";

	char title5[] = " | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ";

	char title6[] = "  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\ ";

	char title7[] = "                                                             ";
	for (int seq = 0; seq < strlen(title1); seq++)
	{
		Sleep(25);
		setPos(20 + seq, 7);
		std::cout << title1[seq];
		setPos(20 + seq, 8);
		std::cout << title2[seq];
		setPos(20 + seq, 9);
		std::cout << title3[seq];
		setPos(20 + seq, 10);
		std::cout << title4[seq];
		setPos(20 + seq, 11);
		std::cout << title5[seq];
		setPos(20 + seq, 12);
		std::cout << title6[seq];
		setPos(20 + seq, 13);
		std::cout << title7[seq];

	}
	setPos(40, 25);
	cout << "    ";
	setPos(40, 25);
	cout << "Your score is ";
	setColor(11, 1);
	cout << score;
	setColor(15, 1);
	setPos(40, 27);
	cout << "Press enter and any key to play again";
	setPos(40, 29);
	cout << "Press enter and ESC to quit game";
	setPos(111, 45);
	cout << "not good enough";
	setPos(111, 46);
	cout << "try harder next time";
	Sleep(1000);
	setColor(1, 1);

	setPos(2, 45);
	getchar();
	if (_getch() == 27)
	{
		setColor(15, 1);
		system("cls");
		exit(1);
	}
	else
	{
		system("cls");
		printUI();
		flash();
	}
	
}
void gameFlash::playerPart(COORD Core)
{
	if (score < 100)
	{
		position[3].X = Core.X - 1; 
		position[4].X = Core.X + 1; 
		position[1].X = Core.X - 1; 
		position[2].X = Core.X + 1; 
		position[5].X = Core.X - 2;
		position[0].X = Core.X + 2;
		position[6].X = position[7].X = Core.X;
		position[1].Y = position[2].Y = position[6].Y = Core.Y - 1;
		position[3].Y = position[4].Y = Core.Y;
		position[5].Y = position[0].Y = position[7].Y = Core.Y + 1;
	}
	if (score >= 100&&score <700)
	{
		position[1].X = Core.X - 1;
		position[2].X = Core.X + 1;
		position[3].X = Core.X - 2;
		position[4].X = Core.X + 2;
		position[5].X = Core.X - 4;
		position[6].X = Core.X - 2;
		position[7].X = Core.X + 2;
		position[0].X = Core.X + 4;
		position[1].Y = position[2].Y = Core.Y - 1;
		position[3].Y = position[4].Y = Core.Y;
		position[5].Y = position[6].Y = position[7].Y = position[0].Y = Core.Y + 1;
	}
	if (score >= 700)
	{
		position[1].X = position[3].X = Core.X - 1;
		position[2].X = position[4].X = Core.X + 1;
		position[5].X = Core.X - 4;
		position[6].X = Core.X - 2;
		position[7].X = Core.X + 2;
		position[0].X = Core.X + 4;
		position[1].Y = position[2].Y = Core.Y - 1;
		position[3].Y = position[4].Y = Core.Y;
		position[5].Y = position[6].Y = position[7].Y = position[0].Y = Core.Y + 1;
	}
}
void gameFlash::printPlayer(COORD Core)
{
	setColor(11, 1);
	if (score < 100)
	{
		for (int i = 0; i < 8; i++)
		{
			setPos(Core);
			cout << 0;
			setPos(position[i]);
			if (i == 1 || i == 4 || i == 5)
				cout << "/";
			else if (i == 2 || i == 3 || i == 0)
				cout << "\\";
			else if (i == 6 || i == 7)
				cout << " ";

		}
	}
	if (score >= 100 && score < 700)
	{
		for (int i = 0; i < 8; i++)
		{
			setPos(Core);
			cout << 0;
			setPos(position[i]);
			if (i == 1 || i == 3 || i == 5)
				cout << "/";
			else if (i == 2 || i == 4 || i == 0)
				cout << "\\";
			else if (i == 6 || i == 7)
				cout << "|";

		}
	}
	if (score >= 700)
	{
		for (int i = 0; i < 8; i++)
		{
			setPos(Core);
			cout << 0;
			setPos(position[i]);
			if (i == 1 || i == 2)
				cout << "_";
			else if (i == 3 || i == 4)
				cout << "*";
			else if (i == 5 )
				cout << "/";
			else if (i == 0)
				cout << "\\";
			else if (i == 7 || i == 6)
				cout << "_";
		}
	}
}
void gameFlash::setBeam()
{
	if (score < 100 || score >= 700)
	{
		for (int i = 0; i < 5; i++)
		{
			if (beam[i].X == 120)
			{
				beam[i].X = Core.X;
				beam[i].Y = Core.Y - 2;
				break;
			}
		}
	}
	if (score >= 100&&score<700)
	{
		for (int q = 5; q < 10; q++)
		{
			if (beam[q].X == 121)
			{
				beam[q].X = Core.X-4;
				beam[q].Y = Core.Y;
				break;
			}

		}
		for (int e = 10; e < 15; e++)
		{
			if (beam[e].X == 122)
			{
				beam[e].X = Core.X + 4;
				beam[e].Y = Core.Y;
				break;
			}
		}
	}
	if (score >= 700)
	{
		for (int q = 5; q < 10; q++)
		{
			if (beam[q].X == 121)
			{
				beam[q].X = Core.X - 3;
				beam[q].Y = Core.Y;
				break;
			}

		}
		for (int e = 10; e < 15; e++)
		{
			if (beam[e].X == 122)
			{
				beam[e].X = Core.X + 3;
				beam[e].Y = Core.Y;
				break;
			}
		}
	}
}
void gameFlash::beamMove()
{
	setColor(14, 1);
	for (int i = 0; i < 5; i++)
	{
		COORD clsbeam;
		if (beam[i].Y != 2 && beam[i].X != 120)
		{
			beam[i].Y = beam[i].Y - 1;
			setPos(beam[i]);
			cout << "|";
			clsbeam.X = beam[i].X;
			clsbeam.Y = beam[i].Y + 1;
			setPos(clsbeam);
			cout << " ";
		}
		if (beam[i].Y == 2)
		{
			setPos(beam[i]);
			cout << " ";
			beam[i].Y = 35;
			beam[i].X = 120;
		}
		
	}
	for (int q = 5; q < 10; q++)//side beam L
	{
		COORD clsbeams;
		if (beam[q].Y != 2 && beam[q].X != 121)
		{
			beam[q].Y = beam[q].Y - 1;
			setPos(beam[q]);
			cout << "^";
			clsbeams.X = beam[q].X;
			clsbeams.Y = beam[q].Y + 1;
			setPos(clsbeams);
			cout << " ";
		}
		if (beam[q].Y == 2)
		{
			setPos(beam[q]);
			cout << " ";
			beam[q].Y = 35;
			beam[q].X = 121;
		}
	}
	for (int e = 10; e < 15; e++)
	{
		COORD clsbeamss;
		if (beam[e].Y != 2 && beam[e].X != 122)
		{
			beam[e].Y = beam[e].Y - 1;
			setPos(beam[e]);
			cout << "^";
			clsbeamss.X = beam[e].X;
			clsbeamss.Y = beam[e].Y + 1;
			setPos(clsbeamss);
			cout << " ";
		}
		if (beam[e].Y == 2)
		{
			setPos(beam[e]);
			cout << " ";
			beam[e].Y = 35;
			beam[e].X = 122;
		}
	}
}
/*void gameFlash::clsBeam()
{
	
		setPos(beam);
		cout << " ";
	
}*/

void gameFlash::clsPlayer(COORD Core)
{
	for (int i = 0; i < 8; i++)
	{
		setPos(Core);
		cout << " ";
		setPos(position[i]);
		cout << " ";
	}
}
void gameFlash::printEnemyA() 
{
	setColor(13, 1);
	for (int k = 0; k < 10; k++)
	{
		enemyA[k].part[4].Y = enemyA[k].part[5].Y = enemyA[k].part[9].Y = enemyA[k].part[10].Y = enemyA[k].part[0].Y;
		enemyA[k].part[1].Y = enemyA[k].part[2].Y = enemyA[k].part[3].Y = enemyA[k].part[0].Y -1;
		enemyA[k].part[6].Y = enemyA[k].part[7].Y = enemyA[k].part[8].Y = enemyA[k].part[0].Y + 1;
		enemyA[k].part[2].X = enemyA[k].part[7].X = enemyA[k].part[0].X;
		enemyA[k].part[9].X = enemyA[k].part[0].X - 1;
		enemyA[k].part[10].X = enemyA[k].part[0].X + 1;
		enemyA[k].part[1].X = enemyA[k].part[4].X = enemyA[k].part[6].X = enemyA[k].part[0].X - 2;
		enemyA[k].part[3].X = enemyA[k].part[5].X = enemyA[k].part[8].X = enemyA[k].part[0].X + 2;
		for (int i = 0; i < 11; i++)
		{
			if (enemyA[k].part[i].Y < 49 && enemyA[k].part[i].Y > 0 && enemyA[k].part[0].X != 120)
			{
				if (i == 0)
				{
					setPos(enemyA[k].part[0]);
					cout << "0";
				}
				if (i == 4 || i == 5)
				{
					setPos(enemyA[k].part[i]);
					cout << "|";
				}
				if (i == 1 || i == 8)
				{
					setPos(enemyA[k].part[i]);
					cout << "/";
				}
				if (i == 3 || i == 6)
				{
					setPos(enemyA[k].part[i]);
					cout << "\\";
				}
				if (i == 9)
				{
					setPos(enemyA[k].part[i]);
					cout << ">";
				}
				if (i == 10)
				{
					setPos(enemyA[k].part[i]);
					cout << "<";
				}
			}
		}
	}
}

void gameFlash::enemyaMove()
{
	
	for (int k = 0; k < 10; k++)
	{
		if (enemyA[k].part[0].X != 120)
		{
			for (int i = 0; i < 11; i++)//clsEnemy
			{
				if (enemyA[k].part[i].Y < 49 && enemyA[k].part[i].Y >0)
				{
					setPos(enemyA[k].part[i]);
					cout << " ";
				}
			}
			enemyA[k].part[0].Y++;
			printEnemyA();
			if (enemyA[k].part[1].Y == 50)
			{
				enemyA[k].part[0].X = 120;
				enemyA[k].part[0].Y = 40;//initEnemy again
			}
		}
	}
}

void gameFlash::setEnemyA()
{
	for (int k = 0; k < 10; k++)
	{
		if (enemyA[k].part[0].X == 120)
		{
			enemyA[k].part[0].X = rand() % (97 - 3) + 3;
			enemyA[k].part[0].Y = -1;
		}
	}
}
void gameFlash::playerHit()
{
	for (int p = 0; p < 8; p++)
	{
		for (int k = 0; k < 10; k++)
		{
			for (int i = 0; i < 11; i++)
			{
				if (position[p].X == enemyA[k].part[i].X && position[p].Y == enemyA[k].part[i].Y)
				{
					if(HP!=0)
					{
						HP--;
					}
					setColor(15, 1);
					setPos(121, 10);
					cout << HP << "   ";
					
					
					
					for (int l = 0; l < 11; l++) //cls the hited enemy
					{
						setPos(enemyA[k].part[l]);
						cout << " ";
					}
					
				enemyA[k].part[0].X = 120; //re init hited enemy
				enemyA[k].part[0].Y = 40;
				}
			}
		}
	}
}
void gameFlash::enemyHit()
{
	for (int b = 0; b < 15; b++)
	{
		for (int k = 0; k < 10; k++)
		{
			for (int i = 0; i < 11; i++)
			{
				if (enemyA[k].part[i].X == beam[b].X && enemyA[k].part[i].Y == beam[b].Y )
				{
					score += 10;
					setColor(15, 1);
					setPos(121, 12);
					cout << score << "   ";
					
					for (int l = 0; l < 11; l++)//cls the hited enemy
					{
						setPos(enemyA[k].part[l]);
						cout << " ";
					}
				
					enemyA[k].part[0].X = 120;//re init hited enemy
					enemyA[k].part[0].Y = 40;
					if (b < 5)
					{
						beam[b].X = 120;
						beam[b].Y = 35;
					}
					if (b >=5&&b<10)
					{
						beam[b].X = 121;
						beam[b].Y = 35;
					}
					if (b >=10&&b<15)
					{
						beam[b].X = 122;
						beam[b].Y = 35;
					}
				}

			}
		}
	}
}

void gameFlash::flash()
{
	system("cls");
	shipShow();
	score = 0;
	HP = 10;//int HP
	playerPart(Core);
	printPlayer(Core);
	printUI();
	for (int i = 0; i < 5; i++)
	{
		beam[i].X = 120;
		beam[i].Y = 35;//initBeam
	}
	for (int q = 5; q < 10; q++)
	{
		beam[q].X = 121;
		beam[q].Y = 35;//init  side Beam L
	}
	for (int e = 10; e < 15; e++)
	{
		beam[e].X = 122;
		beam[e].Y = 35;//init  side Beam R
	}
	for (int k = 0; k < 10; k++)
	{
		enemyA[k].part[0].X = rand()%(98-2)+2;
		enemyA[k].part[0].Y = rand()%(30-1)+1;//initEnemyA
	}
	setColor(15, 1);
	setPos(115, 10);
	cout<<"HP    "  << HP;//init HP print
	setPos(112, 12);
	cout <<"score    "<< score;//init score print
	setPos(107, 20);
	//cout << "Shot them down,soldier!";
	setPos(104, 20);
	cout << "Get higher score to upgrade ship";
	
	setPos(113, 33);
	cout << "WASD    move";
	setPos(112, 35);
	cout << "SPACE    shot";
	setPos(114, 37);
	cout << "ESC    give up";
	while (HP != 0)
	{
		
		if (_kbhit())
			switch (_getch())
			{
			case 'a':
			case 'A':
				if (score < 100)
				{
					if (Core.X > 3)
					{
						clsPlayer(Core);
						Core.X--;
					}
				}
				if (score >= 100)
				{
					if (Core.X > 5)
					{
						clsPlayer(Core);
						Core.X--;
					}
				}
				break;
			case 'd':
			case 'D':
				if (score < 100)
				{
					if (Core.X < 97)
					{
						clsPlayer(Core);
						Core.X++;
					}
				}
				if (score >= 100)
				{
					if (Core.X < 95)
					{
						clsPlayer(Core);
						Core.X++;
					}
				}
				break;
			case 'w':
			case 'W':
				if (Core.Y > 2)
				{
					clsPlayer(Core);
					Core.Y--;
				}
				break;
			case 's':
			case 'S':
				if (Core.Y < 47)
				{
					clsPlayer(Core);
					Core.Y++;
				}
				break;
			
			case 32:
				setBeam();
				
				break;
			case 27:
				system("cls");
				endScene();
				break;

			}
		clsPlayer(Core);
		playerPart(Core);
		printPlayer(Core);
		beamMove();
		setEnemyA();
		enemyaMove();

		playerHit();
		enemyHit();

	}
	
	for (int p = 0; p < 8; p++)
	{
		for (int k = 0; k < 10; k++)
		{
			for (int i = 0; i < 11; i++)
			{
				if (position[p].X == enemyA[k].part[i].X && position[p].Y == enemyA[k].part[i].Y)
				{
					setPos(position[p]);
					cout << "+";
				}
			}
		}
	}
	Sleep(3000);
	getchar;
	Sleep(500);
	system("cls");
	
	endScene();
}

void gameFlash::shipShow()
{
	setColor(15, 1);
	score = 0;
	Core = { 107,25 };
	playerPart(Core);
	for (int i = 0; i < 8; i++)
	{
		setPos(Core);
		cout << 0;
		setPos(position[i]);
		if (i == 1 || i == 4 || i == 5)
			cout << "/";
		else if (i == 2 || i == 3 || i == 0)
			cout << "\\";
		else if (i == 6 || i == 7)
			cout << " ";

	}

	score = 110;
	Core = { 117,25 };
	playerPart(Core);
	for (int i = 0; i < 8; i++)
	{
		setPos(Core);
		cout << 0;
		setPos(position[i]);
		if (i == 1 || i == 3 || i == 5)
			cout << "/";
		else if (i == 2 || i == 4 || i == 0)
			cout << "\\";
		else if (i == 6 || i == 7)
			cout << "|";

	}
	score = 710;
	Core = { 130,25 };
	playerPart(Core);
	for (int i = 0; i < 8; i++)
	{
		setPos(Core);
		cout << 0;
		setPos(position[i]);
		if (i == 1 || i == 2)
			cout << "_";
		else if (i == 3 || i == 4)
			cout << "*";
		else if (i == 5)
			cout << "/";
		else if (i == 0)
			cout << "\\";
		else if (i == 7 || i == 6)
			cout << "_";
	}

	Core = { 50,45 };
	playerPart(Core);
}
int main() {

	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	system("mode con cols=140 lines=50");//window size
	system("color 17");
	printUI();
	gameFlash gameFlash;
	//gameFlash.shipShow();
	gameFlash.playerPart(gameFlash.Core);
	gameFlash.printPlayer(gameFlash.Core);
	
	printmenu();
	gameFlash.flash();
	

	system("cls");//quit
	
	return 0;
}



//{120,40} init position enemy
//{120,35} beam 121/122 for sidebeam
//k enemy number
//i enemy part number
//p player part number
//
//
