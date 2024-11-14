#include "pch.h"
#include "Tile.h"
#include "DTile.h"
#include "TileResTable.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

bool Tile::Initialize()
{
	m_TileInfos = std::vector<std::vector<TileInfo>>(m_CellCount.y, std::vector<TileInfo>(m_CellCount.x));

	rapidcsv::Document doc("datatables/tiletest.csv", rapidcsv::LabelParams(-1, -1));
	int row = doc.GetRowCount();
	int col = doc.GetColumnCount();
	for (int j = 0; j < m_CellCount.y; j++)
	{
		for (int i = 0; i < m_CellCount.x; i++)
		{
			m_TileInfos[j][i].type = (TileType)doc.GetCell<int>(i * 2, j);
			m_TileInfos[j][i].name = doc.GetCell<std::string>(i * 2 + 1, j);
			m_TileInfos[j][i].filepath = DATATABLE_TILERES->GetTileFilePath(GetTypeToString(m_TileInfos[j][i].type), m_TileInfos[j][i].name);
			DTile* tileSprite = new DTile(m_TileInfos[j][i].filepath);
			tileSprite->SetLot({ 1, 1 });
			tileSprite->SetDebugDraw(false);
			tileSprite->SetOrigin(OriginType::BC, { -1.0f,-3.0f });
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
	sf::Vector2f tilepos = m_TileTransform.getInverse().transformPoint(INPUT_MGR->GetMouseViewPos(0));
	sf::Vector2i tileindex = sf::Vector2i(tilepos.x / m_CellSize.x, tilepos.y / m_CellSize.y);
	//std::cout << tileindex.x << ", " << tileindex.y << std::endl;
	if (INPUT_MGR->GetMouseDown(sf::Mouse::Left))
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

std::string Tile::GetTypeToString(TileType type) const
{
	switch (type)
	{
	case TileType::Terrain:
		return "terrain";
		break;
	case TileType::Building:
		return "building";
		break;
	case TileType::Zone:
		return "zone";
		break;
	case TileType::Road:
		return "road";
		break;
	case TileType::Rail:
		return "rail";
		break;
	case TileType::Highway:
		return "highway";
		break;
	case TileType::Underground:
		return "underground";
		break;
	case TileType::Other:
		return "other";
		break;
	}
}
