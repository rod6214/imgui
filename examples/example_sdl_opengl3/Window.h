#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "Events.h"
#include "tables.h"
#include <string>
#include <memory>

namespace POTYPROM
{
    typedef struct _FocusEventArgs
    {
        EventInfo_t info;
        FocusArgs_t args;
    } FocusEventArgs_t;

    typedef struct _EVENTARGS {} EventArgs_t;
    typedef struct _BUTTONRELEASEDEVENTARGS {} ButtonPressedEventArgs_t;
    typedef struct _BUTTONCLICKEVENTARGS {} ButtonClickEventArgs_t;
    typedef struct _COMBOCHANGEDEVENTARGS
    {
        int option;
    } ComboChangedEventArgs_t;
    typedef void (*EventListenerCallback)(const EventInfo_t&, const FocusArgs_t&);
    typedef void (*EventCallback)(const void* sender, const EventArgs_t* args);
    typedef void (*ButtonPressedEventCallback)(const void* sender, const ButtonPressedEventArgs_t& args);
    typedef void (*ButtonClickEventCallback)(const void* sender, const ButtonClickEventArgs_t& args);
    typedef void (*ComboChangedEventCallback)(const void* sender, const ComboChangedEventArgs_t& args);

    class BaseEvent
    {
    public:
        void dispatch(EventCallback*);
        void OnEvent();
    private:
        std::vector<EventCallback*> actions;
    };

    /*class ButtonReleasedEventArgs
    {};

    class ButtonReleasedEventArgs
    {};*/

    class BaseWindows : public Element
    {
    public:
        virtual void OnButtonPressed(ButtonPressedEventArgs_t&) = 0;
    };

    typedef struct _APPARGS
    {
        SDL_Window* pWindow;
        BaseWindows* windows;
    } AppArgs_t;

    class CWindow : public BaseWindows
    {
    public:
        CWindow(SDL_Window*& window, bool& p_open);
        void OnFocus(const EventInfo_t&, const FocusArgs_t&);
        void AddFocusEventListener(const EventListenerCallback&);
        void AddButtonPressedEventListener(const ButtonPressedEventCallback&);
        void AddButtonClickEventListener(const ButtonClickEventCallback&);
        virtual void Show() override;
        void AddElement(Element* el) override;
        void OnButtonPressed(ButtonPressedEventArgs_t&) override;
        bool& pOpen;
    private:
        std::vector<Element*> elements;
        std::vector<EventListenerCallback> focusListeners;
        std::vector<ButtonPressedEventCallback> buttonPressedListeners;
        std::vector<ButtonClickEventCallback> buttonClickListeners;
        SDL_Window*& parent;
        ImGuiID activeWindow;
        bool focused;
        FocusEventArgs_t focusEventArgs;
        bool isPressDown;
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
        CComboBox(std::vector<std::string> els, const char* label);
        ~CComboBox();
        int GetSelectedOption();
        virtual void Show() override;
        virtual void AddElement(Element* el) override;
        void AddChangedEventListener(const ComboChangedEventCallback);
    private:
        std::vector<std::string> elements;
        char* pElements;
        void getInitPointer();
        int selectedOption;
        const char* label;
        std::vector<ComboChangedEventCallback> changedEventListeners;
    };

    class CTextBox : public Element
    {
    public:
        CTextBox(std::string str, int id, int ml, const char* lbl);
        CTextBox(std::string str, ImGuiInputTextFlags flgs, int id, int ml, const char* lbl);
        ~CTextBox();
        void SetId(int id);
        virtual void Show() override;
        virtual void AddElement(Element* el) override;
    private:
        ImGuiInputTextFlags flags;
        int id;
        char* buffer;
        void moveToBuffer(std::string str);
        int bufferLength;
        int maxLength;
        const char* label;
    };
}
