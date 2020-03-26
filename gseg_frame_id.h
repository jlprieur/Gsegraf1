/****************************************************************************
* Name: gseg_frame_id.h  (GsegFrame class)
* list of ID used by GsegFrame class
* 
* JLP
* Version 02/06/2015
****************************************************************************/
#ifndef _gseg_frame_id_h_
#define _gseg_frame_id_h_

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

//---------------------------------------------------------------------
//---------------------------------------------------------------------
enum{
  ID_QUIT         = wxID_EXIT,
// File:
  ID_SAVE_TO_PST  = 1051,
  ID_SAVE_TO_FILE,
  ID_LOAD_GSEG_PARAM_FILE,
  ID_LOAD_GDEV_PARAM_FILE,
  ID_LOAD_IMAGE_FOR_PLOT,
  ID_LOAD_CURVE_FOR_PLOT,

// panel menu
  ID_CONTEXT_HELP,

// View menu
  ID_VIEW_AXIS_LIMITS,
  ID_VIEW_AXIS_ROTATE,
  ID_VIEW_LABEL_CONTOURS,
  ID_VIEW_DISPLAY_COORD,

// Logbook
  ID_LOGBOOK_SHOW,
  ID_LOGBOOK_HIDE,
  ID_LOGBOOK_CLEAR,
  ID_LOGBOOK_CLEAN,
  ID_LOGBOOK_SAVE,

// Help:
  ID_ABOUT          = wxID_ABOUT,
  ID_HELP           = wxID_HELP
};

#endif
