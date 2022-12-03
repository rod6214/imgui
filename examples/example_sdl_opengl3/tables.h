#pragma once
#ifndef __TABLES_H__
#define __TABLES_H__
#include "Bases.h"
#include <vector>
namespace POTYPROM
{
    struct TableItemData
    {
        int ID;
        char buffer[3];
    };

    class TablePanel : public Element
    {
    public:
        TablePanel();
        void SetNumRows(int value);
        int GetNumRows();
        void Show() override;
        virtual void AddElement(Element* el) override;
    private:
        std::vector<TableItemData> items;
        std::vector<Element*> elements;
        int rows;
    };
}
#endif
