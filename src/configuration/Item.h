﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <afxstr.h>

class CItem
{
public:
    int nId;
    CString szPath;
    CString szSize;
    CString szName;
    CString szExtension;
    CString szFormatId;
    int nPreset;
    bool bChecked;
    CString szTime;
    CString szStatus;
    bool bFinished;
    int nProgress;
    int nPreviousProgress;
public:
    CItem()
    {
    }
    CItem(const CItem &other)
    {
        Copy(other);
    }
    CItem& operator=(const CItem &other)
    {
        Copy(other);
        return *this;
    }
    virtual ~CItem()
    {
    }
public:
    void Copy(const CItem &other)
    {
        this->nId = other.nId;
        this->szPath = other.szPath;
        this->szSize = other.szSize;
        this->szName = other.szName;
        this->szExtension = other.szExtension;
        this->szFormatId = other.szFormatId;
        this->nPreset = other.nPreset;
        this->bChecked = other.bChecked;
        this->szTime = other.szTime;
        this->szStatus = other.szStatus;
        this->bFinished = other.bFinished;
        this->nProgress = other.nProgress;
        this->nPreviousProgress = other.nPreviousProgress;
    }
public:
    void ResetProgress()
    {
        this->bFinished = false;
        this->nProgress = 0;
        this->nPreviousProgress = 0;
    }
};
