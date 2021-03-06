﻿// Copyright (c) Wiesław Šoltés. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "StdAfx.h"
#include "MainApp.h"
#include "..\utilities\Utilities.h"
#include "ProgressWorkerContext.h"

const TCHAR* pszWorkerContext[] = {
    /* 00 */ _T("Error"),
    /* 01 */ _T("Errors"),
    /* 02 */ _T("Processing item %d of %d (%d Done, %d %s)"),
    /* 03 */ _T("Processed %d of %d (%d Done, %d %s) in %s")
};

CProgressWorkerContext::CProgressWorkerContext(CConfiguration* pConfig, CMainDlg* pDlg)
    : CWorkerContext(pConfig)
{
    this->bDone = true;
    this->pDlg = pDlg;
}

CProgressWorkerContext::~CProgressWorkerContext()
{

}

void CProgressWorkerContext::Init()
{
    this->timer.Start();

    pDlg->m_Progress.SetPos(0);
}

void CProgressWorkerContext::Next(int nItemId)
{
    this->nProcessedFiles++;
    this->nErrors = (this->nProcessedFiles - 1) - this->nDoneWithoutError;

    if (this->nThreadCount == 1)
    {
        CString szText;
        szText.Format(this->GetString(0x00190003, pszWorkerContext[2]),
            this->nProcessedFiles,
            this->nTotalFiles,
            this->nDoneWithoutError,
            this->nErrors,
            ((this->nErrors == 0) || (this->nErrors > 1)) ? 
            this->GetString(0x00190002, pszWorkerContext[1]) : this->GetString(0x00190001, pszWorkerContext[0]));
        pDlg->m_StatusBar.SetText(szText, 1, 0);

        this->nLastItemId = nItemId;

        if (pDlg->m_Config.m_Options.bEnsureItemIsVisible == true)
            pDlg->m_LstInputItems.EnsureVisible(nItemId, FALSE);
    }
}

void CProgressWorkerContext::Done()
{
    this->timer.Stop();
    this->nErrors = this->nProcessedFiles - this->nDoneWithoutError;

    CString szText;
    szText.Format(this->GetString(0x00190004, pszWorkerContext[3]),
        this->nProcessedFiles,
        this->nTotalFiles,
        this->nDoneWithoutError,
        this->nErrors,
        ((this->nErrors == 0) || (this->nErrors > 1)) ?
        this->GetString(0x00190002, pszWorkerContext[1]) : this->GetString(0x00190001, pszWorkerContext[0]),
        this->timer.Format(this->timer.ElapsedTime(), 3));
    pDlg->m_StatusBar.SetText(szText, 1, 0);

    pDlg->FinishConvert();
}

bool CProgressWorkerContext::Callback(int nItemId, int nProgress, bool bFinished, bool bError)
{
    if (bError == true)
    {
        CItem &item = pConfig->m_Items.Get(nItemId);
        item.bFinished = true;

        if (pConfig->m_Options.bStopOnErrors == true)
        {
            pDlg->m_Progress.SetPos(0);
            this->bRunning = false;
        }

        return this->bRunning;
    }

    if (bFinished == true)
    {
        CItem &item = pConfig->m_Items.Get(nItemId);
        item.bFinished = true;
    }

    if ((bFinished == false) && (this->bRunning == true))
    {
        CItem &current = pConfig->m_Items.Get(nItemId);
        current.nProgress = nProgress;
        if (current.nPreviousProgress > nProgress)
            current.nPreviousProgress = nProgress;

        static volatile bool bSafeCheck = false;
        if (bSafeCheck == false)
        {
            bSafeCheck = true;

            if (nItemId > this->nLastItemId)
            {
                this->nLastItemId = nItemId;
                if (pDlg->m_Config.m_Options.bEnsureItemIsVisible == true)
                    pDlg->m_LstInputItems.EnsureVisible(nItemId, FALSE);
            }

            int nTotalProgress = 0;
            int nItems = pConfig->m_Items.Count();
            for (int i = 0; i < nItems; i++)
            {
                CItem &item = pConfig->m_Items.Get(i);
                if (item.bChecked == true)
                {
                    int nItemProgress = item.nProgress;
                    int nItemPreviousProgress = item.nPreviousProgress;

                    nTotalProgress += nItemProgress;

                    if (item.bFinished == false)
                    {
                        if (nItemProgress > 0 && nItemProgress < 100 && nItemProgress > nItemPreviousProgress)
                        {
                            CString szProgress;
                            szProgress.Format(_T("%d%%\0"), nItemProgress);
                            pDlg->m_LstInputItems.SetItemText(i, ITEM_COLUMN_STATUS, szProgress); // Status

                            item.nPreviousProgress = nItemProgress;
                        }
                        else if (nItemProgress == 100 && nItemProgress > nItemPreviousProgress)
                        {
                            item.nPreviousProgress = nItemProgress;
                        }
                    }
                }
            }

            int nPos = nTotalProgress / nTotalFiles;
            if (pDlg->m_Progress.GetPos() != nPos)
                pDlg->m_Progress.SetPos(nPos);

            bSafeCheck = false;
        }
    }

    return this->bRunning;
}

void CProgressWorkerContext::Status(int nItemId, CString szTime, CString szStatus)
{
    pDlg->m_LstInputItems.SetItemText(nItemId, ITEM_COLUMN_TIME, szTime); // Time
    pDlg->m_LstInputItems.SetItemText(nItemId, ITEM_COLUMN_STATUS, szStatus); // Status
};
