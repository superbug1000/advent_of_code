#include "stdio.h"
#include <string.h>

int calc_score1(player, opponent)
{
    int score = player + 1;
    if (player == opponent) 
    {
        score += 3;
    }
    else if (((player + 2) % 3) == opponent) 
    {
        score += 6;
    }

    return score;
}

int calc_score2(player, opponent)
{
    int offset = 0;
    if (player == 0)
    {
        offset = 2;
    } 
    else if (player == 2)
    {
        offset = 1;
    }

    int choice = (opponent + offset) % 3;
    return calc_score1(choice, opponent);
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        return 1;
    }

    char player_base = 'X';
    char opponent_base = 'A';

    int score1 = 0;
    int score2 = 0;
    char line[8] = "";
    while (fgets(line, sizeof(line), file))
    {
        char player = line[2] - player_base;
        char opponent = line[0] - opponent_base;

        score1 += calc_score1(player, opponent);
        score2 += calc_score2(player, opponent);
    }

    printf("Score1: %d\n", score1);
    printf("Score2: %d\n", score2);
    
    fclose(file);
    return 0;
}
