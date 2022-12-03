#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "Events.h"
#include "tables.h"
#include <string>

namespace POTYPROM
{
    typedef void (*EventListenerCallback)(const EventInfo_t&, const FocusArgs_t&);

    typedef struct _FocusEventArgs
    {
        EventInfo_t info;
        FocusArgs_t args;
    } FocusEventArgs_t;

    class CWindow : public Element
    {
    public:
        CWindow(SDL_Window*& window, bool& p_open);
        void OnFocus(const EventInfo_t&, const FocusArgs_t&);
        void AddFocusEventListener(const EventListenerCallback&);
        virtual void Show() override;
        virtual void AddElement(Element* el) override;
        bool& pOpen;
    private:
        std::vector<Element*> elements;
        std::vector<EventListenerCallback> focusListeners;
        SDL_Window*& parent;
        ImGuiID activeWindow;
        bool focused;
        FocusEventArgs_t focusEventArgs;
    };

    class CPanel : public Element
    {
    public:
        virtual void Show() override;
        virtual void AddElement(Element* el) override;
    private:
        std::vector<Element*> elements;
    };

    class CComboBox : public Element
    {
    public:
        CComboBox(std::vector<std::string> els);
        ~CComboBox();
        int GetSelectedOption();
        virtual void Show() override;
        virtual void AddElement(Element* el) override;
    private:
        std::vector<std::string> elements;
        char* pElements;
        void getInitPointer();
        int selectedOption;
    };
}
