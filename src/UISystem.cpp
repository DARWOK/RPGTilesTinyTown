#include "UISystem.h"
UISystem* UISystem::instance = nullptr; // Initialize the static pointer to nullptr

Label* UISystem::createLabel(const char* text, int x, int y, int fontSize)
{
	Label* label = new Label();
	label->text = text;
	label->rect.x = x;
	label->rect.y = y;
	label->fontSize = fontSize;
	views.push_back(label);
	return label;
}

ImageView* UISystem::createImage(const char* image, int x, int y, int width, int height)
{
	ImageView* imageView = new ImageView(image, x,y,width,height);
	imageView->texture = LoadTexture(image);
	imageView->rect.x = x;
	imageView->rect.y = y;
	imageView->rect.width = width;
	imageView->rect.height = height;
	views.push_back(imageView);
	return imageView;
}

Button* UISystem::createButton(const char* text, int x, int y, int w, int h, int fontsize)
{
	Button* button = new Button();
	button->text = text;
	button->rect.width = w;
	button->rect.height = h;
	button->rect.x = x;
	button->rect.y = y;
	button->fontSize = fontsize;
	views.push_back(button);
	return button;
}

//Button* UISystem::createButton(const char* text, int x, int y, int width, int height)
//{
//	Button* button = new Button();
//	button->text = text;
//	button->rect.x = x;
//	button->rect.y = y;
//	button->rect.width = width;
//	button->rect.height = height;
//	views.push_back(button);
//	return button;
//}

void UISystem::draw()
{
	for (View* view : views)
	{
		if (view->visible)
			view->draw();
	}
}

void UISystem::update()
{
	for (View* view : views)
	{
		if (view->visible)
			view->update();
	}
}
