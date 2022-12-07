#pragma once
#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__
#include <type_traits>
#include <iostream>
#include "imgui_impl_sdl.h"
#include "imgui_internal.h"
#include "Window.h"

namespace POTYPROM
{
    CWindow::CWindow(SDL_Window*& window, bool& p_open)
        : pOpen(p_open), parent(window), activeWindow((ImGuiID)-1), focused(false), isPressDown(false)
    {
        /*AddFocusEventListener([](const EventInfo_t& info, const FocusArgs_t&) {
            std::cout << "Window id: " << info.windowID << std::endl;
        });*/

        /*AddButtonPressedEventListener([](const void* sender, const ButtonPressedEventArgs_t& args) {
            std::cout << "Pressed" << std::endl;
        });*/

        /*AddButtonClickEventListener([](const void* sender, const ButtonClickEventArgs_t& args) {
            std::cout << "Click" << std::endl;
        });*/
    }

    void CWindow::AddElement(Element* pEl)
    {
        elements.push_back(pEl);
    }

    void CWindow::Show()
    {
        if (pOpen)
        {
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

                if (show_another_window)
                {
                    if (ImGui::Begin("MainPanel", &show_another_window))
                    {
                        activeWindow = ImGui::GetID("MainPanel");
                        auto dd = ImGui::GetCurrentWindow();
                        auto activeId = ImGui::GetActiveID();

                        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
                        {
                            int pressedEvents = static_cast<int>(buttonPressedListeners.size());
                            for (int i = 0; i < pressedEvents; i++)
                            {
                                ButtonPressedEventArgs_t args;
                                buttonPressedListeners[i](NULL, args);
                            }

                            if (!isPressDown)
                            {
                                int clickEvents = static_cast<int>(buttonClickListeners.size());
                                for (int i = 0; i < clickEvents; i++)
                                {
                                    ButtonClickEventArgs_t args;
                                    buttonClickListeners[i](NULL, args);
                                }
                                isPressDown = true;
                            }
                        }

                        if (isPressDown && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
                        {
                            isPressDown = false;
                        }

                        size_t len = elements.size();

                        for (int i = 0; i < len; i++)
                        {
                            elements[i]->Show();
                        }
                        //ImGui::Text("This is a child window!");
                        ImGui::End();
                    }
                }
                
                if (pOpen && ImGui::Button("Close this window"))
                    pOpen = false;
                
            }
            ImGui::End();
        }
    }

    void CWindow::OnFocus(const EventInfo_t& info, const FocusArgs_t& args)
    {
        focusEventArgs.info = info;
        focusEventArgs.args = args;
        focused = true;
    }

    void CWindow::AddFocusEventListener(const EventListenerCallback& listener)
    {
        focusListeners.push_back(listener);
    }

    void CWindow::AddButtonPressedEventListener(const ButtonPressedEventCallback& listener)
    {
        this->buttonPressedListeners.push_back(listener);
    }

    void CWindow::AddButtonClickEventListener(const ButtonClickEventCallback& listener)
    {
        this->buttonClickListeners.push_back(listener);
    }

    void CWindow::OnButtonPressed(ButtonPressedEventArgs_t& args)
    {
        int len = static_cast<int>(buttonPressedListeners.size());
        for (int i = 0; i < len; i++)
        {
            buttonPressedListeners[i](this, args);
        }
    }

    void CPanel::AddElement(Element* el)
    {
        elements.push_back(el);
    }

    void CPanel::Show()
    {
        static bool show_another_window = true;
        if (show_another_window)
        {
            ImGui::Begin("Internal Test", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            int len = static_cast<int>(elements.size());
            for (int i = 0; i < len; i++)
            {
                elements[i]->Show();
            }
            ImGui::End();
        }
    }

    CComboBox::CComboBox(std::vector<std::string> els, const char* lbl)
        : elements(els), pElements(NULL), selectedOption(0), label(lbl)
    {
        getInitPointer();
    }

    CComboBox::~CComboBox()
    {
        delete pElements;
    }

    int CComboBox::GetSelectedOption()
    {
        return selectedOption;
    }

    void CComboBox::Show()
    {
        static int currentOption = selectedOption;
        int len = static_cast<int>(elements.size());
        ImGui::Combo(label, &selectedOption, pElements, len);
        if (currentOption != selectedOption)
        {
            currentOption = selectedOption;
            len = static_cast<int>(this->changedEventListeners.size());
            for (int i = 0; i < len; i++)
            {
                ComboChangedEventArgs_t args = { currentOption };
                changedEventListeners[i](NULL, args);
            }
        }
    }
    
    void CComboBox::getInitPointer()
    {
        int lx = static_cast<int>(elements.size());
        int ly = 0;

        for (int i = 0; i < lx; i++)
        {
            auto option = elements[i];
            ly += static_cast<int>(option.size()) + 2;
        }

        ly += 4;

        pElements = new char[ly];
        char* ptr = pElements;

        for (int i = 0; i < lx; i++)
        {
            auto option = elements[i];
            ly = static_cast<int>(option.size());
            auto src = option.data();

            for (int j = 0; j < ly; j++)
            {
                *(ptr++) = src[j];
            }
            *ptr++ = '\0';
        }

        *ptr++ = '\0';
        *ptr++ = '\0';
        *ptr++ = '\0';
        *ptr++ = '\0';
    }

    void CComboBox::AddChangedEventListener(const ComboChangedEventCallback callback)
    {
        changedEventListeners.push_back(callback);
    }

    void CComboBox::AddElement(Element*) {}

    void BaseEvent::dispatch(EventCallback* callback)
    {
        actions.push_back(callback);
    }

    void BaseEvent::OnEvent()
    {
        int len = static_cast<int>(actions.size());
        for (int i = 0; i < len; i++)
        {
        }
    }

    CTextBox::CTextBox(std::string str, int _id, int ml, const char* lbl):
        flags(ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase),
        id(_id),
        bufferLength(0),
        maxLength(ml),
        label(lbl)
    {
        moveToBuffer(str);
    }

    CTextBox::CTextBox(std::string str, ImGuiInputTextFlags flgs, int _id, int ml, const char* lbl)
        :flags(flgs),
        id(_id),
        bufferLength(0),
        maxLength(ml),
        label(lbl)
    {
        moveToBuffer(str);
    }

    CTextBox::~CTextBox()
    {
        delete buffer;
    }

    void CTextBox::moveToBuffer(std::string str)
    {
        auto src = str.data();
        auto len = static_cast<int>(str.size());
        bufferLength = len;
        buffer = new char[256];
        char* ptr = buffer;
        for (int i = 0; i < len; i++)
        {
            *(ptr++) = src[i];
        }
        *ptr = '\0';
    }

    void CTextBox::SetId(int id)
    {
        this->id = id;
    }

    void CTextBox::Show()
    {
        auto len = maxLength + 1;
        ImGui::PushID(id);
        ImGui::InputText(label, buffer, len, flags);
        ImGui::PopID();
    }

    void CTextBox::AddElement(Element* el) {}
}
#endif
