#include <stdio.h>
#include "application.h"

void POTYPROM::TablePanel::Show()
{
    //static ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY;
    //static ImGuiTableFlags flags = ImGuiTableFlags_RowBg;
    static int row_bg_type = 0;
    static int row_bg_target = 1;
    static int cell_bg_type = 1;
    static int total_columns = 16;

    IM_ASSERT(row_bg_type >= 0 && row_bg_type <= 2);
    IM_ASSERT(row_bg_target >= 0 && row_bg_target <= 1);
    IM_ASSERT(cell_bg_type >= 0 && cell_bg_type <= 1);

    if (ImGui::BeginTable("table1", total_columns))
    {
        for (int row = 0; row < 50; row++)
        {
            ImGui::TableNextRow();

            // Demonstrate setting a row background color with 'ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBgX, ...)'
            // We use a transparent color so we can see the one behind in case our target is RowBg1 and RowBg0 was already targeted by the ImGuiTableFlags_RowBg flag.
            if (row_bg_type != 0)
            {
                ImU32 row_bg_color = ImGui::GetColorU32(row_bg_type == 1 ? ImVec4(0.7f, 0.3f, 0.3f, 0.65f) : ImVec4(0.2f + row * 0.1f, 0.2f, 0.2f, 0.65f)); // Flat or Gradient?
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0 + row_bg_target, row_bg_color);
            }

            // Fill cells
            for (int column = 0; column < total_columns; column++)
            {
                ImGui::TableSetColumnIndex(column);
                //ImGui::Text("%c%c", 'A' + row, '0' + column);
                ImGui::Text("%c", 'A');

                // Change background of Cells B1->C2
                // Demonstrate setting a cell background color with 'ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ...)'
                // (the CellBg color will be blended over the RowBg and ColumnBg colors)
                // We can also pass a column number as a third parameter to TableSetBgColor() and do this outside the column loop.
                if (row >= 1 && row <= 2 && column >= 1 && column <= 2 && cell_bg_type == 1)
                {
                    ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
                }
            }
        }
        ImGui::EndTable();
    }
}
