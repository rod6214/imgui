#include "Startup.h"
#include <memory>
#include <iostream>
#include "SDL_events.h"
#include "imgui.h"
#include "Window.h"

namespace POTYPROM
{
    int calculateNumRows(int option);

    void Start(AppArgs_t& args)
    {
        bool show_poty_prom = true;
        args.windows = new POTYPROM::CWindow(args.pWindow, show_poty_prom);
        auto secWindow = new POTYPROM::CPanel();
        static auto table = new POTYPROM::TablePanel();
        static auto combo = new POTYPROM::CComboBox({ "16", "32", "64", "128", "256", "512", "1024", "2048", "4096", "8192", "16384", "32768", "65536" }, "Size");
        auto textBox = new POTYPROM::CTextBox("0x0000", 45251, 10, "Start address");

        combo->AddChangedEventListener([](const void* sender, const ComboChangedEventArgs_t& args) {
            auto numRows = calculateNumRows(combo->GetSelectedOption());
            table->SetNumRows(numRows);
        });

        auto numRows = calculateNumRows(combo->GetSelectedOption());
        table->SetNumRows(numRows);
        args.windows->AddElement(table);
        table->AddElement(secWindow);
        secWindow->AddElement(combo);
        secWindow->AddElement(textBox);
    }

    int calculateNumRows(int option)
    {
        int options[] = { 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };
        return options[option] / 16;
    }

    //void ButtonPressedEvent(SDL_Event&, AppArgs_t& args)
    //{
    //    /*ButtonPressedEventArgs_t buttonPressedEvent;
    //    args.windows->OnButtonPressed(buttonPressedEvent);*/
    //}
}
