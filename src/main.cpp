
#include <thread>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std::literals::chrono_literals;

constexpr auto tick_time = 100ms;

#include "level_0.hpp"
//#include "level_1.hpp"
//#include "level_2.hpp"
//#include "level_3.hpp"

constexpr char SNAKE_HEAD = '@';
constexpr char SNAKE_TAIL = '~';
constexpr char SNAKE_BODY[4] = {'>', 'v', '<', '^'};
constexpr char APPLE = '*';

constexpr int SNAKE_DIR_X_TABLE[4] = {1, 0, -1, 0};
constexpr int SNAKE_DIR_Y_TABLE[4] = {0, 1, 0, -1};

int snake_x = 1;
int snake_y = 0;
int snake_tail_x = 0;
int snake_tail_y = 0;

int snake_user_dir = 0;

int snake_dir = 0;
int snake_tail_dir = 0;

char screen[HEIGHT][WIDTH + 1][2];

bool shutdown = false;

int points = 0;

void spawn_apple() {
    int x, y;
    do {
        x = rand() % WIDTH;
        y = rand() % HEIGHT;
    } while (screen[y][x][0] != '.');
    screen[y][x][0] = APPLE;
}

void shrink_snake_tail() {
    // undraw snake tail
    screen[snake_tail_y][snake_tail_x][0] = '.';

    // move snake tail
    snake_tail_x += SNAKE_DIR_X_TABLE[snake_tail_dir];
    snake_tail_y += SNAKE_DIR_Y_TABLE[snake_tail_dir];

    // wrap snake tail
    if (snake_tail_x < 0) snake_tail_x += WIDTH;
    if (snake_tail_x >= WIDTH) snake_tail_x -= WIDTH;
    if (snake_tail_y < 0) snake_tail_y += HEIGHT;
    if (snake_tail_y >= HEIGHT) snake_tail_y -= HEIGHT;

    // calculate new snake tail direction
    switch (screen[snake_tail_y][snake_tail_x][0])
    {
    case SNAKE_BODY[0]: snake_tail_dir = 0; break;
    case SNAKE_BODY[1]: snake_tail_dir = 1; break;
    case SNAKE_BODY[2]: snake_tail_dir = 2; break;
    case SNAKE_BODY[3]: snake_tail_dir = 3; break;
    case SNAKE_HEAD: snake_tail_dir = snake_dir; break;
    }

    // draw snake tail
    screen[snake_tail_y][snake_tail_x][0] = SNAKE_TAIL;
}

void thread_main() {
    do {
        snake_dir = snake_user_dir;
        // get next block
        char next = screen[snake_y + SNAKE_DIR_Y_TABLE[snake_dir]][snake_x + SNAKE_DIR_X_TABLE[snake_dir]][0];
        
        if (next != APPLE) {
            shrink_snake_tail();
        }

        if (snake_tail_x != snake_x || snake_tail_y != snake_y) {
            // draw snake body
            screen[snake_y][snake_x][0] = SNAKE_BODY[snake_dir];
        }

        // move snake head
        snake_x += SNAKE_DIR_X_TABLE[snake_dir];
        snake_y += SNAKE_DIR_Y_TABLE[snake_dir];

        // wrap snake
        if (snake_x < 0) snake_x += WIDTH;
        if (snake_x >= WIDTH) snake_x -= WIDTH;
        if (snake_y < 0) snake_y += HEIGHT;
        if (snake_y >= HEIGHT) snake_y -= HEIGHT;

        bool died = false;
        bool apple_eaten = false;

        // interact with environment
        if (screen[snake_y][snake_x][0] == '.') {
            // move normally
        } else if (screen[snake_y][snake_x][0] == APPLE) {
            // eat apple
            apple_eaten = true;
        } else {
            died = true;
        }

        screen[snake_y][snake_x][0] = SNAKE_HEAD;

        if (apple_eaten) {
            points++;
            spawn_apple();
        }

        // render
        printf("\033[H\033[2J");
        printf("SNAKE! https://github.com/kernel32dev/cobrinha-c\r\n");
        printf("MAPA: %s\r\n", LEVEL_NAME);
        printf("setas para virar, \"qq\" para sair\r\n");
        printf("edite main.cpp para customizar o jogo!\r\n");
        fwrite(screen, sizeof(char), sizeof(screen), stdout);
        printf("pontos: %i\r\n", points);
        if (died) {
            printf("morreu!\r\n");
            break;
        }
        std::this_thread::sleep_for(tick_time);
    } while (!shutdown);
    shutdown = true;
}

int main() {
    system("stty raw");

    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            screen[y][x][0] = LEVEL[x + y * WIDTH];
            screen[y][x][1] = ' ';
        }
        screen[y][WIDTH][0] = '\r';
        screen[y][WIDTH][1] = '\n';
    }

    screen[snake_tail_y][snake_tail_x][0] = SNAKE_TAIL;
    screen[snake_y][snake_x][0] = SNAKE_HEAD;

    spawn_apple();

    auto thread = std::thread(thread_main);

    while (int c = getchar()) {
        if (shutdown) break;
        switch (c)
        {
        case 'A': if (snake_dir != 1) snake_user_dir = 3; break;
        case 'B': if (snake_dir != 3) snake_user_dir = 1; break;
        case 'C': if (snake_dir != 2) snake_user_dir = 0; break;
        case 'D': if (snake_dir != 0) snake_user_dir = 2; break;
        case 'q': {
            shutdown = true;
            break;
        }
        default:
            //printf("read a char: %c\n", c);
            break;
        }
    }

    thread.join();
    system("stty cooked");
    printf("\r\n");
}
