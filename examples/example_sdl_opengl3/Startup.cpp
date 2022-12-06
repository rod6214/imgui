#include "Startup.h"
#include <memory>
#include <iostream>
#include "SDL_events.h"
#include "imgui.h"
#include "Window.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_internal.h"
namespace POTYPROM
{
    void Start(AppArgs_t& args)
    {
        bool show_poty_prom = true;
        args.windows = new POTYPROM::CWindow(args.pWindow, show_poty_prom);
        auto secWindow = new POTYPROM::CPanel();
        auto table = new POTYPROM::TablePanel();
        auto combo = new POTYPROM::CComboBox({ "OPTION1", "OPTION2" });
        //POTYPROM::CPanel secWindow;
        //POTYPROM::TablePanel table;
        //POTYPROM::CComboBox combo({ "OPTION1", "OPTION2" });

        table->SetNumRows(100);
        args.windows->AddElement(table);
        table->AddElement(secWindow);
        secWindow->AddElement(combo);
    }

    void ButtonPressedEvent(SDL_Event&, AppArgs_t& args)
    {
        /*ButtonPressedEventArgs_t buttonPressedEvent;
        args.windows->OnButtonPressed(buttonPressedEvent);*/
    }
}
