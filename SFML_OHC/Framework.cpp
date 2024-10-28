#include "pch.h"
#include "Framework.h"

void Framework::Initialize(int width, int height, const std::string& name)
{
	m_MainWindow.create(sf::VideoMode(width, height), name);
	//m_View.reset(sf::FloatRect(0, 0, m_MainWindow.getSize().x, m_MainWindow.getSize().y));
	m_View.reset(sf::FloatRect(0, 0, m_MainWindow.getSize().x*2, m_MainWindow.getSize().y*2));
	m_View2.reset(sf::FloatRect(0 , 0 , m_MainWindow.getSize().x*4 , m_MainWindow.getSize().y*4));
	GM->Initialize(&m_MainWindow);
	IM->Initialize();
	SM->Initialize();
}

void Framework::Do()
{
	while (m_MainWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		m_RealDeltaTime = m_DeltaTime = dt.asSeconds();
		m_DeltaTime *= m_TimeScale;
		m_RealTime += m_RealDeltaTime;
		m_Time += m_DeltaTime;

		// 이벤트 루프
		IM->Clear();
		sf::Event event;
		while (m_MainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_MainWindow.close();

			IM->Update(event);
		}

		// 업데이트
		GM->Update(m_DeltaTime);
		// 드로우
		m_MainWindow.clear();
		m_MainWindow.setView(m_View);
		GM->Render();
		m_MainWindow.setView(m_View2);
		GM->Render2();
		m_MainWindow.display();
		GM->LateUpdate();
	}
}

void Framework::Release()
{
}

