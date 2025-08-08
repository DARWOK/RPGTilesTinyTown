#pragma once
#include <View.h>

class ImageView : public View
{
public:
	Texture2D texture;

	ImageView(const char* image, int x, int y, int w, int h);

	void update() override;
	void draw() override;

};

