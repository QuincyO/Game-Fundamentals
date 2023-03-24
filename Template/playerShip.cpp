#include "playerShip.h"

playerShip::playerShip(const char* texture) : fundObject(texture)
{
}

Vec2 playerShip::getPos()
{
    Vec2 returnVector = { dst.x,dst.y };
    return returnVector;
}

Vec2 playerShip::getSize()
{
    Vec2 objectSize = { dst.w,dst.h };
    return objectSize;
}

void playerShip::setSize(Vec2 width_or_height)
{
    dst.w = width_or_height.x;
    dst.y = width_or_height.y;

}

void playerShip::setPos(Vec2 XposY)
{
    dst.x = XposY.x;
    dst.y = XposY.y;
}

void playerShip::setSpriteSheetInfo(int width_of_frame, int height_of_frame, int amount_of_frames)
{

}

void playerShip::input()
{

}

void playerShip::update()
{

}

void playerShip::shoot()
{

}

void playerShip::draw()
{

}
