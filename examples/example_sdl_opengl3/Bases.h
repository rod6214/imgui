#pragma once
#ifndef __BASES_H__
#define __BASES_H__
#include "application.h"
namespace POTYPROM
{
    class Element
    {
    public:
        virtual void Show() = 0;
        virtual void AddElement(Element* el) = 0;
    };
}
#endif
