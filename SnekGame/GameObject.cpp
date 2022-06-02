#include "GameObject.h"

GameObject::GameObject() : m_sprite{ SpriteType::EMPTY_TILE } {}

GameObject::GameObject(SpriteType sprite) : m_sprite{ sprite } {}

std::string GameObject::getRenderedSprite() {
	switch (m_sprite) {
		case SpriteType::EMPTY_TILE:
			return " ";
		case SpriteType::SNAKE_HEAD:
			return "O";
		case SpriteType::SNAKE_TAIL:
			return "*";
		case SpriteType::APPLE:
			return "@";
		default:
			return "X";
	}
}

SpriteType GameObject::getSprite() {
	return m_sprite;
}