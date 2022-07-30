#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h> 
#define MAXANCHO 640
#define MAXLARGO 480
/*#define ANCHOESCALADO MAXANCHO/20
#define LARGOESCALADO MAXLARGO/20*/

void moveBall();
void p1Move();
void p2Move();
void startNew();
void checkWin();
void setupGame();
void mapa();
void dibujamapa();
BITMAP* buffer;
char mapita[MAXANCHO][MAXLARGO];
BITMAP* bloque;
PALETTE paleta;
BITMAP* bloquereal;
int main()
{
    allegro_init();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
    buffer = create_bitmap(640, 480);

    setupGame();
    mapa();
    dibujamapa();
    while (!key[KEY_ESC])
    {
        p1Move();
        p2Move();
        moveBall();
        checkWin();
    }

    return 0;
}
END_OF_MAIN();

int ball_x = 320;
int ball_y = 240;

int ball_tempX = 320;
int ball_tempY = 240;

int p1_x = 20;
int p1_y = 210;

int p1_tempX = 20;
int p1_tempY = 210;

int p2_x = 620;
int p2_y = 210;

int p2_tempX = 620;
int p2_tempY = 210;

time_t secs;
int dir;


void moveBall()
{

    ball_tempX = ball_x;
    ball_tempY = ball_y;

    if (dir == 1 && ball_x > 5 && ball_y > 5) {

        if (ball_x == p1_x + 15 && ball_y >= p1_y && ball_y <= p1_y + 60) {
            dir = rand() % 2 + 3;
        }
        else {
            --ball_x;
            --ball_y;
        }

    }
    else if (dir == 2 && ball_x > 5 && ball_y < 475) {

        if (ball_x == p1_x + 15 && ball_y >= p1_y && ball_y <= p1_y + 60) {
            dir = rand() % 2 + 3;
        }
        else {
            --ball_x;
            ++ball_y;
        }

    }
    else if (dir == 3 && ball_x < 635 && ball_y > 5) {

        if (ball_x + 5 == p2_x && ball_y >= p2_y && ball_y <= p2_y + 60) {
            dir = rand() % 2 + 1;
        }
        else {
            ++ball_x;
            --ball_y;
        }

    }
    else if (dir == 4 && ball_x < 635 && ball_y < 475) {

        if (ball_x + 5 == p2_x && ball_y >= p2_y && ball_y <= p2_y + 60) {
            dir = rand() % 2 + 1;
        }
        else {
            ++ball_x;
            ++ball_y;
        }

    }
    else {

        if (dir == 1 || dir == 3)    ++dir;
        else if (dir == 2 || dir == 4)    --dir;

    }

    acquire_screen();
    circlefill(buffer, ball_tempX, ball_tempY, 5, makecol(0, 0, 0));
    circlefill(buffer, ball_x, ball_y, 5, makecol(128, 255, 0));
    draw_sprite(screen, buffer, 0, 0);
    release_screen();

    rest(5);

}

void p1Move()
{

    p1_tempY = p1_y;

    if (key[KEY_W] && p1_y > 0) {

        --p1_y;

    }
    else if (key[KEY_S] && p1_y < 420) {

        ++p1_y;

    }

    acquire_screen();
    rectfill(buffer, p1_tempX, p1_tempY, p1_tempX + 10, p1_tempY + 60, makecol(0, 0, 0));
    rectfill(buffer, p1_x, p1_y, p1_x + 10, p1_y + 60, makecol(0, 0, 255));
    release_screen();

}

void p2Move()
{

    p2_tempY = p2_y;

    if (key[KEY_UP] && p2_y > 0) {

        --p2_y;

    }
    else if (key[KEY_DOWN] && p2_y < 420) {

        ++p2_y;

    }

    acquire_screen();
    rectfill(buffer, p2_tempX, p2_tempY, p2_tempX + 10, p2_tempY + 60, makecol(0, 0, 0));
    rectfill(buffer, p2_x, p2_y, p2_x + 10, p2_y + 60, makecol(0, 0, 255));
    release_screen();

}

void startNew()
{

    clear_keybuf();
    readkey();
    clear_to_color(buffer, makecol(0, 0, 0));
    ball_x = 320;
    ball_y = 240;

    p1_x = 20;
    p1_y = 210;

    p2_x = 620;
    p2_y = 210;

}

void checkWin()
{

    if (ball_x < p1_x) {
        textout_ex(screen, font, "Player 2 Wins!", 320, 240, makecol(255, 0, 0), makecol(0, 0, 0));
        startNew();
    }
    else if (ball_x > p2_x) {
        textout_ex(screen, font, "Player 1 Wins!", 320, 240, makecol(255, 0, 0), makecol(0, 0, 0));
        startNew();
    }

}

void setupGame()
{

    acquire_screen();
    rectfill(buffer, p1_x, p1_y, p1_x + 10, p1_y + 60, makecol(0, 0, 255));
    rectfill(buffer, p2_x, p2_y, p2_x + 10, p2_y + 60, makecol(0, 0, 255));
    circlefill(buffer, ball_x, ball_y, 5, makecol(128, 255, 0));
    draw_sprite(screen, buffer, 0, 0);
    release_screen();

    time(&secs);
    srand((unsigned int)secs);
    dir = rand() % 4 + 1;

}

void mapa()
{
    FILE* mapFile;
    int i, j;
    if ((mapFile = fopen("mapa.txt", "r")) == NULL)
    {
        printf("Error al abrir archivo");
        return;
    }
    for (i = 0; i < MAXANCHO; i++)
    {
        for (j = 0; j < MAXLARGO; j++)
        {
            fscanf(mapFile, "%c", &mapita[i][j]);
        }
    }
    fclose(mapFile);
}

void dibujamapa()
{
    int i, j;
    bloque = load_bitmap("bloque.bmp", NULL);
    bloquereal = create_bitmap(20, 20);
    blit(bloque, bloquereal, 0, 0, 20, 20, 20, 20);
    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 24; j++)
        {
            if (mapita[i][j] == 'x')
            {
                draw_sprite(buffer, bloquereal, 20 * i, 20 * j);
                /*blit(bloque,buffer,0,0,i*20,j*20,20,20);*/
                /*rectfill(buffer,i*20,j*20, (i*20)+20,(j*20)+20,3);*/
            }
        }
    }
}
