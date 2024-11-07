#include "pch.h"
#include "TileGrid.h"
#include "DSprite.h"
#include "DLine.h"

TileGrid::TileGrid()
{
}

TileGrid::~TileGrid()
{
}

bool TileGrid::Initialize()
{
	DSprite* sprite = new DSprite("character/player.png");
	SetDrawable(sprite);
	sprite->setPosition(100, 100);

	std::vector<sf::Vector2f> rowPoints;
	std::vector<sf::Vector2f> colPoints;
	float max = 100*100;
	for (int i = 0; i < 100; i++)
	{
		rowPoints.push_back({ 0,				i * 100.f });
		rowPoints.push_back({ max,				i * 100.f });
		colPoints.push_back({ i * 100.f,		0 });
		colPoints.push_back({ i * 100.f ,		max});
	}
	DLine* gridRow = new DLine(rowPoints.data(), rowPoints.size(), sf::Color::Red, false);
	DLine* gridCol = new DLine(colPoints.data(), colPoints.size(), sf::Color::Blue, false);
	SetDrawable(gridRow);
	SetDrawable(gridCol);

	return false;
}

void TileGrid::Reset()
{
	GetDrawable(1)->setRotation(45);
	GetDrawable(2)->setRotation(45);


}
