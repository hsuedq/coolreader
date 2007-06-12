#include <wx/wx.h>
#include <wx/power.h>
#include <wx/mstream.h>
#include <wx/stdpaths.h>
#include <wx/listctrl.h>
#include <crengine.h>
#include "cr3.h"
#include "rescont.h"
#include "HistList.h"

BEGIN_EVENT_TABLE( HistList, wxListView )
//    EVT_PAINT( cr3view::OnPaint )
//    EVT_SIZE    ( cr3view::OnSize )
//    EVT_MOUSEWHEEL( cr3view::OnMouseWheel )
//    EVT_LEFT_DOWN( cr3view::OnMouseLDown )
//    EVT_RIGHT_DOWN( cr3view::OnMouseRDown )
//    EVT_MENU_RANGE( 0, 0xFFFF, cr3view::OnCommand )
//    EVT_SET_FOCUS( cr3view::OnSetFocus )
//    EVT_TIMER(RENDER_TIMER_ID, cr3view::OnTimer)
//    EVT_TIMER(CLOCK_TIMER_ID, cr3view::OnTimer)
//    EVT_INIT_DIALOG(cr3view::OnInitDialog)
END_EVENT_TABLE()

HistList::HistList()
: _records(NULL)
{
}

HistList::~HistList()
{
    if ( _records )
        delete _records;
}

void HistList::SetRecords(LVPtrVector<CRFileHistRecord> & records )
{
    if ( _records )
        delete _records;
    _records = new LVPtrVector<CRFileHistRecord>( records );
    SetItemCount(_records->length());
    SetColumnWidth(0, wxLIST_AUTOSIZE);
    SetColumnWidth(1, wxLIST_AUTOSIZE);
    SetColumnWidth(2, wxLIST_AUTOSIZE);
    if ( GetItemCount()>0 ) {
        Select(0);
    }
}

bool HistList::Create(wxWindow* parent, wxWindowID id )
{
    bool res = wxListView::Create(parent, id, wxDefaultPosition, wxDefaultSize, 
        wxLC_REPORT | wxLC_VIRTUAL | wxLC_SINGLE_SEL );
    wxListItem col1;
    //wxListItem col2;
    //col1.SetColumn(0);
    col1.SetText(wxString(wxT("Last time")));
    //col1.SetWidth(wxLIST_AUTOSIZE);
    col1.SetAlign(wxLIST_FORMAT_CENTRE);
    InsertColumn( 0, col1 );

    col1.SetAlign(wxLIST_FORMAT_LEFT);
    col1.SetText(wxString(wxT("Book")));
    InsertColumn( 1, col1 );
    col1.SetText(wxString(wxT("Pos")));
    InsertColumn( 2, col1 );
    SetItemCount(20);

    SetColumnWidth(0, wxLIST_AUTOSIZE);
    SetColumnWidth(1, wxLIST_AUTOSIZE);
    SetColumnWidth(2, wxLIST_AUTOSIZE);
    SetColumnWidth(3, wxLIST_AUTOSIZE);

    Update();

    //SetColumnWidth(0, wxLIST_AUTOSIZE);
    //col1.
    //col2.SetColumn(1);
    //SetColumnWidth(1, wxLIST_AUTOSIZE);
    //SetColumn( 0, col1 );
    //SetColumn( 1, col2 );
    //SetColumn( 2, col3 );
    return res;
}

wxString HistList::OnGetItemText(long item, long column) const
{
    if ( _records && item>=0 && item<_records->length() ) {
        CRFileHistRecord * rec = (*_records)[item];
        lString16 data;
        switch ( column ) {
        case 0:
            data = rec->getLastTimeString();
            break;
        case 1:
            {
                lString16 fname = rec->getFileName();
                lString16 author = rec->getAuthor();
                lString16 title = rec->getTitle();
                lString16 series = rec->getSeries();
                if ( !series.empty() ) {
                    if ( !title.empty() )
                        title << L" ";
                    title << series;
                }
                if ( !author.empty() && !title.empty() )
                    author << L". ";
                data << author << title;
                if ( data.empty() )
                    data = fname;
            }
            break;
        case 2:
            {
                data = lString16::itoa(rec->getLastPos()->getPercent()/100) + L"%";
            }
            break;
        }
        return wxString(data.c_str());
    } else
        return wxString(wxT(""));
}


/*

wxColour cr3view::getBackgroundColour()
{
#if (COLOR_BACKBUFFER==1)
    lUInt32 cl = _docview->getBackgroundColor();
#else
    lUInt32 cl = 0xFFFFFF;
#endif
    wxColour wxcl( (cl>>16)&255, (cl>>8)&255, (cl>>0)&255 );
    return wxcl;
}

void cr3view::OnInitDialog(wxInitDialogEvent& event)
{
    //SetBackgroundColour( getBackgroundColour() );
}

lString16 cr3view::GetLastRecentFileName()
{
    if ( _docview && _docview->getHistory()->getRecords().length()>0 )
        return _docview->getHistory()->getRecords()[0]->getFilePathName();
    return lString16();
}

cr3view::cr3view()
: _scrollbar(NULL)
, _firstRender(false)
{
    _docview = new LVDocView();

    {
        LVStreamRef stream = LVOpenFileStream( GetHistoryFileName().c_str(), LVOM_READ );
        if ( !stream.isNull() ) {
            _docview->getHistory()->loadFromStream( stream.get() );
        }
    }


    _renderTimer = new wxTimer( this, RENDER_TIMER_ID );
    _clockTimer = new wxTimer( this, CLOCK_TIMER_ID );

    //SetBackgroundColour( getBackgroundColour() );
    InitDialog();
    //int width, height;
    //GetClientSize( &width, &height );
	//Resize( 300, 300 );	
}

cr3view::~cr3view()
{
    delete _renderTimer;
    delete _clockTimer;
    delete _docview;
}

void cr3view::OnTimer(wxTimerEvent& event)
{
    //printf("cr3view::OnTimer() \n");
    if ( event.GetId() == RENDER_TIMER_ID ) {
        int dx;
        int dy;
        GetClientSize( &dx, &dy );
        if ( _docview->IsRendered() && dx == _docview->GetWidth()
                && dy == _docview->GetHeight() )
            return; // no resize
        if (dx<5 || dy<5 || dx>3000 || dy>3000)
        {
            return;
        }

        if ( _firstRender ) {
            _docview->restorePosition();
            _firstRender = false;
        }

        _docview->Resize( dx, dy );

        UpdateScrollBar();
        Paint();
    } else if ( event.GetId() == CLOCK_TIMER_ID ) {
        if ( IsShownOnScreen() ) {
            if ( _docview->IsRendered() && _docview->isTimeChanged() )
                Paint();
        }
    }
}

void cr3view::Paint()
{
    //printf("cr3view::Paint() \n");
    int battery_state = -1;
#ifdef _WIN32
    SYSTEM_POWER_STATUS bstatus;
    BOOL pow = GetSystemPowerStatus(&bstatus);
    if (bstatus.BatteryFlag & 128)
        pow = FALSE;
    if (bstatus.ACLineStatus!=0 || bstatus.BatteryLifePercent==255)
        pow = FALSE;
    if ( pow )
        battery_state = bstatus.BatteryLifePercent;
#else
    if ( ::wxGetPowerType() == wxPOWER_BATTERY ) {
        int n = ::wxGetBatteryState();
        if ( n == wxBATTERY_NORMAL_STATE )
            battery_state = 100;
        else if ( n == wxBATTERY_LOW_STATE )
            battery_state = 50;
        else if ( n == wxBATTERY_CRITICAL_STATE )
            battery_state = 0;
        else if ( n == wxBATTERY_SHUTDOWN_STATE )
            battery_state = 0;
    };
#endif
    _docview->setBatteryState( battery_state );
    _docview->Draw();
    Refresh( FALSE );
}

static lChar16 detectSlash( lString16 path )
{
    for ( unsigned i=0; i<path.length(); i++ )
        if ( path[i]=='\\' || path[i]=='/' )
            return path[i];
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

lString16 cr3view::GetHistoryFileName()
{
    lString16 cfgdir( wxStandardPaths::Get().GetUserDataDir().c_str() );
    if ( !wxDirExists( cfgdir.c_str() ) )
        ::wxMkdir( wxString( cfgdir.c_str() ) );
    lChar16 slash = detectSlash( cfgdir );
    cfgdir << slash;
    return cfgdir + L"cr3hist.bmk";
}

void cr3view::CloseDocument()
{
    //printf("cr3view::CloseDocument()  \n");
    _docview->savePosition();
    _docview->Clear();
    LVStreamRef stream = LVOpenFileStream( GetHistoryFileName().c_str(), LVOM_WRITE );
    if ( !stream.isNull() )
        _docview->getHistory()->saveToStream( stream.get() );
}

void cr3view::UpdateScrollBar()
{
	if ( !_scrollbar )
		return;
    const LVScrollInfo * lvsi = _docview->getScrollInfo();
    _scrollbar->SetScrollbar(
        lvsi->pos,      //int position, 
        lvsi->pagesize, //int thumbSize, 
        lvsi->maxpos + lvsi->pagesize,   //int range, 
        lvsi->pagesize, //int pageSize, 
        true//const bool refresh = true
    );
    wxStatusBar * sb = ((wxFrame*)GetParent())->GetStatusBar();
    if ( sb )
        sb->SetStatusText( wxString( lvsi->posText.c_str() ), 1 );

}

void cr3view::OnMouseLDown( wxMouseEvent & event )
{
    int x = event.GetX();
    int y = event.GetY();
    ldomXPointer ptr = _docview->getNodeByPoint( lvPoint( x, y ) );
    if ( ptr.isNull() ) {
        printf("node not found!\n");

        return;
    }
    if ( ptr.getNode()->isText() ) {
        printf("text : %s     \t", UnicodeToUtf8( ptr.toString() ).c_str() );
    } else {
        printf("element : %s  \t", UnicodeToUtf8( ptr.toString() ).c_str() );
    }
    lvPoint pt2 = ptr.toPoint();
    printf("  (%d, %d)  ->  (%d, %d)\n", x, y+_docview->GetPos(), pt2.x, pt2.y);
}

void cr3view::OnMouseRDown( wxMouseEvent & event )
{
    wxMenu pm;
    pm.Append( wxID_OPEN, wxT( "&Open...\tCtrl+O" ) );
    pm.Append( wxID_SAVE, wxT( "&Save...\tCtrl+S" ) );
    pm.AppendSeparator();
    pm.Append( Menu_View_TOC, wxT( "Table of Contents\tF5" ) );
    pm.Append( Menu_File_About, wxT( "&About...\tF1" ) );
    pm.AppendSeparator();
    pm.Append( Menu_View_ZoomIn, wxT( "Zoom In" ) );
    pm.Append( Menu_View_ZoomOut, wxT( "Zoom Out" ) );
    pm.AppendSeparator();
    pm.Append( Menu_View_ToggleFullScreen, wxT( "Toggle Fullscreen\tAlt+Enter" ) );
    pm.Append( Menu_View_TogglePages, wxT( "Toggle Pages/Scroll\tCtrl+P" ) );
    pm.Append( Menu_View_TogglePageHeader, wxT( "Toggle page heading\tCtrl+H" ) );
    pm.AppendSeparator();
    pm.Append( Menu_File_Quit, wxT( "E&xit\tAlt+X" ) );

    ((wxFrame*)GetParent())->PopupMenu(&pm);
}

void cr3view::TogglePageHeader()
{
    _docview->setPageHeaderInfo(
        _docview->getPageHeaderInfo() ?
        0 :
              PGHDR_PAGE_NUMBER
            | PGHDR_PAGE_COUNT
            | PGHDR_AUTHOR
            | PGHDR_TITLE
        );
    UpdateScrollBar();
    Paint();
}

void cr3view::ToggleViewMode()
{
    _docview->setViewMode( _docview->getViewMode()==DVM_SCROLL ? DVM_PAGES : DVM_SCROLL );
    UpdateScrollBar();
    Paint();
}

void cr3view::OnCommand(wxCommandEvent& event)
{
	switch ( event.GetId() ) {
	case Menu_View_ZoomIn:
        {
	        wxCursor hg( wxCURSOR_WAIT );
	        this->SetCursor( hg );
	        wxSetCursor( hg );
            //===========================================
            doCommand( DCMD_ZOOM_IN, 0 );
            //===========================================
	        this->SetCursor( wxNullCursor );
	        wxSetCursor( wxNullCursor );
        }
		break;
	case Menu_View_ZoomOut:
        {
	        wxCursor hg( wxCURSOR_WAIT );
	        this->SetCursor( hg );
	        wxSetCursor( hg );
            //===========================================
    	    doCommand( DCMD_ZOOM_OUT, 0 );
            //===========================================
	        this->SetCursor( wxNullCursor );
	        wxSetCursor( wxNullCursor );
        }
		break;
	case Menu_View_NextPage:
	    doCommand( DCMD_PAGEDOWN, 1 );
		break;
	case Menu_View_PrevPage:
		doCommand( DCMD_PAGEUP, 1 );
		break;
	case Menu_View_NextLine:
	    doCommand( DCMD_LINEDOWN, 1 );
		break;
	case Menu_View_PrevLine:
		doCommand( DCMD_LINEUP, 1 );
		break;
	case Menu_View_Begin:
	    doCommand( DCMD_BEGIN, 0 );
		break;
	case Menu_View_End:
		doCommand( DCMD_END, 0 );
		break;
    case Menu_View_TogglePages:
        ToggleViewMode();
        break;
    case Menu_View_TogglePageHeader:
        TogglePageHeader();
        break;
	}
}

void cr3view::OnScroll(wxScrollEvent& event)
{
    int id = event.GetEventType();
    //printf("Scroll event: %d\n", id);
    if (id == wxEVT_SCROLL_TOP)
        doCommand( DCMD_BEGIN, 0 );
    else if (id == wxEVT_SCROLL_BOTTOM )
        doCommand( DCMD_BEGIN, 0 );
    else if (id == wxEVT_SCROLL_LINEUP )
        doCommand( DCMD_LINEUP, 0 );
    else if (id == wxEVT_SCROLL_LINEDOWN )
        doCommand( DCMD_LINEDOWN, 0 );
    else if (id == wxEVT_SCROLL_PAGEUP )
        doCommand( DCMD_PAGEUP, 0 );
    else if (id == wxEVT_SCROLL_PAGEDOWN )
        doCommand( DCMD_PAGEDOWN, 0 );
    else if (id == wxEVT_SCROLL_THUMBRELEASE || id == wxEVT_SCROLL_THUMBTRACK)
    {
        doCommand( DCMD_GO_POS,
              _docview->scrollPosToDocPos( event.GetPosition() ) );
    }
}

void cr3view::OnMouseWheel(wxMouseEvent& event)
{
    int rotation = event.GetWheelRotation();
    if ( rotation>0 )
        doCommand( DCMD_LINEUP, 3 );
    else if ( rotation<0 )
        doCommand( DCMD_LINEDOWN, 3 );
}

void cr3view::OnKeyDown(wxKeyEvent& event)
{
    int code = event.GetKeyCode() ;
    
        switch( code )
        {
        case WXK_NUMPAD_ADD:
            {
        doCommand( DCMD_ZOOM_IN, 0 );
            }
            break;
        case WXK_NUMPAD_SUBTRACT:
            {
        doCommand( DCMD_ZOOM_OUT, 0 );
            }
            break;

        }
}

bool cr3view::LoadDocument( const wxString & fname )
{
    //printf("cr3view::LoadDocument()\n");
    _renderTimer->Stop();
    _clockTimer->Stop();
    CloseDocument();

	wxCursor hg( wxCURSOR_WAIT );
	this->SetCursor( hg );
	wxSetCursor( hg );
    //===========================================
    GetParent()->Update();
    //printf("   loading...  ");
	bool res = _docview->LoadDocument( fname.c_str() );
    //printf("   done. \n");
	//DEBUG
	//_docview->exportWolFile( "test.wol", true );
	//_docview->SetPos(0);
    lString16 title = (_docview->getAuthors() + L". " + _docview->getTitle());
    GetParent()->SetLabel( wxString( title.c_str() ) );
    _firstRender = true;
    ScheduleRender();
    //_docview->restorePosition();
	//_docview->Render();
	//UpdateScrollBar();
	//Paint();
    GetParent()->SetFocus();
    //===========================================
	wxSetCursor( wxNullCursor );
	this->SetCursor( wxNullCursor );
    return res;
}

void cr3view::goToBookmark(ldomXPointer bm)
{
    _docview->goToBookmark(bm);
    UpdateScrollBar();
    Paint();
}

void cr3view::doCommand( LVDocCmd cmd, int param )
{
    _docview->doCommand( cmd, param );
    UpdateScrollBar();
    Paint();
}

void cr3view::Resize(int dx, int dy)
{
    //printf("   Resize(%d,%d) \n", dx, dy );
    if ( dx==0 && dy==0 ) {
        GetClientSize( &dx, &dy );
    }
    if ( _docview->IsRendered() && _docview->GetWidth() == dx && _docview->GetHeight() == dy )
        return; // no resize
    if (dx<5 || dy<5 || dx>3000 || dy>3000)
    {
        return;
    }
    _renderTimer->Stop();
    _renderTimer->Start( 100, wxTIMER_ONE_SHOT );
    _clockTimer->Stop();
    _clockTimer->Start( 10 * 1000, wxTIMER_CONTINUOUS );
}

void cr3view::OnPaint(wxPaintEvent& event)
{
    //printf("   OnPaint()  \n" );
    wxPaintDC dc(this);

    int dx = _docview->GetWidth();
    int dy = _docview->GetHeight();
    wxImage img;
    img.Create(dx, dy, true);

    unsigned char * bits = img.GetData();
    for ( int y=0; y<dy; y++ ) {
		int bpp = _docview->GetDrawBuf()->GetBitsPerPixel();
		if ( bpp==32 ) {
            const lUInt32* src = (const lUInt32*) _docview->GetDrawBuf()->GetScanLine( y );
            unsigned char * dst = bits + y*dx*3;
            for ( int x=0; x<dx; x++ )
            {
                lUInt32 c = *src++;
                *dst++ = (c>>16) & 255;
                *dst++ = (c>>8) & 255;
                *dst++ = (c>>0) & 255;
            }
		} else if ( bpp==2 ) {
			//
			static const unsigned char palette[4][3] = {
				{ 0xff, 0xff, 0xff },
				{ 0xaa, 0xaa, 0xaa },
				{ 0x55, 0x55, 0x55 },
				{ 0x00, 0x00, 0x00 },
			};
			const lUInt8* src = (const lUInt8*) _docview->GetDrawBuf()->GetScanLine( y );
			unsigned char * dst = bits + y*dx*3;
			for ( int x=0; x<dx; x++ )
			{
				lUInt32 c = (( src[x>>2] >> ((3-(x&3))<<1) ))&3;
				*dst++ = palette[c][0];
				*dst++ = palette[c][1];
				*dst++ = palette[c][2];
			}
		} else if ( bpp==1 ) {
			//
			static const unsigned char palette[2][3] = {
				{ 0xff, 0xff, 0xff },
				{ 0x00, 0x00, 0x00 },
			};
			const lUInt8* src = (const lUInt8*) _docview->GetDrawBuf()->GetScanLine( y );
			unsigned char * dst = bits + y*dx*3;
			for ( int x=0; x<dx; x++ )
			{
				lUInt32 c = (( src[x>>3] >> ((7-(x&7))) ))&1;
				*dst++ = palette[c][0];
				*dst++ = palette[c][1];
				*dst++ = palette[c][2];
			}
		}
    }

    // fill
    wxBitmap bmp( img );
    dc.DrawBitmap( bmp, 0, 0, false );
}

void cr3view::OnSize(wxSizeEvent& event)
{
    int width, height;
    GetClientSize( &width, &height );
    //printf("   OnSize(%d, %d)  \n", width, height );
    Resize( width, height );
}

*/