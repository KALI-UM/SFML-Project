#include "pch.h"
#include "Framework.h"

void Framework::Initialize(int width, int height, const std::string& name)
{
	m_MainWindow.create(sf::VideoMode(width, height), name);
	Utils::Initialize();
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

		// �̺�Ʈ ����
		IM->Clear();
		sf::Event event;
		while (m_MainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_MainWindow.close();

			IM->UpdateEvent(event);
		}

		// ������Ʈ
		GM->Update(m_DeltaTime);
		// ��ο�
		m_MainWindow.clear();
		GM->Render();
		m_MainWindow.display();
		GM->LateUpdate(m_DeltaTime);
		GM->FixedUpdate(m_DeltaTime);
	}
}

void Framework::Release()
{
}

