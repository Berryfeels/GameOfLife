#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ALIVE = 'O';
int DEAD = ' ';

void draw_board(int height, int width, int board[height][width])
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			putchar(board[y][x]);
		}
		putchar('\n');
	}
}
int main (int ac, char **av)
{
	if(ac != 4)
	{
		putchar('e');
		return 1;
	}

	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iterations = atoi(av[3]);

	//First initialise the board. The board is width by height
	int board[height][width];

	//INITIATE BOARD: adesso inizializziamo tutto a ' '
	for (int y = 0; y < height; y++){
		for(int x = 0; x < width; x++) {board[y][x] = DEAD;}
	}

	//disegna la posizione di partenza
	char buff;
	int alive = -1;
	int x = 0, y = 0;
	while(read(0, &buff, 1) > 0)
	{
		if(buff == 'w' && y > 0)
			y--;
		else if(buff == 'a' && x > 0)
			x--;
		else if(buff == 's' && y < height - 1)
			y++;
		else if(buff == 'd' && x < width - 1)
			x++;
		if(buff == 'x')
			alive = -alive;
		if(alive == 1)
				board[y][x] = ALIVE;
	}

	//APPLY RULES ON REPETITIONS
	/*
	1 Any live cell with two or three live neighbours survives.
	2 Any dead cell with three live neighbours becomes a live cell.
	3 All other live cells die in the next generation. 
		Similarly, all other dead cells stay dead.*/
	
	unsigned int neighbours = 0;
	int new_board[height][width];
	for(int i = 0; i < iterations; i++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				//COUNT NEIGHBOURS
				for(int w = - 1; w <= 1; w++)
				{
					for(int h = - 1; h <= 1; h++)
					{
						if(w||h)
						{
							int ny = y + h;
							int nx = x + w;
							if (ny >= 0 && ny < height && nx >= 0 && nx < width
								&& board[ny][nx] == ALIVE)
								neighbours++;
						}
					}
				}
				//1 Any live cell with two or three live neighbours survives.
				if(board[y][x] == ALIVE && (neighbours == 2 || neighbours == 3))
					new_board[y][x] = ALIVE;
				//2 Any dead cell with three live neighbours becomes a live cell.
				else if(board[y][x] == DEAD && neighbours == 3)
					new_board[y][x] = ALIVE;
				//3 All other live cells die in the next generation.
				else
					new_board[y][x] = DEAD;
				neighbours = 0;
			}
		}
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				board[y][x] = new_board[y][x];
			}
		}
	}
	draw_board(height, width, board);
	return 0;
}