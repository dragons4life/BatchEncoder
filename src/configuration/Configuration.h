﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include "Options.h"
#include "FormatsList.h"
#include "ItemsList.h"

class CConfiguration
{
public:
    COptions m_Options;
    CFormatsList m_Formats;
    CItemsList m_Items;
public:
    CConfiguration()
    {
    }
    CConfiguration(const CConfiguration &other)
    {
        Copy(other);
    }
    CConfiguration& operator=(const CConfiguration &other)
    {
        Copy(other);
        return *this;
    }
    virtual ~CConfiguration()
    {
    }
public:
    void Copy(const CConfiguration &other)
    {
        this->m_Options = other.m_Options;
        this->m_Formats = other.m_Formats;
        this->m_Items = other.m_Items;
    }
};
