/******************************************************************************
* Name:        gsegraf1_menu (GsegFrame class)
* Purpose:     handling menu events of Gsegraf1.cpp
*
* Author:      JLP 
* Version:     20/02/2019
******************************************************************************/
#include "gseg_frame.h"
#include "gseg_frame_id.h"

/************************************************************************
* Input ascii file with curves
* Read the file containing plot data and load it to graphic panel (wxGP):
*************************************************************************/
void GsegFrame::OnLoadPlotDataFromFile( wxCommandEvent& event )
{
wxString str1, path, extension, fname, err_msg;
int status;

 switch(event.GetId()) {
   case ID_LOAD_GSEG_PARAM_FILE :
     status = m_gpanel->wxGP_SelectAndLoadGsegParamFile(m_full_filename1, 
                                                        err_msg);
     break;
   case ID_LOAD_GDEV_PARAM_FILE :
     status = m_gpanel->wxGP_SelectAndLoadGdevParamFile(m_full_filename1, 
                                                        err_msg);
     break;
// Input ascii file with X,Y curve
   default:
   case ID_LOAD_CURVE_FOR_PLOT :
     status = m_gpanel->wxGP_SelectAndLoadCurveFromFile(m_full_filename1,
                                                        err_msg);
     break;
// Input an image FITS file
   case ID_LOAD_IMAGE_FOR_PLOT :
     status = m_gpanel->wxGP_SelectAndLoadFitsImage(m_full_filename1,
                                                        err_msg);
     break;
  }

if(status == 0) { 

// Removes the directory name (since the full path is generally too long...)
  wxFileName::SplitPath(m_full_filename1, &path, &fname, &extension);
  m_filename1 = fname + _T(".") + extension;

// Logbook:
  LogPanel->Clear();

  str1 = _T("%%\n%% Input file: ") + m_filename1 + _T("\n");
  WriteToLogbook(str1, true);
 } else {
  WriteToLogbook(err_msg, true);
 }

return;
}
