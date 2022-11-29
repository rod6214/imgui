#pragma once
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "application.h"
#include "Events.h"
#include <type_traits>
#include <iostream>
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"
#include "Window.h"

namespace POTYPROM
{
    /*template<typename T>*/
    

    //template<typename T>
    CWindow::CWindow(SDL_Window*& window, bool& p_open)
        : pOpen(p_open), parent(window), activeWindow((ImGuiID)-1), focused(false)
    {
        //static_assert(std::is_base_of<Element, T>::value, "Type of class must be based on Element type.");

        AddFocusEventListener([](const EventInfo_t& info, const FocusArgs_t&) {
            std::cout << "Window id: " << info.windowID << std::endl;
        });
    }

    //template<typename T>
    void CWindow::AddElement(Element* pEl)
    {
        elements.push_back(pEl);
    }

    //template<typename T>
    void CWindow::Show()
    {
        if (pOpen)
        {
            if (ImGui::IsWindowFocused())
            {
                std::cout << "Test" << std::endl;
            }
            static ImGuiWindowFlags sec_flags = ImGuiWindowFlags_Modal;
            static bool use_work_area = true;
            static bool show_another_window = true;
            static ImGuiWindowFlags flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
            ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
            
            if (ImGui::Begin("Example: Fullscreen window", &pOpen, flags))
            {
                ImVec2 vec = viewport->WorkSize;
                vec.x = vec.x / 2;

                if (ImGui::Begin("MainPanel", &show_another_window, sec_flags))
                {
                    auto activeId = ImGui::GetActiveID();

                    if (activeId != activeWindow && activeId != 0 && focused)
                    {
                        size_t len = focusListeners.size();
                        for (int i = 0; i < len; i++)
                        {
                            focusEventArgs.info.windowID = activeId;
                            focusListeners[i](focusEventArgs.info, focusEventArgs.args);
                        }
                        activeWindow = activeId;
                        focused = false;
                    }
                    
                    size_t len = elements.size();
                    
                    for (int i = 0; i < len; i++)
                    {
                        elements[i]->Show();
                    }
                    ImGui::Text("This is a child window!");
                    ImGui::End();
                }
                
                if (pOpen && ImGui::Button("Close this window"))
                    pOpen = false;
                
            }
            ImGui::End();
        }
    }

    //template<typename T>
    void CWindow::OnFocus(const EventInfo_t& info, const FocusArgs_t& args)
    {
        focusEventArgs.info = info;
        focusEventArgs.args = args;
        focused = true;
    }

    //template<typename T>
    void CWindow::AddFocusEventListener(const EventListenerCallback& listener)
    {
        focusListeners.push_back(listener);
    }

    void CPanel::AddElement(Element* el)
    {
        elements.push_back(el);
    }

    void CPanel::Show()
    {
        static bool show_another_window = true;
        ImGui::Begin("Internal Test", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}
#endif
