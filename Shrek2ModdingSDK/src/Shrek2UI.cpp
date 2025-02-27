/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2DirectX.h"
#define D3D_RELEASE(D3D_PTR) if( D3D_PTR ){ D3D_PTR->Release(); D3D_PTR = NULL; }

void Shrek2UI::Initialize()
{
	try {
		IsUIRunning = true;
		std::cout << "Trying to attach to Shrek 2's UI Pipeline (DirectX)" << std::endl;
		bool hasHookedEndScene = false;
		while (hasHookedEndScene == false) {
			hasHookedEndScene = HookEndScene();
			if (hasHookedEndScene == false) {
				Sleep(500);
			}
		}
		std::cout << "Successfully attached to Shrek 2's UI Pipeline (DirectX)" << std::endl;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::Initialize", ex.what());
	}
}

void Shrek2UI::Reset(IDirect3DDevice8* pDevice) {
	try {
		D3D_RELEASE(shLargeFont);
		D3D_RELEASE(shNormalFont);
		D3D_RELEASE(shSmallFont);
		D3D_RELEASE(g_pSprite);

		D3DXCreateFont(pDevice, hLargeFont, &shLargeFont);
		D3DXCreateFont(pDevice, hNormalFont, &shNormalFont);
		D3DXCreateFont(pDevice, hSmallFont, &shSmallFont);
		D3DXCreateSprite(pDevice, &g_pSprite);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::Reset", ex.what());
	}
}

void Shrek2UI::InitializeFonts(IDirect3DDevice8* pDevice)
{
	try {
		if (!hLargeFont) {
			hLargeFont = CreateFont(30, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, PROOF_QUALITY, 0, "Arial");
			D3DXCreateFont(pDevice, hLargeFont, &shLargeFont);
		}

		if (!hNormalFont) {
			hNormalFont = CreateFont(20, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, PROOF_QUALITY, 0, "Arial");
			D3DXCreateFont(pDevice, hNormalFont, &shNormalFont);
		}

		if (!hSmallFont) {
			hSmallFont = CreateFont(15, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, PROOF_QUALITY, 0, "Arial");
			D3DXCreateFont(pDevice, hSmallFont, &shSmallFont);
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::InitializeFonts", ex.what());
	}
}

void Shrek2UI::InitializeSprite(IDirect3DDevice8* pDevice)
{
	try {
		if (!g_pSprite) {
			D3DXCreateSprite(pDevice, &g_pSprite);
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::InitializeSprite", ex.what());
	}
}

void Shrek2UI::RenderRectangle(Shrek2Rect rect, D3DCOLOR color) {
	try {
		D3DRECT rectangle = { rect.X, rect.Y, rect.X2, rect.Y2 };
		GlobalPDevice->Clear(1, &rectangle, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0.0f, 0);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::RenderRectangle", ex.what());
	}
}

void Shrek2UI::RenderText(Shrek2Rect rect, std::string text, D3DCOLOR color, Shrek2Fonts font, DWORD alignment)
{
	try {
		RECT textRectangle;
		SetRect(&textRectangle, rect.X, rect.Y, rect.X2, rect.Y2);

		if (font == Shrek2Fonts::Large)
		{
			shLargeFont->DrawText(text.c_str(), -1, &textRectangle, alignment, color);
		}
		else if (font == Shrek2Fonts::Medium) 
		{
			shNormalFont->DrawText(text.c_str(), -1, &textRectangle, alignment, color);
		}
		else if(font == Shrek2Fonts::Small) {
			shSmallFont->DrawText(text.c_str(), -1, &textRectangle, alignment, color);
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::RenderText1", ex.what());
	}
}

void Shrek2UI::RenderText(Shrek2Rect rect, std::string text, D3DCOLOR color, bool isNormalText)
{
	try {
		RECT textRectangle;
		SetRect(&textRectangle, rect.X, rect.Y, rect.X2, rect.Y2);

		if (isNormalText) {
			shNormalFont->DrawText(text.c_str(), -1, &textRectangle, DT_LEFT, color);
		}
		else {
			shSmallFont->DrawText(text.c_str(), -1, &textRectangle, DT_LEFT, color);
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::RenderText2", ex.what());
	}
}

void Shrek2UI::RenderTextCenter(Shrek2Rect rect, std::string text, D3DCOLOR color, Shrek2Fonts font)
{
	try {
		RECT textRectangle;
		SetRect(&textRectangle, rect.X, rect.Y, rect.X2, rect.Y2);

		if (font == Shrek2Fonts::Large)
		{
			shLargeFont->DrawText(text.c_str(), -1, &textRectangle, DT_CENTER, color);
		}
		else if (font == Shrek2Fonts::Medium)
		{
			shNormalFont->DrawText(text.c_str(), -1, &textRectangle, DT_CENTER, color);
		}
		else if (font == Shrek2Fonts::Small) {
			shSmallFont->DrawText(text.c_str(), -1, &textRectangle, DT_CENTER, color);
		}
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::RenderTextCenter", ex.what());
	}
}

void Shrek2UI::RenderTexture(Shrek2Texture texture, Shrek2Position position, D3DXCOLOR color)
{
	try {
		g_pSprite->Begin();
		{
			auto pos = D3DXVECTOR2(position.X, position.Y);
			g_pSprite->Draw(texture.Texture, NULL, NULL, NULL, 0, &pos, color);
		}
		g_pSprite->End();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::RenderTexture1", ex.what());
	}
}

void Shrek2UI::RenderTexture(Shrek2Texture texture, Shrek2Position position, float rotation, D3DXCOLOR color)
{
	try {
		g_pSprite->Begin();
		{
			auto pos = D3DXVECTOR2(position.X, position.Y);
			g_pSprite->Draw(texture.Texture, NULL, NULL, NULL, rotation, &pos, color);
		}
		g_pSprite->End();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::RenderTexture2", ex.what());
	}
}

void Shrek2UI::RenderTexture(Shrek2Texture texture, Shrek2Position position, Shrek2Vector2 scale, float rotation, D3DXCOLOR color)
{
	try {
		g_pSprite->Begin();
		{
			auto pos = D3DXVECTOR2(position.X, position.Y);
			auto drawScale = D3DXVECTOR2(scale.X, scale.Y);
			g_pSprite->Draw(texture.Texture, NULL, &drawScale, NULL, rotation, &pos, color);
		}
		g_pSprite->End();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::RenderTexture3", ex.what());
	}
}

void Shrek2UI::RenderTexture(Shrek2Texture texture, Shrek2Vector2 position, D3DXCOLOR color)
{
	try {
		g_pSprite->Begin();
		{
			auto pos = D3DXVECTOR2(position.X, position.Y);
			g_pSprite->Draw(texture.Texture, NULL, NULL, NULL, 0, &pos, color);
		}
		g_pSprite->End();
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::RenderTexture4", ex.what());
	}
}

void Shrek2UI::StopUI() {
	try {
		IsUIRunning = false;
		Shrek2Textures::ReleaseTextures();
		if (pEndScene) DetourDetach((PVOID*)pEndScene, (PBYTE)hookedEndScene);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::StopUI", ex.what());
	}
}

void Shrek2UI::TriggerReset()
{
	try {
		IsResetNeeded = true;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::TriggerReset", ex.what());
	}
}

D3DCOLOR Shrek2UI::GetColor(int r, int g, int b) {
	return D3DCOLOR_ARGB(255, r, g, b);
}

D3DCOLOR Shrek2UI::GetColorAlpha(int r, int g, int b, int a) {
	return D3DCOLOR_ARGB(a, r, g, b);
}

HRESULT __stdcall Shrek2UI::hookedEndScene(IDirect3DDevice8* pDevice)
{
	try {
		if (IsUIRunning) {
			GlobalPDevice = pDevice;
			if (!ViewportLoaded) {
				ViewportLoaded = true;
				GlobalPDevice->GetViewport(&Viewport);
				LastGameWindowSize = GameWindowSize;
			}

			InitializeFonts(pDevice);
			InitializeSprite(pDevice);
			Shrek2Textures::InitializeTextures(pDevice);

			if (EqualRect(&GameWindowSize, &LastGameWindowSize) == false || IsResetNeeded) {
				IsResetNeeded = false;
				LastGameWindowSize = GameWindowSize;
				pDevice->GetViewport(&Viewport);
				Reset(pDevice);
				Shrek2Textures::ReleaseTextures();
				Shrek2Textures::InitializeTextures(pDevice);
			}

			RenderUI();
		}
		return pEndScene(pDevice);
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::HookedEndScene", ex.what());
		return NULL;
	}
}

bool Shrek2UI::HookEndScene()
{
	try {
		IDirect3D8* pD3D = Direct3DCreate8(D3D_SDK_VERSION);
		if (!pD3D) return false;

		D3DPRESENT_PARAMETERS d3dparams = { 0 };
		d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dparams.hDeviceWindow = GetForegroundWindow();
		d3dparams.Windowed = true;
		d3dparams.BackBufferHeight = 0L;
		d3dparams.BackBufferWidth = 0L;
		d3dparams.BackBufferFormat = D3DFMT_A8R8G8B8;

		IDirect3DDevice8* pDevice = NULL;

		HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dparams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dparams, &pDevice);
		if (FAILED(result) || !pDevice) {
			pD3D->Release();
			return false;
		}
		void** vTable = *reinterpret_cast<void***>(pDevice);

		pEndScene = (endScene)DetourAttach((PVOID*)vTable[35], (PBYTE)hookedEndScene);

		pDevice->Release();
		pD3D->Release();

		return true;
	}
	catch (std::exception& ex)
	{
		Shrek2Logging::LogError("Shrek2UI::HookEndScene", ex.what());
		return false;
	}
}