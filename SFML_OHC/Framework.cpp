#include "pch.h"
#include "Framework.h"

void Framework::Initialize(int width, int height, const std::string& name)
{
	m_MainWindow.create(sf::VideoMode(width, height), name);
	Utils::Initialize();
	GM->Initialize(&m_MainWindow);
	IM->Initialize();
	SM->Initialize();
	ImGuiManager::Init(&m_MainWindow);
}

void Framework::Do()
{
	m_MainWindow.setFramerateLimit(60);
	sf::Time dt = clock.restart();

	while (m_MainWindow.isOpen())
	{
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
			ImGuiManager::PollEvent(event);
			IM->UpdateEvent(event);
		}

		// 업데이트
		if (m_RealTime - m_FixedTimePrev > m_FixedTimeStamp)
		{
			m_FixedTimePrev = m_RealTime;
			GM->FixedUpdate(m_RealDeltaTime);
		}

		GM->Update(m_DeltaTime);
		GM->LateUpdate(m_DeltaTime);

		// 드로우
		m_MainWindow.clear();

		//std::cout << 1.0f / m_RealDeltaTime << std::endl;

		GM->Render();

		{ // ImGui Layer
			ImGuiManager::Begin(dt);
			GM->ImGuiUpdate();
			ImGuiManager::End();
		}

		m_MainWindow.display();

		dt = clock.restart();
	}
}

void Framework::Release()
{
	ImGuiManager::Release();
}

