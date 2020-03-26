/******************************************************************************
* Name:        gseg_frame_logbook.cpp (GsegFrame class)
* same as  "pisco/Gdpisco/gseg_frame_logbook.cpp" (GdpFrame class)
*          but without "int BinariesSaveMeasurements();"
*
* Purpose:     Logbook utilities 
* Author:      JLP 
* Version:     03/06/2015 
******************************************************************************/
#include "gseg_frame.h"
#include "gseg_frame_id.h"  // Menu identifiers

/*
int  SaveLogbook(wxString save_filename)
void ShowLogbook()
void HideLogbook()
void ClearLogbook()
void CleanLogbook()
int  WriteToLogbook(wxString str1, bool SaveToFile);
int  AddNewPointToLogbook(int xx, int yy)
*/

/************************************************************************
* Save useful content of logbook to file 
* Input:
* save_filename: wxString whose value is set in gdp_frame_menu.cpp
************************************************************************/
int GsegFrame::SaveLogbook(wxString save_filename)
{
int status = -2;

 if(initialized == 1234) status = LogPanel->SaveLogbook(save_filename);

return(status);
}
/************************************************************************
* Showing logbook panel 
************************************************************************/
void GsegFrame::ShowLogbook()
{
 if(initialized != 1234) return;

 m_topsizer->Show(LogPanel);
 m_topsizer->Layout();
}
/************************************************************************
* Hiding logbook panel 
************************************************************************/
void GsegFrame::HideLogbook()
{
 if(initialized != 1234) return;

 m_topsizer->Hide(LogPanel);
 m_topsizer->Layout();
}
/*******************************************************************
* Clear the logbook: erase all its content
********************************************************************/
void GsegFrame::ClearLogbook()
{
wxString str1;

 if(initialized != 1234) return;

 LogPanel->Clear();

// Rewrite the filename at the beginning, since this is essential: 
 str1 = _T("%%\n%% Input file: ") + m_filename1 + _T("\n");
 WriteToLogbook(str1, true);

return;
}
/*******************************************************************
* Clean the logbook: only keep its useful content
********************************************************************/
void GsegFrame::CleanLogbook()
{
 if(initialized != 1234) return;
 LogPanel->Clean();
}
/************************************************************************
* Write to logbook 
*************************************************************************/
int  GsegFrame::WriteToLogbook(wxString str1, bool SaveToFile)
{
int status = -1;

 if(initialized == 1234) status = LogPanel->WriteToLogbook(str1, SaveToFile);

return(status);
}
/************************************************************************
* Add a new point to logbook 
*************************************************************************/
int GsegFrame::AddNewPointToLogbook(double xx, double yy, double value)
{
int status = -1;
wxString str1;

 if(initialized == 1234) { 
  str1.Printf("%.2f %.2f %.4g\n", xx, yy, value);
  status = LogPanel->WriteToLogbook(str1, true);
  }

return(status);
}
