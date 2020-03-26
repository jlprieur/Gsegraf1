/****************************************************************************
* Name: Gsegraf1.cpp
* From Gdisp1.cpp and then Gplot1.cpp (version 19/08/2013)
* 
* JLP
* Version 19/02/2019
****************************************************************************/
#include <stdlib.h>   // exit() 
#include "time.h"

// JLP routines:
#include "gseg_frame.h"
#include "jlp_wx_gpanel.h"

#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    #define USE_XPM
#endif

#ifdef USE_XPM
    #include "mondrian.xpm"
#endif

#include "wx/progdlg.h"


#if !wxUSE_TOGGLEBTN
    #define wxToggleButton wxCheckBox
    #define EVT_TOGGLEBUTTON EVT_CHECKBOX
#endif

// static JLP_wxGraphicPanel *m_gpanel;

#include "gseg_frame_id.h"  // My ID numbers (ID_xxx)

BEGIN_EVENT_TABLE(GsegFrame, wxFrame)

// File:
   EVT_MENU(ID_SAVE_TO_PST,     GsegFrame::OnSaveToPostscript)
   EVT_MENU(ID_SAVE_TO_FILE,    GsegFrame::OnSaveToFile)
   EVT_MENU(ID_LOAD_GSEG_PARAM_FILE, GsegFrame::OnLoadPlotDataFromFile)
   EVT_MENU(ID_LOAD_GDEV_PARAM_FILE, GsegFrame::OnLoadPlotDataFromFile)
   EVT_MENU(ID_LOAD_CURVE_FOR_PLOT, GsegFrame::OnLoadPlotDataFromFile)
   EVT_MENU(ID_LOAD_IMAGE_FOR_PLOT, GsegFrame::OnLoadPlotDataFromFile)
   EVT_MENU(ID_QUIT,            GsegFrame::OnQuit)

// View menu
   EVT_MENU(ID_VIEW_AXIS_LIMITS, GsegFrame::OnViewChangeAxisLimits)
   EVT_MENU(ID_VIEW_AXIS_ROTATE, GsegFrame::OnViewAxisRotate)
   EVT_MENU(ID_VIEW_LABEL_CONTOURS, GsegFrame::OnViewLabelContours)
   EVT_MENU(ID_VIEW_DISPLAY_COORD, GsegFrame::OnViewDisplayCoordinates)
   
// Logbook (from menu):
   EVT_MENU(ID_LOGBOOK_SHOW, GsegFrame::OnViewLogbook)
   EVT_MENU(ID_LOGBOOK_HIDE, GsegFrame::OnViewLogbook)
   EVT_MENU(ID_LOGBOOK_CLEAN, GsegFrame::OnCleanLogbook)
   EVT_MENU(ID_LOGBOOK_CLEAR, GsegFrame::OnClearLogbook)
   EVT_MENU(ID_LOGBOOK_SAVE, GsegFrame::OnSaveLogbook)

// Miscellaneous:
   EVT_MENU(ID_CONTEXT_HELP,   GsegFrame::OnContextHelp)
   EVT_MENU(ID_ABOUT,          GsegFrame::OnAbout)
   EVT_MENU(ID_HELP,           GsegFrame::OnHelp)

END_EVENT_TABLE()

//----------------------------------------------------------------------
// MyApp
//----------------------------------------------------------------------

class MyApp: public wxApp
{
public:
   bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
// Transform coma into point for numbers:
setlocale(LC_NUMERIC, "C");

    // use standard command line handling:
    if ( !wxApp::OnInit() )
        return false;

    // parse the cmd line
    int iwidth = 800, iheight = 500;
    if ( argc == 3 )
    {
        wxSscanf(wxString(argv[1]), wxT("%d"), &iwidth);
        wxSscanf(wxString(argv[2]), wxT("%d"), &iheight);
    }

#if wxUSE_HELP
    wxHelpProvider::Set( new wxSimpleHelpProvider );
#endif // wxUSE_HELP

// Create the main frame window
    GsegFrame *main_frame1 = new GsegFrame(_T("Gsegraf1"), iwidth, iheight);

// Give it an icon
// The wxICON() macros loads an icon from a resource under Windows
// and uses an #included XPM image under GTK+ and Motif

#ifdef USE_XPM
    main_frame1->SetIcon( wxICON(mondrian) );
#endif

    main_frame1->Show(true);

    return true;
}

/**********************************************************************
* GsegFrame constructor
* logbook panel (JLP_Logbook) + graphic panel (JLP_wxGraphicPanel)
*
* INPUT:
*   iwidth, iheight : size of created window
*
***********************************************************************/
GsegFrame::GsegFrame(const wxChar *title, int iwidth, int iheight)
       : wxFrame(NULL, wxID_ANY, title, wxPoint(-1, -1), wxSize(iwidth, iheight))
{
int iwidth1, iheight1;
wxSize m_size1;
wxString str1;

// Status bar:
// Create a status bar with two fields at the bottom:
  m_StatusBar = CreateStatusBar(2);
// First field has a variable length, second has a fixed length:
  int widths[2];
  widths[0] = -1;
  widths[1] = 140;
  SetStatusWidths( 2, widths );

//
  m_size1 = this->GetClientSize();
printf("GsegFrame/Size: width=%d height=%d iwidth=%d iheight=%d\n", m_size1.x,
       m_size1.y, iwidth, iheight);
 m_size1.x -= 20;
 m_size1.y -= 20;

// Create topsizer to locate panels and log window
  m_topsizer = new wxBoxSizer( wxVERTICAL );

// Create Logbook first:
  str1 = wxString("");
  iwidth1 = m_size1.x;
  iheight1 = m_size1.y / 6;
  LogPanel = new JLP_wxLogbook(this, str1, iwidth1, iheight1);

  wxLog::SetActiveTarget(new wxLogTextCtrl(LogPanel));

// Then create the gseg_graphic panel:
  iwidth = m_size1.x;
  iheight = (m_size1.y * 5 )/ 6;
  m_gpanel = new JLP_wxGraphicPanel(this, wxID_ANY, 
                                    LogPanel, 20, 20, iwidth, iheight);

  SetSizer(m_topsizer);
// The initial size of m_scrolled1 is interpreted as the minimal size:
// 1 : make vertically stretchable
// wxEXPAND : make horizontally stretchable, and the item will be expanded
// to fill the space assigned to the item.
// Proportion set to 5, i.e., log window will be 1/6 of the image
  m_topsizer->Add(m_gpanel, 5, wxEXPAND | wxALL);

// Proportion set to 1, i.e., log window will be 1/6 of the image
  m_topsizer->Add( LogPanel, 1, wxEXPAND );

/// SetSizerAndFit(m_topsizer);

// Create a menu on top of the window:
  Gp_SetupMenu();

initialized = 1234;

return;
}
/********************************************************************
* Setup the menu on top of main frame
********************************************************************/
void GsegFrame::Gp_SetupMenu()
{
SetHelpText( _T("Program to plot curves from data contained in ASCII files") );

  menu_bar = new wxMenuBar;

// ***************** File menu **********************************
  wxMenu *file_menu = new wxMenu;

  file_menu->Append(ID_LOAD_GSEG_PARAM_FILE, 
                    _T("Open a gsegraf parameter file"), _T("Ascii file width plot commands"));
  file_menu->Append(ID_LOAD_GDEV_PARAM_FILE, 
                    _T("Open a gdev parameter file"), _T("Ascii file width plot commands"));
  file_menu->Append(ID_LOAD_CURVE_FOR_PLOT, _T("Open a X,Y curve in a file"),
                    _T("Ascii file (possibility of multicolumns)"));
  file_menu->Append(ID_LOAD_IMAGE_FOR_PLOT, _T("Open an image in FITS file)"),
                    _T("FITS file"));
  file_menu->AppendSeparator();
  file_menu->Append( ID_SAVE_TO_FILE, _T("Save to jpeg, png,... file"),
                    _T("Save to bmp, jpg, png, pcx, pnm, tiff, xpm, ico, cur"));
  file_menu->Append( ID_SAVE_TO_PST, _T("Save to postscript file"),
                    _T("Postscript file"));
  file_menu->AppendSeparator();

  file_menu->Append(ID_QUIT, _T("E&xit\tAlt-X"), _T("Quit controls sample"));
  menu_bar->Append(file_menu, _T("&File"));

// View menu
   EVT_MENU(ID_VIEW_AXIS_LIMITS, GsegFrame::OnViewChangeAxisLimits)
   EVT_MENU(ID_VIEW_AXIS_ROTATE, GsegFrame::OnViewAxisRotate)
   EVT_MENU(ID_VIEW_LABEL_CONTOURS, GsegFrame::OnViewLabelContours)
   EVT_MENU(ID_VIEW_DISPLAY_COORD, GsegFrame::OnViewDisplayCoordinates)

// ***************** View menu ******************************
  menuView = new wxMenu;
  menuView->Append(ID_VIEW_AXIS_LIMITS, _T("Change axis limits"),
                   wxT("Display and change the axis limits"));
  menuView->Append(ID_VIEW_AXIS_ROTATE, _T("Rotate 3d axes"),
                   wxT("Change the projection angles of the 3d plot"));
  menuView->Append(ID_VIEW_LABEL_CONTOURS, _T("Label contours"),
                   wxT("Interactive labelling of the contours"));
  menuView->Append(ID_VIEW_DISPLAY_COORD, _T("Display coordinates"),
                   wxT("Display the coordinates on the status bar")); 
  menu_bar->Append(menuView, _T("View"));

// ***************** Logbook menu ******************************
  menuLog = new wxMenu;
  menuLog->Append( ID_LOGBOOK_SHOW, _T("Show logbook"),
                       wxT("Display the logbook window"), wxITEM_RADIO);
  menuLog->Append( ID_LOGBOOK_HIDE, _T("Hide logbook"),
                       wxT("Hide the logbook window"), wxITEM_RADIO);
  menuLog->Append( ID_LOGBOOK_CLEAR, _T("Clear the logbook"),
                       wxT("Clear the logbook content"));
  menuLog->Append( ID_LOGBOOK_CLEAN, _T("Clean the logbook"),
                       wxT("Clean the logbook content"));
  menuLog->Append( ID_LOGBOOK_SAVE, _T("Save cleaned logbook"),
                       wxT("Save a selection from the logbook content"));
  menu_bar->Append(menuLog, _T("Logbook"));

// ***************** Help menu ******************************
  wxMenu *help_menu = new wxMenu;
  help_menu->Append(ID_HELP, _T("&Help"));
  help_menu->Append(ID_CONTEXT_HELP, _T("&Context help...\tCtrl-H"),
                     _T("Get context help for a control"));
  help_menu->Append(ID_ABOUT, _T("&About\tF1"));
  menu_bar->Append(help_menu, _T("&Help"));

  SetMenuBar(menu_bar);

return;
}

void GsegFrame::OnQuit (wxCommandEvent& WXUNUSED(event) )
{
   Close(true);
}

/*****************************************************************
* Help 
*****************************************************************/
void GsegFrame::OnHelp( wxCommandEvent& WXUNUSED(event) )
{
 (void)wxMessageBox(_T("Sorry: \"Help\" is not implemented yet\n") 
                    _T("Current version: 20/02/2019"),
                    _T("Gsegraf1"),
                     wxICON_INFORMATION | wxOK );
}
/*****************************************************************
* About
*****************************************************************/
void GsegFrame::OnAbout( wxCommandEvent& WXUNUSED(event) )
{
 (void)wxMessageBox( _T("Gsegraf1\n")
                     _T("Jean-Louis Prieur (c) 2019\n")
                     _T("Created with wxWidgets"), _T("Gsegraf1"), 
                     wxICON_INFORMATION | wxOK );
}
/*****************************************************************
* Context help
*****************************************************************/
void GsegFrame::OnContextHelp(wxCommandEvent& WXUNUSED(event))
{
// Starts a local event loop
    wxContextHelp chelp(this);
}
/************************************************************************
** Display text in status bar 
*************************************************************************/
void GsegFrame::SetText_to_StatusBar(wxString str1, const int icol)
{
// Update the first field (since 2nd argument is 0 here) of the status bar:
  if(m_StatusBar != NULL) m_StatusBar->SetStatusText(str1, icol);
}
