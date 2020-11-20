#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#endif
// Option vars:
bool printFps = false; // False by defualt due to issues with the terminal
// ------------
bool hasFocus = false;
bool mouseFocus = false;
bool menu = true;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
SDL_Rect bg;
SDL_Rect p1;
SDL_Rect p2;
bool rc = false;
float p1g = 0;
float p2g = 0;
float p1r = 0;
float p2r = 0;
bool chkcycle = false;
bool isRunning = true;
bool fullscr = false;
bool setfscrmode = false;
bool rp1ot = true;
int fps;
int p1s = 0;
int p2s = 0;
int pto = 0;
int p2aihc = 300;
bool sp = false;
SDL_Rect ptrail1[16];
SDL_Rect ptrail2[16];
Uint32 trv[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Uint32 getTimer(Uint8 tn) {
    return SDL_GetTicks() - trv[tn];
}
void resetTimer(Uint8 tn) {
    trv[tn] = SDL_GetTicks();
    return;
}
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    return main(0, NULL);
}
#endif
void handleSDLEvents()
{
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
            continue;
        }
        if (event.type == SDL_WINDOWEVENT || true) {
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                hasFocus = true;
                SDL_ShowCursor(0);
            }
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                hasFocus = false;
                mouseFocus = false;
                SDL_ShowCursor(1);
            }
            if (event.window.event == SDL_WINDOWEVENT_ENTER && hasFocus) {
                mouseFocus = true;
            }
        }
    }
    const Uint8 *KBS = SDL_GetKeyboardState(NULL);
    if ((KBS[SDL_SCANCODE_LALT] || KBS[SDL_SCANCODE_RALT]) && KBS[SDL_SCANCODE_RETURN]) {
        fullscr = !fullscr;
        setfscrmode = false;
        while ((KBS[SDL_SCANCODE_LALT] || KBS[SDL_SCANCODE_RALT]) && KBS[SDL_SCANCODE_RETURN]) {
            SDL_PollEvent(&event);
        }
    }
    if (KBS[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }
    if (getTimer(1) >= 1000) {
        resetTimer(1);
        if (printFps) {printf("\033[s\033[0;0H\033[K\n\033[K\033[0;0HFPS: %d\n\033[u", fps);}
        fps = 0;
    }
    return;
}
void renderScreen(TTF_Font *df) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 63, 255);
    SDL_RenderClear(renderer);
    if (rp1ot) {
        for (int i = 0; i <= 15; i++) {
            SDL_SetRenderDrawColor(renderer, 127, 34, 255, 2);
            SDL_RenderFillRect(renderer, &ptrail2[i]);
            pto++;
            if (pto >= 16) {
                pto = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 12, 255, 255);
        SDL_RenderFillRect(renderer, &p2);
        for (int i = 0; i <= 15; i++) {
            SDL_SetRenderDrawColor(renderer, 128, 255, 12, 2);
            SDL_RenderFillRect(renderer, &ptrail1[i]);
            pto++;
            if (pto >= 16) {
                pto = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 12, 255);
        SDL_RenderFillRect(renderer, &p1);
    } else {
        for (int i = 0; i <= 15; i++) {
            SDL_SetRenderDrawColor(renderer, 127, 34, 255, 2);
            SDL_RenderFillRect(renderer, &ptrail2[i]);
            pto++;
            if (pto >= 16) {
                pto = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 12, 255, 255);
        SDL_RenderFillRect(renderer, &p2);
        for (int i = 0; i <= 15; i++) {
            SDL_SetRenderDrawColor(renderer, 128, 255, 12, 2);
            SDL_RenderFillRect(renderer, &ptrail1[i]);
            pto++;
            if (pto >= 16) {
                pto = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 12, 255);
        SDL_RenderFillRect(renderer, &p1);
    }
    char sv1[4];
    char sv2[4];
    sprintf(sv1, "%d", p1s);
    sprintf(sv2, "%d", p2s);
    SDL_Color fontColor = {0, 255, 0, 192};
    SDL_Surface * pss1 = TTF_RenderText_Solid(df, sv1, fontColor);
    SDL_Surface * pss2 = TTF_RenderText_Solid(df, sv2, fontColor);
    SDL_Surface * spms1 = TTF_RenderText_Solid(df, "1: One Player" , fontColor);
    SDL_Surface * spms2 = TTF_RenderText_Solid(df, "2: Two Players" , fontColor);
    SDL_Texture * pst1 = SDL_CreateTextureFromSurface(renderer, pss1);
    SDL_Texture * pst2 = SDL_CreateTextureFromSurface(renderer, pss2);
    SDL_Texture * spmt1 = SDL_CreateTextureFromSurface(renderer, spms1);
    SDL_Texture * spmt2 = SDL_CreateTextureFromSurface(renderer, spms2);
    int pstw1 = 0;
    int pstw2 = 0;
    int spmw1 = 0;
    int spmw2 = 0;
    int psth1 = 0;
    int psth2 = 0;
    int spmh1 = 0;
    int spmh2 = 0;
    SDL_QueryTexture(pst1, NULL, NULL, &pstw1, &psth1);
    SDL_QueryTexture(pst2, NULL, NULL, &pstw2, &psth2);
    SDL_QueryTexture(spmt1, NULL, NULL, &spmw1, &spmh1);
    SDL_QueryTexture(spmt2, NULL, NULL, &spmw2, &spmh2);
    pstw1 = pstw1 / 2;
    pstw2 = pstw2 / 2;
    psth1 = psth1 / 2;
    psth2 = psth2 / 2;
    SDL_Rect txt1 = {0, 0, pstw1, psth1};
    SDL_Rect txt2 = {639 - pstw2, 0, pstw2, psth2};
    SDL_Rect txt3 = {320 - spmw1 / 4 - 1, 120, spmw1 / 2, 36};
    SDL_Rect txt4 = {320 - spmw2 / 4 - 1, 156, spmw2 / 2, 36};
    SDL_RenderCopy(renderer, pst1, NULL, &txt1);
    SDL_RenderCopy(renderer, pst2, NULL, &txt2);
    if (menu) {
        SDL_RenderCopy(renderer, spmt1, NULL, &txt3);
        SDL_RenderCopy(renderer, spmt2, NULL, &txt4);
    }
    SDL_DestroyTexture(pst1);
    SDL_DestroyTexture(pst2);
    SDL_FreeSurface(pss1);
    SDL_FreeSurface(pss2);
    fps++;
    if (getTimer(0) < (100/6)) {
        SDL_Delay(100/6 - getTimer(0));
    }
    resetTimer(0);
    if (!setfscrmode) {
        setfscrmode = true;
        if (fullscr) {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        } else {
            SDL_SetWindowFullscreen(window, 0);
        }
    }
    SDL_RenderPresent(renderer);
    return;
}
void doGameLogic()
{
    if (chkcycle) {SDL_PollEvent(&event);}
    const Uint8 *KBS = SDL_GetKeyboardState(NULL);
    bool aiup = false;
    bool aileft = false;
    bool airight = false;
    int aip = (p2.x) - (p1.x);
    if (menu) {
        if (KBS[SDL_SCANCODE_1]) {
            sp = true;
            menu = false;
        }
        if (KBS[SDL_SCANCODE_2]) {
            sp = false;
            menu = false;
        }
        goto sgl;
    }
    if (p1r > 0) {p1r = p1r - 0.1;}
    if (p1r < 0) {p1r = p1r + 0.1;}
    if (p2r > 0) {p2r = p2r - 0.1;}
    if (p2r < 0) {p2r = p2r + 0.1;}
    if (sp) {
        p2aihc = 300;
        if (abs(p1.x + 10 - p2.x + 10) < 250 + rand()%15 && rand()%1 == 0 && (p2r > 5 || p2r < -5)) {aiup = true; p2aihc = 200;}
        if (abs(p1.x + 10 - p2.x + 10) < 220 + rand()%10 && rand()%3 == 0) {aiup = false;}
        if (abs(p1.x + 10 - p2.x + 10) < 50 + rand()%5 && rand()%1 == 0) {aiup = true;}
        if (abs(p1.x + 10 - p2.x + 10) < 40 + rand()%5 && rand()%1 == 0) {aiup = false;}
        if (p2.y < 450) {aiup = false;}
        if ((aip < -10 && p2.y > 400) || (p2r < 0 && p2.y < 415) && p1.y > p2aihc) {airight = true;}
        if ((aip > 10 && p2.y > 400) || (p2r > 0 && p2.y < 415) && p1.y > p2aihc) {aileft = true;}
    }
    if (p1g > -15 && chkcycle) {p1g = p1g - 0.75;}
    if (p2g > -15 && chkcycle) {p2g = p2g - 0.75;}
    if (KBS[SDL_SCANCODE_A] && p1r > -15) {p1r = p1r - 0.23;}
    if (KBS[SDL_SCANCODE_D] && p1r < 15) {p1r = p1r + 0.23;}
    if (((KBS[SDL_SCANCODE_LEFT] && !sp) || aileft) && p2r > -15) {p2r = p2r - 0.23;}
    if (((KBS[SDL_SCANCODE_RIGHT] && !sp) || airight) && p2r < 15) {p2r = p2r + 0.23;}
    p1.x = p1.x + p1r;
    p2.x = p2.x + p2r;
    if (p1.x > 620) {p1.x = 620; p1r = p1r * -0.25;}
    if (p1.x < 0) {p1.x = 0; p1r = p1r * -0.25;}
    if (p2.x > 620) {p2.x = 620; p2r = p2r * -0.25;}
    if (p2.x < 0) {p2.x = 0; p2r = p2r * -0.25;}
    p1.y = p1.y - p1g;
    p2.y = p2.y - p2g;
    if (p1.y > 430) {
        if (p1.y >= 460) {
            p1.y = 460;
            p1g = p1g * -0.3 - 0.5;
            if (KBS[SDL_SCANCODE_A] && p1r > -15) {p1r = p1r - 0.87;}
            if (KBS[SDL_SCANCODE_D] && p1r < 15) {p1r = p1r + 0.87;}
            if (KBS[SDL_SCANCODE_W] && chkcycle) {
                p1g = p1g / 1.5;
            }
            if (p1r > 0) {p1r = p1r - 0.5;}
            if (p1r < 0) {p1r = p1r + 0.5;}
        }
        if (KBS[SDL_SCANCODE_W] && chkcycle) {
            p1g = p1g + 5.5;
        }
    }
    if (p2.y > 430) {
        if (p2.y >= 460) {
            p2.y = 460;
            p2g = p2g * -0.3 - 0.5;
            if (((KBS[SDL_SCANCODE_LEFT] && !sp) || aileft) && p2r > -15) {p2r = p2r - 0.87;}
            if (((KBS[SDL_SCANCODE_RIGHT] && !sp) || airight) && p2r < 15) {p2r = p2r + 0.87;}
            if (((KBS[SDL_SCANCODE_UP] && !sp) || aiup) && chkcycle) {
                p2g = p2g / 1.5;
            }
            if (p2r > 0) {p2r = p2r - 0.5;}
            if (p2r < 0) {p2r = p2r + 0.5;}
        }
        if (((KBS[SDL_SCANCODE_UP] && !sp) || aiup) && chkcycle) {
            p2g = p2g + 5.5;
        }
    }
    chkcycle = !chkcycle;
    rc = false;
    if (p2.x + 20 - p1.x > -1 && p1.x + 20 - p2.x > -1 && p2.y + 20 - p1.y > -1 && p1.y + 20 - p2.y > -1) {rc = true;}
    if (!rc) {
        rp1ot = rand()%2;
    } else {
        if (p1g < 0.1 && p1.y + 20 < p2.y + 17 && p1.y + 20 > p2.y - 1) {
            p2.x = 520; p2.y = -120;
            p1s++;
        }
        if (p2g < 0.1 && p2.y + 20 < p1.y + 17 && p2.y + 20 > p1.y - 1) {
            p1.x = 99; p1.y = -120;
            p2s++;
        }
    }
    ptrail1[pto].x = p1.x;
    ptrail1[pto].y = p1.y;
    ptrail2[pto].x = p2.x;
    ptrail2[pto].y = p2.y;
    pto++;
    if (pto >= 16) {
        pto = 0;
    }
    sgl:
    menu = menu;
    return;
}
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window = SDL_CreateWindow("Block Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    bg.x = 0; bg.y = 0; bg.w = 640; bg.h = 480;
    p1.x = 99; p1.y = -120; p1.w = 20; p1.h = 20;
    p2.x = 520; p2.y = -120; p2.w = 20; p2.h = 20;
    TTF_Font * font = TTF_OpenFont("LCD_MONO.TTF", 96);
    for (int i = 0; i <= 15; i++) {
        ptrail1[i].h = 20;
        ptrail1[i].w = 20;
        ptrail2[i].h = 20;
        ptrail2[i].w = 20;
        ptrail1[i].x = 99;
        ptrail1[i].y = -120;
        ptrail2[i].x = 520;
        ptrail2[i].y = -120;
    }
    while (isRunning) {
        handleSDLEvents();
        doGameLogic();
        renderScreen(font);
    }
    SDL_SetWindowFullscreen(window, 0);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

