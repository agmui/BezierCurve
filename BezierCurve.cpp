#include "BezierCurve.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

BezierCurve::BezierCurve(SDL_Renderer *gRenderer, uint resolution)
{
    this->gRenderer = gRenderer;
    this->dotIndex = -1;
    this->curveIndex = 0;
    this->resolution = resolution;
    this->degree = 0;
}
BezierCurve::~BezierCurve()
{
}

float BezierCurve::lerp(float start, float end, float t)
{
    return start * (1 - t) + end * t;
}

// SDL_Point BezierCurve::lerpPoint(SDL_Point start, SDL_Point end, float t)
// {
//     return (SDL_Point){lerp(start.x, end.x, t), lerp(start.y, end.y, t)};
// }

SDL_FPoint BezierCurve::lerpLine(SDL_FPoint start, SDL_FPoint end, float t, bool showLines)
{

    SDL_FPoint newSDL_Point = {lerp(start.x, end.x, t), lerp(start.y, end.y, t)};
    if (showLines)
    {
        SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLineF(this->gRenderer, start.x, start.y, end.x, end.y);
        SDL_FRect fillRect = {newSDL_Point.x, newSDL_Point.y, 4.0, 4.0};
        SDL_RenderFillRectF(this->gRenderer, &fillRect);
    }

    return newSDL_Point;
}

/**
 * @brief draw an n degree Bezier curve
 * 
 * @param degree left degree as a var so the curve could change degrees on the fly
 * @param cords 
 * @param t 
 * @param showLines option to show lerp lines
 */
void BezierCurve::nDegreeCurve(int degree, SDL_FPoint cords[], float t, bool showLines)
{
    // //safe guard
    // if (degree == 0)
    // {
    // this->cords = cords;
    //     this->degree = degree;
    // }

    if (degree == 1)
    {
        this->curveIndex++;
        // std::cout << curveIndex<<','<<resolution << std::endl;
        this->curveIndex %= this->resolution;
        this->curve[this->curveIndex] = cords[0];
        for (auto &pt : curve)
        {
            SDL_RenderDrawPointF(this->gRenderer, pt.x, pt.y);
        }
        return;
    }

    SDL_FPoint newCords[degree];
    for (int i = 0; i < degree - 1; i++)
    {
        newCords[i] = lerpLine(cords[i], cords[i + 1], t, showLines);
    }

    nDegreeCurve(degree - 1, newCords, t, showLines);
}

void BezierCurve::drawHelpers(SDL_FPoint cords[], size_t numSDL_Points, bool mouseClick, int mouseX, int mouseY)
{
    if (mouseClick && dotIndex == -1)
    {
        for (size_t i = 0; i < numSDL_Points; i++)
        {
            if (cords[i].x - 4 < mouseX && mouseX < cords[i].x + 4 && cords[i].y - 4 < mouseY && mouseY < cords[i].y + 4)
            {
                dotIndex = i;
                break;
            }
        }
    }
    else if (!mouseClick)
    {
        dotIndex = -1;
    }
    else
    {
        cords[dotIndex].x = mouseX;
        cords[dotIndex].y = mouseY;
    }

    for (size_t i = 1; i < numSDL_Points - 1; i++)
    {
        SDL_FRect emptyRect = {cords[i].x - 4, cords[i].y - 4, 8.0, 8.0};
        SDL_RenderDrawRectF(this->gRenderer, &emptyRect);
    }
    SDL_FRect fillRect = {cords[0].x - 4, cords[0].y - 4, 8.0, 8.0};
    SDL_FRect fillRect2 = {cords[numSDL_Points - 1].x - 4, cords[numSDL_Points - 1].y - 4, 8.0, 8.0};
    SDL_RenderFillRectF(this->gRenderer, &fillRect);
    SDL_RenderFillRectF(this->gRenderer, &fillRect2);
    SDL_RenderDrawLineF(this->gRenderer, cords[0].x, cords[0].y, cords[1].x, cords[1].y);
    SDL_RenderDrawLineF(this->gRenderer, cords[numSDL_Points - 2].x, cords[numSDL_Points - 2].y, cords[numSDL_Points - 1].x, cords[numSDL_Points - 1].y);
}

// bezierCurve without t and just returns array of SDL_Points
// SDL_Point BezierCurve::bezierCurve()
// {
// }
