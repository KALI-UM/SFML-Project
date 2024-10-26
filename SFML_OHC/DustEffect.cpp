#include "pch.h"
#include "DustEffect.h"
#include "DSprite.h"

DustEffect::DustEffect()
	:EffectObject(5, new DSprite(DrawType::Effect))
{
}

DustEffect::~DustEffect()
{
}

bool DustEffect::Initialize()
{
	bool result = EffectObject::Initialize();
	
	DSprite* sprite;
	for (auto& particle : m_Particles)
	{
		sprite = dynamic_cast<DSprite*>(particle);
		sprite->SetTexture("monster/dust.png");
	}
	return result;
}

void DustEffect::Reset()
{
	EffectObject::Reset();
	for (auto& sprite : m_Particles)
	{
		sprite->SetOriginCenter();
	}

	m_Offset = 15.f;

	m_Particles[0]->Transform()->rotate(60);
	m_Particles[1]->Transform()->rotate(120);
	m_Particles[2]->Transform()->rotate(180);
	m_Particles[3]->Transform()->rotate(210);
	m_Particles[4]->Transform()->rotate(0);

	m_Particles[0]->Transform()->setScale(0.8f, 0.8f);
	m_Particles[1]->Transform()->setScale(1.6f, 1.6f);
	m_Particles[2]->Transform()->setScale(1, 1);
	m_Particles[3]->Transform()->setScale(0.2f, 0.2f);
	m_Particles[4]->Transform()->setScale(1.2f, 1.2f);
}

void DustEffect::EffectPlay(float dt)
{
	for (auto& particle : m_Particles)
	{
		sf::Vector2f scale = particle->Transform()->getScale();
		scale *= 1 - (dt * m_Speed);
		particle->Transform()->setScale(scale);
	}
}

void DustEffect::SetPosition()
{
	m_Particles[0]->Transform()->setPosition({ m_Position.x - m_Offset * 0.2f, m_Position.y - m_Offset * 0.7f });
	m_Particles[1]->Transform()->setPosition({ m_Position.x + m_Offset * 0.8f, m_Position.y + m_Offset });
	m_Particles[2]->Transform()->setPosition({ m_Position.x + m_Offset * 1.2f, m_Position.y - m_Offset });
	m_Particles[3]->Transform()->setPosition({ m_Position.x - m_Offset, m_Position.y + m_Offset * 0.5f });
	m_Particles[4]->Transform()->setPosition({ m_Position.x, m_Position.y });
}
