﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "StdAfx.h"
#include "MainApp.h"
#include "..\language\LanguageHelper.h"
#include "..\utilities\Utilities.h"
#include "AboutDlg.h"

IMPLEMENT_DYNAMIC(CAboutDlg, CDialog)
CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CAboutDlg::IDD, pParent)
{

}

CAboutDlg::~CAboutDlg()
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDOK, m_BtnOK);
    DDX_Control(pDX, IDC_STATIC_TEXT_APP_NAME, m_StcMainAppName);
    DDX_Control(pDX, IDC_STATIC_TEXT_WEBSITE, m_StcWebsite);
    DDX_Control(pDX, IDC_STATIC_TEXT_EMAIL, m_StcEmail);
    DDX_Control(pDX, IDC_STATIC_LICENSE, m_StcLicense);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_StcMainAppName.SetBold(true);
    m_StcMainAppName.SetWindowText(_T(VER_PRODUCTNAME_STR " v" VER_FILE_VERSION_SHORT_STR " " VER_COPYRIGHT_STR));
    m_StcWebsite.SetWindowText(_T("https://github.com/wieslawsoltes/BatchEncoder"));
    m_StcWebsite.SetTargetUrl(_T("https://github.com/wieslawsoltes/BatchEncoder"));
    m_StcEmail.SetWindowText(_T("wieslaw.soltes@gmail.com"));
    m_StcEmail.SetTargetUrl(_T("mailto:wieslaw.soltes@gmail.com"));

    this->SetLanguage();

    return TRUE;
}

void CAboutDlg::OnOK()
{
    CDialog::OnOK();
}

void CAboutDlg::OnCancel()
{
    CDialog::OnCancel();
}

void CAboutDlg::OnClose()
{
    CDialog::OnClose();
}

void CAboutDlg::OnBnClickedOk()
{
    OnOK();
}

void CAboutDlg::SetLanguage()
{
    CLanguageHelper helper(pConfig);

    helper.SetWndText(this, 0x000D0010);
    helper.SetWndText(&m_BtnOK, 0x000D0011);
    helper.SetWndText(&m_StcLicense, 0x000D0012);
}
