/****************************************************************************
* Name: gseg_frame.h
* 
* JLP
* Version 17/08/2017
****************************************************************************/
#ifndef _gseg_frame__ 
#define _gseg_frame__ 

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/tglbtn.h"
#include "wx/bookctrl.h"
#include "wx/imaglist.h"
#include "wx/cshelp.h"

#if wxUSE_TOOLTIPS
    #include "wx/tooltip.h"
#endif

#include "jlp_wxlogbook.h"    // JLP_wxLogbook class
#include "jlp_wx_gpanel.h"    // JLP_wxGraphicPanel class

//----------------------------------------------------------------------
// class definitions
//----------------------------------------------------------------------

class GsegFrame: public wxFrame
{
public:
    GsegFrame(const wxChar *title, int x, int y);
    ~GsegFrame() {return;};

    void Gp_SetupMenu();
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);

    void SetText_to_StatusBar(wxString text, const int icol);

// In "gsegraf1_menu.cpp":
    void OnLoadPlotDataFromFile(wxCommandEvent& event);

// In "gseg_frame_menu.cpp":
    void OnSaveToPostscript(wxCommandEvent& event);
    void OnSaveToFile(wxCommandEvent& event);
    void OnViewLogbook(wxCommandEvent& event);
    void OnSaveLogbook(wxCommandEvent& event);
    void OnClearLogbook(wxCommandEvent& event);
    void OnCleanLogbook(wxCommandEvent& event);
    void OnViewChangeAxisLimits(wxCommandEvent& event);
    void OnViewAxisRotate(wxCommandEvent& event);
    void OnViewLabelContours(wxCommandEvent& event);
    void OnViewDisplayCoordinates(wxCommandEvent& event);

// in "gseg_logbook.cpp":
    int SaveLogbook(wxString save_filename);
    void ShowLogbook();
    void HideLogbook();
    void ClearLogbook();
    void CleanLogbook();
    int WriteToLogbook(wxString str1, bool SaveToFile);
    int AddNewPointToLogbook(double xx, double yy, double value);

#if wxUSE_TOOLTIPS
    void OnToggleTooltips(wxCommandEvent& event);
#endif // wxUSE_TOOLTIPS

    void OnContextHelp(wxCommandEvent& event);

private:
  void OnResize(wxSizeEvent &event);

  JLP_wxGraphicPanel *m_gpanel;

  int initialized;
  wxString    m_filename1, m_full_filename1;

// Menus:
  wxMenuBar *menu_bar;
  wxMenu *menuFile, *menuLog, *menuView;
  wxBoxSizer  *m_topsizer;
  wxStatusBar *m_StatusBar;
 
// Logbook:
  wxString    m_Logbook;
  JLP_wxLogbook *LogPanel;

  DECLARE_EVENT_TABLE()
};

#endif
