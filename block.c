#include "block.h"

SDL_Rect redbrick = {0, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect orangebrick = {31, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect whitebrick = {0, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect bluebrick = {32, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect bluelightbrick = {64,0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect greenbrick = {98,0,BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect navybrick = {128,0,BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect darkgreenbrick = {159,0,BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect pinkbrick = {64,16,BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect yellowbrick = {96,16,BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect darkredbrick = {128,16,BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect magentabrick = {160,16,BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect silverbrick1 = {0, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect silverbrick2 = {32, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect silverbrick3 = {64, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect silverbrick4 = {96, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect silverbrick5 = {128, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect silverbrick6 = {160, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect goldbrick1 = {0, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect goldbrick2 = {32, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect goldbrick3 = {64, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect goldbrick4 = {96, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect goldbrick5 = {128, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect goldbrick6 = {160, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect ball1 = {0, 64, BALL_SPRITE_WIDTH, BALL_SPRITE_HEIGHT};
SDL_Rect ball2 = {16, 64, BALL_SPRITE_WIDTH, BALL_SPRITE_HEIGHT};
SDL_Rect ball3 = {32, 64, BALL_SPRITE_WIDTH, BALL_SPRITE_HEIGHT};
SDL_Rect ball4 = {48, 64, BALL_SPRITE_WIDTH, BALL_SPRITE_HEIGHT};
SDL_Rect ball5 = {64, 64, BALL_SPRITE_WIDTH, BALL_SPRITE_HEIGHT};
SDL_Rect ball6 = {80, 64, BALL_SPRITE_WIDTH, BALL_SPRITE_HEIGHT};

SDL_Rect background1 = {0, 128, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect background2 = {64, 128, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect background3 = {128, 128, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect background4 = {192, 128, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect background5 = {256, 128, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect background6 = {320, 128, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};

SDL_Rect darkbackground1 = {0, 192, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect darkbackground2 = {64, 192, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect darkbackground3 = {128, 192, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect darkbackground4 = {192, 192, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect darkbackground5 = {256, 192, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};
SDL_Rect darkbackground6 = {320, 192, BACKGROUND_SPRITE_WIDTH, BACKGROUND_SPRITE_HEIGHT};

SDL_Rect a = {32, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect b = {64, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect c = {96, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect d = {128, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect e = {160, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect f = {192, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect g = {224, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect h = {256, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect i = {288, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect j = {320, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect k = {352, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect l = {384, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect m = {416, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect n = {448, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect o = {480, 64, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect p = {0, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect q = {32, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect r = {64, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect s = {96, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect t = {128, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect u = {160, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect v = {192, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect w = {224, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect x = {256, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect y = {288, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect z = {320, 96, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};

SDL_Rect zero = {0, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect un = {32, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect deux = {64, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect trois = {96, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect quatre = {128, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect cinq = {160, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect six = {192, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect sept = {224, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect huit = {256, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};
SDL_Rect neuf = {288, 32, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT};

SDL_Rect slow1 = {256, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect slow2 = {288, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect slow3 = {320, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect slow4 = {352, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect slow5 = {384, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect slow6 = {416, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect slow7 = {448, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect slow8 = {480, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect catch1 = {256, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect catch2 = {288, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect catch3 = {320, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect catch4 = {352, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect catch5 = {384, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect catch6 = {416, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect catch7 = {448, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect catch8 = {480, 16, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect expand1 = {256, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect expand2 = {288, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect expand3 = {320, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect expand4 = {352, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect expand5 = {384, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect expand6 = {416, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect expand7 = {448, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect expand8 = {480, 32, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect divide1 = {256, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect divide2 = {288, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect divide3 = {320, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect divide4 = {352, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect divide5 = {384, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect divide6 = {416, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect divide7 = {448, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect divide8 = {480, 48, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect laser1 = {256, 64, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect laser2 = {288, 64, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect laser3 = {320, 64, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect laser4 = {352, 64, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect laser5 = {384, 64, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect laser6 = {416, 64, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect laser7 = {448, 64, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect laser8 = {480, 64, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect break1 = {256, 80, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect break2 = {288, 80, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect break3 = {320, 80, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect break4 = {352, 80, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect break5 = {384, 80, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect break6 = {416, 80, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect break7 = {448, 80, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect break8 = {480, 80, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Rect player1 = {256, 96, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect player2 = {288, 96, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect player3 = {320, 96, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect player4 = {352, 96, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect player5 = {384, 96, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect player6 = {416, 96, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect player7 = {448, 96, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};
SDL_Rect player8 = {480, 96, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};