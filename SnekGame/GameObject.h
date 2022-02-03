#pragma once
#include <string>

enum class SpriteType {
	EMPTY_TILE,
	SNAKE_HEAD,
	SNAKE_TAIL,
	APPLE,
};

class GameObject {
	SpriteType m_sprite;
public:
	GameObject();

	GameObject(SpriteType sprite);

	/// <summary>
	/// Gets the character the sprite correspnds to
	/// </summary>
	/// <returns></returns>
	std::string getRenderedSprite();
};