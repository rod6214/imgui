#include <stdio.h>
#include "tables.h"
#include "imgui.h"

POTYPROM::TablePanel::TablePanel() : rows(1) {}

void POTYPROM::TablePanel::AddElement(POTYPROM::Element* el)
{
    elements.push_back(el);
}

void POTYPROM::TablePanel::SetNumRows(int value)
{
    rows = value;
}

int POTYPROM::TablePanel::GetNumRows()
{
    return rows;
}

void POTYPROM::TablePanel::Show()
{
    static int row_bg_type = 0;
    static int row_bg_target = 1;
    static int cell_bg_type = 1;
    static int total_columns = 16;

    IM_ASSERT(row_bg_type >= 0 && row_bg_type <= 2);
    IM_ASSERT(row_bg_target >= 0 && row_bg_target <= 1);
    IM_ASSERT(cell_bg_type >= 0 && cell_bg_type <= 1);

    if (ImGui::BeginTable("table1", total_columns))
    {
        for (int row = 0; row < rows; row++)
        {
            ImGui::TableNextRow();

            // Fill cells
            for (int column = 0; column < 16; column++)
            {
                ImGui::TableSetColumnIndex(column);
                int n = 16*row + column;
                items.push_back({ n, "00"});
                ImGui::PushID(n);
                ImGui::InputText("", items[n].buffer, IM_ARRAYSIZE(items[n].buffer), ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
                ImGui::PopID();
            }
        }

        size_t len = elements.size();

        for (int i = 0; i < len; i++)
        {
            elements[i]->Show();
        }
       
        ImGui::EndTable();
    }
}
