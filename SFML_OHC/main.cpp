#include "pch.h"
#include "Framework.h"

int main()
{
	Framework::GetInstance()->Initialize(540, 720, "Dragon Flight");
	Framework::GetInstance()->Do();
	Framework::GetInstance()->Release();
	return 0;
}