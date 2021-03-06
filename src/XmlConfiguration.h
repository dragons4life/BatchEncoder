﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

#include <afxstr.h>
#include <afxtempl.h>
#include "XmlConfigurationBase.h"
#include "configuration\Options.h"
#include "configuration\PresetsList.h"
#include "configuration\Format.h"
#include "configuration\FormatsList.h"
#include "configuration\ItemsList.h"
#include "language\Language.h"
#include "language\LanguagesList.h"

class XmlConfiguration : private XmlConfigurationBase
{
public:
    XmlConfiguration();
    virtual ~XmlConfiguration();
private:
    void GetOptions(tinyxml2::XMLElement *pOptionsElem, COptions &m_Options);
    void SetOptions(tinyxml2::XMLElement *pOptionsElem, COptions &m_Options);
    void GetPresets(tinyxml2::XMLElement *pPresetsElem, CPresetsList &m_Presets);
    void SetPresets(tinyxml2::XMLElement *pPresetsElem, CPresetsList &m_Presets);
    void GetFormat(tinyxml2::XMLElement *pFormatElem, CFormat &m_Format);
    void SetFormat(tinyxml2::XMLElement *pFormatElem, CFormat &m_Format);
    void GetFormats(tinyxml2::XMLElement *pFormatsElem, CFormatsList &m_Formats);
    void SetFormats(tinyxml2::XMLElement *pFormatsElem, CFormatsList &m_Formats);
    void GetItems(tinyxml2::XMLElement *pItemsElem, CItemsList &m_Items);
    void SetItems(tinyxml2::XMLElement *pItemsElem, CItemsList &m_Items);
    void GetLanguage(tinyxml2::XMLElement *pLanguageElem, CLanguage &m_Language);
    void SetLanguage(tinyxml2::XMLElement *pLanguageElem, CLanguage &m_Language);
    void GetLanguages(tinyxml2::XMLElement *pLanguagesElem, CLanguagesList &m_Languages);
    void SetLanguages(tinyxml2::XMLElement *pLanguagesElem, CLanguagesList &m_Languages);
public:
    void GetOptions(COptions &m_Options);
    void SetOptions(COptions &m_Options);
    void GetPresets(CPresetsList &m_Presets);
    void SetPresets(CPresetsList &m_Presets);
    void GetFormat(CFormat &m_Format);
    void SetFormat(CFormat &m_Format);
    void GetFormats(CFormatsList &m_Formats);
    void SetFormats(CFormatsList &m_Formats);
    void GetItems(CItemsList &m_Items);
    void SetItems(CItemsList &m_Items);
    void GetLanguage(CLanguage &m_Language);
    void SetLanguage(CLanguage &m_Language);
    void GetLanguages(CLanguagesList &m_Languages);
    void SetLanguages(CLanguagesList &m_Languages);
    bool Open(CString szFileName);
    bool Save(CString szFileName);
};
