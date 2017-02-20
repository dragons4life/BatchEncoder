﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <afxstr.h>
#include "ListT.h"
#include "Language.h"

class CLanguagesList : public CListT<CLanguage>
{
public:
    int GetLanguageById(CString szLanguageId)
    {
        int nCount = this->GetSize();
        for (int i = 0; i < nCount; i++)
        {
            CLanguage& language = this->GetData(i);
            if (szLanguageId.CompareNoCase(language.szId) == 0)
                return i;
        }
        return -1;
    }
};
