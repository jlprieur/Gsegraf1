/******************************************************************************
* Name:        gseg_frame_menu (GsegFrame class)
* Purpose:     handling menu events of GsegFrame class
*
* Author:      JLP 
* Version:     03/06/2015 
******************************************************************************/
#include "gseg_frame.h"
#include "gseg_frame_id.h"  // Menu identifiers

/* Declared in gseg_frame.h

void OnSaveToPostscript(wxCommandEvent &event);
void OnSaveToFile(wxCommandEvent &WXUNUSED(event));
void OnViewLogbook(wxCommandEvent& event);
void OnSaveLogbook(wxCommandEvent& WXUNUSED(event));
void OnClearLogbook(wxCommandEvent& event);
void OnCleanLogbook(wxCommandEvent& event);
void OnViewChangeAxisLimits(wxCommandEvent& WXUNUSED(event));
void OnViewAxisRotate(wxCommandEvent& WXUNUSED(event));
void OnViewLabelContours(wxCommandEvent& WXUNUSED(event));
void OnViewDisplayCoordinates(wxCommandEvent& WXUNUSED(event));

*/

/************************************************************************
* Output curve as a postscript file
************************************************************************/
void GsegFrame::OnSaveToPostscript(wxCommandEvent &WXUNUSED(event))
{
if(initialized != 1234) return;

if(m_gpanel != NULL) m_gpanel->wxGP_SaveGraphicToPostscriptFile();

return;
}
/************************************************************************
* Output curve as a JPEG, PNG, etc. file
************************************************************************/
void GsegFrame::OnSaveToFile(wxCommandEvent &WXUNUSED(event))
{
if(initialized != 1234) return;

if(m_gpanel != NULL) m_gpanel->wxGP_SaveGraphicToFile();

return;
}
/************************************************************************
* Showing/hiding logbook panel 
************************************************************************/
void GsegFrame::OnViewLogbook(wxCommandEvent& event)
{
  switch (event.GetId())
  {
   case ID_LOGBOOK_SHOW:
     ShowLogbook();
     break;
   case ID_LOGBOOK_HIDE:
     HideLogbook();
     break;
   }
}
/************************************************************************
* Save useful content of logbook to file 
************************************************************************/
void GsegFrame::OnSaveLogbook(wxCommandEvent& WXUNUSED(event))
{
wxString save_filename;

// Select name for output logbook file:
wxFileDialog
saveFileDialog(this, wxT("Save logbook to file"), wxT(""), wxT(""), 
               wxT("Logbook files (*.log;*.txt)|*.log;*.txt"), 
               wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

 if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

save_filename = saveFileDialog.GetFilename();

SaveLogbook(save_filename);

return;
}
/*******************************************************************
* Clear the logbook: erase all its content
********************************************************************/
void GsegFrame::OnClearLogbook(wxCommandEvent& event)
{
ClearLogbook();
return;
}
/*******************************************************************
* Clean the logbook: only keep its useful content
********************************************************************/
void GsegFrame::OnCleanLogbook(wxCommandEvent& event)
{
CleanLogbook();
}
/************************************************************************
* Change axis limits 
************************************************************************/
void GsegFrame::OnViewChangeAxisLimits(wxCommandEvent& WXUNUSED(event))
{
 if(m_gpanel != NULL) m_gpanel->wxGP_ViewChangeAxisLimits();
}
/************************************************************************
* Change axis projection of 3D plots 
************************************************************************/
void GsegFrame::OnViewAxisRotate(wxCommandEvent& WXUNUSED(event))
{
int status;

 if(m_gpanel != NULL) {
   status = m_gpanel->wxGP_ViewAxisRotate();
   if(status == -5) {
    wxMessageBox(wxT("Axis rotation is not available in this mode (only for 3D plots!)"),
                 wxT("GsegFrame::OnViewAxisRotate"), wxICON_ERROR);
    }
  }

return;
}
/************************************************************************
* Display labels with the value of some contours 
************************************************************************/
void GsegFrame::OnViewLabelContours(wxCommandEvent& WXUNUSED(event))
{
int status = -1;

 if(m_gpanel != NULL) {
   status = m_gpanel->wxGP_Set_ViewLabelContours();
   if(status == -5) {
    wxMessageBox(wxT("Labelling not available in this mode"),
                 wxT("GsegFrame::OnViewLabelContours"), wxICON_ERROR);
   }
 }
return;
}
/************************************************************************
* Switch on/off coordinate display on top of the image 
* By default, display the X/Y coordinates at the bottom of the graphic panel
************************************************************************/
void GsegFrame::OnViewDisplayCoordinates(wxCommandEvent& WXUNUSED(event))
{
int status = -1;

 if(m_gpanel != NULL) {
   status = m_gpanel->wxGP_Set_ViewDisplayCoordinates();
   if(status == -5) {
    wxMessageBox(wxT("ViewDisplayCoordinates not available in this mode"),
                 wxT("GsegFrame::OnViewDisplayCoordinates"), wxICON_ERROR);
   }
 }
}
