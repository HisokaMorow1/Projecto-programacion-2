#include "allegro5/allegro.h" 
#include "allegro5/allegro_image.h" 
#include "allegro5/allegro_native_dialog.h" 
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h> 
#include <allegro5/allegro_primitives.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<time.h> 
#include<string.h>
#include <stdio.h>
#define MAXANCHO 640
#define MAXLARGO 480
#define largo 10
#define MAX 3
/*#define ANCHOESCALADO MAXANCHO/20
#define LARGOESCALADO MAXLARGO/20*/




struct jugador
{
    char nombre[largo];
    int puntaje;
};

void moveBall();
void p1Move(ALLEGRO_EVENT ev);
void p2Move(ALLEGRO_EVENT ev);
void startNew();
void checkWin(struct jugador jugadores[2]);
void setupGame();
void mapa();
void dibujamapa();
ALLEGRO_BITMAP* buffer;
ALLEGRO_FONT* font;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;
char mapita[MAXANCHO][MAXLARGO];
ALLEGRO_BITMAP* bloque;
ALLEGRO_BITMAP* bloquereal;
int main()
{
   
    struct jugador jugadores[2];
    al_init();
    al_install_keyboard();
    buffer = al_create_bitmap(640, 480);
    al_init_font_addon();
    const int FPS = 60;
    setupGame();
    mapa();
    dibujamapa();
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    printf("Jugador 1   :");
    scanf("%s", jugadores[0].nombre);
    printf("Jugador 2   :");
    scanf("%s", jugadores[1].nombre);

    ALLEGRO_EVENT ev;    
        while (ev.type != ALLEGRO_KEY_ESCAPE)
        {
            al_wait_for_event(event_queue, &ev);
            p1Move(ev);
            p2Move(ev);
            moveBall();
            checkWin(jugadores);
        }
        

    return 0;
}

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


    al_draw_filled_circle(ball_tempX, ball_tempY, 5, al_map_rgb(0, 0, 0));
    al_draw_filled_circle(ball_x, ball_y, 5, al_map_rgb(128, 255, 0));
    al_draw_bitmap(buffer, 0, 0, 0);
    al_flip_display();

    al_rest(5);

}

void p1Move(ALLEGRO_EVENT ev)
{

    p1_tempY = p1_y;

    if (ev.type == ALLEGRO_KEY_W && p1_y > 0) {

        --p1_y;

    }
    else if (ev.type == ALLEGRO_KEY_S && p1_y < 420) {

        ++p1_y;

    }


    al_draw_filled_rectangle(p1_tempX, p1_tempY, p1_tempX + 10, p1_tempY + 60, al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(p1_x, p1_y, p1_x + 10, p1_y + 60, al_map_rgb(0, 0, 255));
    al_flip_display();

}

void p2Move(ALLEGRO_EVENT ev)
{

    p2_tempY = p2_y;

    if (ev.type == ALLEGRO_KEY_UP && p2_y > 0) {

        --p2_y;

    }
    else if (ev.type == ALLEGRO_KEY_DOWN && p2_y < 420) {

        ++p2_y;

    }

    al_draw_filled_rectangle(p2_tempX, p2_tempY, p2_tempX + 10, p2_tempY + 60, al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(p2_x, p2_y, p2_x + 10, p2_y + 60, al_map_rgb(0, 0, 255));
    al_flip_display();

}

void startNew()
{
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    ball_x = 320;
    ball_y = 240;

    p1_x = 20;
    p1_y = 210;

    p2_x = 620;
    p2_y = 210;

}

void checkWin(struct jugador jugadores[2])
{
    int i=100;
    
    font = al_load_ttf_font(("Memories.ttf"),14,0);
    if (ball_x < p1_x) 
    {
        al_draw_textf(font, al_map_rgb(255, 0, 0), 320, 240,0,"%s", "Player 1 Wins!" );
        al_draw_textf(font, al_map_rgb(255, 255, 255), 200, 200 + (i * 20), 0, "%s ", jugadores[0].nombre);
        startNew();
    }
    else if (ball_x > p2_x) 
    {
        al_draw_textf(font,al_map_rgb(255, 0, 0), 320, 240, 0, "%s", "Player 2 Wins!");
        al_draw_textf(font, al_map_rgb(255, 255, 255), 200, 200 + (i * 20), 0, "%s ", jugadores[1].nombre);
        startNew();
    }

}

void setupGame()
{
    al_flip_display();
    al_draw_filled_rectangle(p1_x, p1_y, p1_x + 10, p1_y + 60, al_map_rgb(0, 0, 255));
    al_draw_filled_rectangle(p2_x, p2_y, p2_x + 10, p2_y + 60, al_map_rgb(0, 0, 255));
    al_draw_filled_circle(ball_x, ball_y, 5, al_map_rgb(128, 255, 0));
    al_flip_display();

    time(&secs);
    srand((unsigned int)secs);
    dir = rand() % 4 + 1;

}

void mapa()
{
    FILE *mapFile;
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
    bloque = al_load_bitmap("bloque.bmp");
    bloquereal = al_create_bitmap(20, 20);
    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 24; j++)
        {
            if (mapita[i][j] == 'x')
            {
                al_draw_bitmap(bloque, 20 * j, 20 * i, 0);
            }
        }
    }
}
