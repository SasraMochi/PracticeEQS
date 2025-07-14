#include <windows.h>
#include "DxLib.h"
#include <assert.h> // �摜�ǂݍ��ݎ��s�\���p

#include "Math/MySystemTimer.h"
#include "Math/Screen.h"
#include "Game.h"

#include "imgui.h"
#include <Backends/imgui_impl_win32.h>
#include <Backends/imgui_impl_dx11.h>

#include "imnodes.h"

// FPS�֘A�ݒ�
int TargetFPS = 60;
static bool EnableFrameSkip = true;
double MaxAllowSkipTime = 0.2;
long IntervalTicks = (long)(1.0 / TargetFPS * 10000000);
int MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);

static long nextFrameTicks = IntervalTicks;
static int skipCount = 0;
static long fpsTicks = 0;
static int fpsFrameCount = 0;
static float CurrentFPS; // ���݂�FPS

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ImGui�Ƀv���V�[�W���̏��𗬂�
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp)) {
		return true;
	}

	return 0;
}

// �`�揈��
static void GameDraw(Game& game)
{
	ClearDrawScreen();
	game.draw();

	// ImGui�̕`��
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	game.draw_debug();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ScreenFlip();
	skipCount = 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �v���O�����̏����D��x���グ��
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	// ���������̐ݒ�
	SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);

	// ��ʃ��[�h�̐ݒ�
	SetWindowSize(Screen::Width, Screen::Height);
	SetGraphMode(Screen::Width, Screen::Height, 32);
	SetMainWindowText("�Q�[���̃E�B���h�E����ς���Ƃ��͂���");
	ChangeWindowMode(TRUE);
	SetAlwaysRunFlag(TRUE);

	// DX���C�u�����̏�����
	if (DxLib_Init() < 0) return -1;

	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseTransColor(FALSE);

	// ImGui�̏�����
	ImGui::CreateContext();
	ImNodes::CreateContext();
	g_pd3dDevice = (ID3D11Device*)(GetUseDirect3D11Device());
	g_pd3dDeviceContext = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();
	ImGui_ImplWin32_Init(GetMainWindowHandle());
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	SetHookWinProc(WndProc);
	ImGui::GetIO().Fonts->AddFontFromFileTTF("c:/Windows/Fonts/meiryo.ttc", 40.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
	// ImGui_ImplDX11_CreateDeviceObjects();

	// �Q�[��������
	Game game(Screen::Width, Screen::Height);
	game.start();

	MySystemTimer& timer = MySystemTimer::GetInstance();
	ScreenFlip();
	timer.Init();

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// FPS�v��
		fpsFrameCount++;
		if (fpsFrameCount >= 60)
		{
			long elapsedTicks = timer.GetElapsedTicks() - fpsTicks;
			float elapsedSec = (float)elapsedTicks / 10000000;
			CurrentFPS = fpsFrameCount / elapsedSec;
			fpsFrameCount = 0;
			fpsTicks = timer.GetElapsedTicks();
		}

		game.update();

		// �X���[���[�V�����E������Ή�
		if (timer.isTimeScaleMode && timer.timeScale > 0)
		{
			TargetFPS = (int)(60 / timer.timeScale);
			IntervalTicks = (long)(1.0 / TargetFPS * 10000000);
			MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
		}

		// �����������L���ȏꍇ
		if (GetWaitVSyncFlag() == TRUE && !timer.isTimeScaleMode)
		{
			if (EnableFrameSkip)
			{
				long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
				if (waitTicks < 0)
				{
					if (skipCount < MaxAllowSkipCount)
					{
						skipCount++;
					}
					else
					{
						nextFrameTicks = timer.GetElapsedTicks();
						GameDraw(game);
					}
				}
				else
				{
					GameDraw(game);
				}
				nextFrameTicks += IntervalTicks;
			}
			else
			{
				GameDraw(game);
			}
		}
		else
		{
			// ���������������ȏꍇ
			long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
			if (EnableFrameSkip && waitTicks < 0)
			{
				if (skipCount < MaxAllowSkipCount)
				{
					skipCount++;
				}
				else

				{
					nextFrameTicks = timer.GetElapsedTicks();
					GameDraw(game);
				}
			}
			else
			{
				if (waitTicks > 20000)
				{
					int waitMillsec = (int)(waitTicks / 10000) - 2;
					timer.SleepForMilliSec(waitMillsec);
				}
				while (timer.GetElapsedTicks() < nextFrameTicks) {}
				GameDraw(game);
			}
			nextFrameTicks += IntervalTicks;
		}
	}

#if _DEBUG
	// ImGui�I������
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImNodes::DestroyContext();
	ImGui::DestroyContext();
#endif

	WaitKey();
	DxLib::DxLib_End();
	return 0;
}
