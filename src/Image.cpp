#include "Image.h"

void ImageView::update()
{
    // No update logic needed for static images
}

ImageView::ImageView(const char* image, int x, int y, int w, int h)
    : View(x, y, w, h)
{
    texture = LoadTexture(image);
}

void ImageView::draw()
{
	DrawTexture(texture, rect.x, rect.y, WHITE);
}