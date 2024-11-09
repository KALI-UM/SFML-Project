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
	std::vector<sf::Vector2f> rowPoints;
	std::vector<sf::Vector2f> colPoints;
	for (int i = 0; i < 100; i++)
	{
		rowPoints.push_back({ 0,					i * m_CellSize.y });
		rowPoints.push_back({ m_CellSize.x * 100,	i * m_CellSize.y });
		colPoints.push_back({ i * m_CellSize.x,		0 });
		colPoints.push_back({ i * m_CellSize.x ,	m_CellSize.y * 100 });
	}
	DLine* gridRow = new DLine(rowPoints.data(), rowPoints.size(), sf::Color::Red, false);
	DLine* gridCol = new DLine(colPoints.data(), colPoints.size(), sf::Color::Blue, false);
	SetDrawable(gridRow);
	SetDrawable(gridCol);

	return false;
}

void TileGrid::Reset()
{

}

void TileGrid::Update(float dt)
{
}
