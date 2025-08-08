#include "Sidekick.h"

using namespace LoW;

void Sidekick::update()
{
	if (owner != nullptr)
	{
		Vector2 dir = Vector2Subtract(owner->position, position);

		float distance = Vector2Length(dir);
		if (distance > 50)
		{
			dir = Vector2Normalize(dir);
			position = Vector2Add(position, Vector2Scale(dir, speed * GetFrameTime()));
		}
	}
}
