#include <SDL2/SDL.h>

class BezierCurve
{
private:
    SDL_Renderer *gRenderer;
    uint dotIndex;
    SDL_FPoint curve[100];
    uint curveIndex;
    uint resolution;
    uint degree;
    // SDL_Point cords[];

public:
    BezierCurve(SDL_Renderer *gRenderer, uint resolution=100);
    ~BezierCurve();

    float lerp(float start, float end, float t);

    // SDL_Point lerpPoint(SDL_Point start, SDL_Point end);
    SDL_FPoint lerpLine(SDL_FPoint start, SDL_FPoint end, float t, bool showLines);

    /**
     * @brief
     * Make sure degree is one less than the number of points
     * @param degree
     * @param cords
     * @param t
     * @param showLines
     */
    void nDegreeCurve(int degree, SDL_FPoint cords[], float t, bool showLines);
    void drawHelpers(SDL_FPoint cords[], size_t numSDL_Points, bool mouseClick, int mouseX, int mouseY);
    // SDL_Point bezierCurve();
};