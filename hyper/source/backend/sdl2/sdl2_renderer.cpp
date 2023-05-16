#include "sdl2_renderer.h"

#include "hyper/core/window.h"

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer.h>

#include <stdexcept>

namespace hyper
{
	Renderer::Impl::Impl(const Window& window)
	{
		auto pWindow = reinterpret_cast<SDL_Window*>(window.GetNativeWindow());

		m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (m_pRenderer == nullptr)
		{
			throw std::runtime_error("Failed to create SDL2 renderer");
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForSDLRenderer(pWindow, m_pRenderer);
		ImGui_ImplSDLRenderer_Init(m_pRenderer);
	}

	Renderer::Impl::~Impl()
	{
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_DestroyRenderer(m_pRenderer);
	}

	void Renderer::Impl::BeginFrame()
	{
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(m_pRenderer);

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void Renderer::Impl::EndFrame()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Render();
		SDL_RenderSetScale(m_pRenderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(m_pRenderer);
	}
}
