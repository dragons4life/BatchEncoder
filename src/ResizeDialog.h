﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once

const CSize NOANCHOR(-1, -1);
const CSize TOP_LEFT(0, 0);
const CSize TOP_CENTER(50, 0);
const CSize TOP_RIGHT(100, 0);
const CSize MIDDLE_LEFT(0, 50);
const CSize MIDDLE_CENTER(50, 50);
const CSize MIDDLE_RIGHT(100, 50);
const CSize BOTTOM_LEFT(0, 100);
const CSize BOTTOM_CENTER(50, 100);
const CSize BOTTOM_RIGHT(100, 100);

class CResizeDialog : public CDialog
{
private:
    class Layout
    {
    public:
        HWND hwnd;
        BOOL adj_hscroll;
        BOOL need_refresh;
        SIZE tl_type;
        SIZE tl_margin;
        SIZE br_type;
        SIZE br_margin;
    public:
        Layout(HWND hw,
            SIZE tl_t, SIZE tl_m,
            SIZE br_t, SIZE br_m,
            BOOL hscroll,
            BOOL refresh)
        {
            hwnd = hw;
            adj_hscroll = hscroll;
            need_refresh = refresh;
            tl_type = tl_t;
            tl_margin = tl_m;
            br_type = br_t;
            br_margin = br_m;
        };
    };
public:
    CResizeDialog();
    CResizeDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
    CResizeDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
    virtual ~CResizeDialog();
private:
    BOOL m_bShowGrip;
    BOOL m_bUseMaxTrack;
    BOOL m_bUseMinTrack;
    BOOL m_bUseMaxRect;
public:
    CString m_sSection;
    CString m_sEntry;
public:
    BOOL m_bInitDone;
public:
    SIZE m_szGripSize;
public:
    CRect m_rcGripRect;
public:
    POINT m_ptMinTrackSize;
    POINT m_ptMaxTrackSize;
    POINT m_ptMaxPos;
    POINT m_ptMaxSize;
public:
    CPtrList m_plLayoutList;
private:
    void InitVars();
public:
    void ArrangeLayout();
public:
    void UpdateGripPos();
public:
    void AddAnchor(HWND wnd, CSize tl_type, CSize br_type = NOANCHOR);
    void AddAnchor(UINT ctrl_ID, CSize tl_type, CSize br_type = NOANCHOR)
    {
        AddAnchor(::GetDlgItem(*this, ctrl_ID), tl_type, br_type);
    };
public:
    void ShowSizeGrip(BOOL bShow);
public:
    void SetMaximizedRect(const CRect& rc);
    void ResetMaximizedRect();
public:
    void SetMinTrackSize(const CSize& size);
    void ResetMinTrackSize();
public:
    void SetMaxTrackSize(const CSize& size);
    void ResetMaxTrackSize();
public:
    CString GetWindowRectStr();
    void SetWindowRectStr(CString data);
protected:
    virtual BOOL OnInitDialog();
protected:
    afx_msg UINT OnNcHitTest(CPoint point);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnDestroy();
    afx_msg void OnPaint();
protected:
    DECLARE_MESSAGE_MAP()
};
