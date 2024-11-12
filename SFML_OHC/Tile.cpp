#include "pch.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

bool Tile::Initialize()
{
	m_TextureId.push_back("tile/00.png");
	m_TextureId.push_back("tile/01.png");

	rapidcsv::Document doc("file/tiletest.csv", rapidcsv::LabelParams(-1, -1));
	for (int j = 0; j < 100; j++)
	{
		for (int i = 0; i < 100; i++)
		{
			DSprite* tileSprite = new DSprite(m_TextureId[doc.GetCell<int>(i, j)]);
			tileSprite->SetDebugDraw(false);
			tileSprite->SetOrigin(OriginType::BC);
			tileSprite->setLocalPosition({ (i)*m_CellSize.x, (j + 1) * m_CellSize.y });
			SetDrawable(tileSprite);
		}
	}
	return false;
}

void Tile::Reset()
{
}

void Tile::Update(float dt)
{
	sf::Vector2f tilepos = m_TileTransform.getInverse().transformPoint(IM->GetMouseViewPos(0));
	sf::Vector2i tileindex = sf::Vector2i(tilepos.x / m_CellSize.x, tilepos.y / m_CellSize.y);
	std::cout << tileindex.x << ", " << tileindex.y << std::endl;
	if (IM->GetMouseDown(sf::Mouse::Left))
	{
		if (tileindex.x >= 0 && tileindex.x < 100 || tileindex.y >= 0 || tileindex.y < 100)
			GetDrawable(tileindex.x + tileindex.y * 100)->SetFillColor(sf::Color::Blue);
	}
}

void Tile::SetTileTransform(const sf::Vector2f& zero, const sf::Transform& trans)
{
	m_TileTransform = trans;
	setPosition(zero);
	for (auto& tile : m_Drawable)
	{
		tile->setLocalPosition(m_TileTransform.transformPoint(tile->getLocalPosition()));
	}
}
