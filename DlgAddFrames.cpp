#include "DlgAddFrames.h"
#include "wx/msgdlg.h"

//(*InternalHeaders(DlgAddFrames)
#include <wx/string.h>
//*)

//(*IdInit(DlgAddFrames)
const long DlgAddFrames::ID_LISTCTRL1 = wxNewId();
const long DlgAddFrames::ID_BUTTON3 = wxNewId();
const long DlgAddFrames::ID_BUTTON4 = wxNewId();
const long DlgAddFrames::ID_BUTTON5 = wxNewId();
const long DlgAddFrames::ID_BUTTON1 = wxNewId();
const long DlgAddFrames::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DlgAddFrames,wxDialog)
    //(*EventTable(DlgAddFrames)
    //*)
    EVT_LIST_ITEM_SELECTED(DlgAddFrames::ID_LISTCTRL1, DlgAddFrames::OnListSelected)
END_EVENT_TABLE()

DlgAddFrames::DlgAddFrames(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(DlgAddFrames)
    Create(parent, wxID_ANY, _T("添加帧"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(511,444));
    ListCtrl_Files = new wxListCtrl(this, ID_LISTCTRL1, wxPoint(24,8), wxSize(440,391), wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LISTCTRL1"));
    Button_UP = new wxButton(this, ID_BUTTON3, _T("∧"), wxPoint(472,130), wxSize(18,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button_Down = new wxButton(this, ID_BUTTON4, _T("∨"), wxPoint(472,160), wxSize(18,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button_Del = new wxButton(this, ID_BUTTON5, _T("×"), wxPoint(472,190), wxSize(18,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Button_OK = new wxButton(this, ID_BUTTON1, _T("确定"), wxPoint(88,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button1 = new wxButton(this, ID_BUTTON2, _T("取消"), wxPoint(312,408), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));

    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DlgAddFrames::OnButton_UPClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DlgAddFrames::OnButton_DownClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DlgAddFrames::OnButton_DelClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DlgAddFrames::OnButton_OKClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DlgAddFrames::OnButton1Click);
    //*)
    itemsel = -1;

}

DlgAddFrames::~DlgAddFrames()
{
    //(*Destroy(DlgAddFrames)
    //*)
}
void DlgAddFrames::OnListSelected(wxListEvent &event)
{
    itemsel = event.GetIndex();
}
void DlgAddFrames::InitListCtrl(const wxArrayString &files)
{
    ListCtrl_Files->InsertColumn(0, wxT("文件"));
    ListCtrl_Files->SetColumnWidth(0, 430);
    for(size_t i = 0; i < files.GetCount(); i++)
    {
        ListCtrl_Files->InsertItem(i, files[i]);
    }
}

wxArrayString DlgAddFrames::GetArrangedFiles()
{
    wxArrayString arfiles;
    for(int i = 0; i < ListCtrl_Files->GetItemCount(); i++)
    {
        arfiles.Add(ListCtrl_Files->GetItemText((long)i));
    }
    return arfiles;
}

void DlgAddFrames::OnButton_UPClick(wxCommandEvent& event)
{
    if(itemsel > 0)
    {
        wxString tempstr = ListCtrl_Files->GetItemText(itemsel);
        wxString tempstr2 = ListCtrl_Files->GetItemText(itemsel - 1);
        ListCtrl_Files->SetItemText(itemsel, tempstr2);
        ListCtrl_Files->SetItemText(itemsel-1, tempstr);

        itemsel--;
        wxListItem stati;
        stati.SetMask(wxLIST_MASK_STATE);
        stati.SetState(wxLIST_STATE_SELECTED);
        stati.SetId(itemsel);
        ListCtrl_Files->SetItem(stati);
    }
}

void DlgAddFrames::OnButton_DownClick(wxCommandEvent& event)
{
    if(itemsel >= 0 && itemsel < ListCtrl_Files->GetItemCount() -1)
    {
        wxString tempstr = ListCtrl_Files->GetItemText(itemsel);
        wxString tempstr2 = ListCtrl_Files->GetItemText(itemsel + 1);
        ListCtrl_Files->SetItemText(itemsel, tempstr2);
        ListCtrl_Files->SetItemText(itemsel+1, tempstr);

        itemsel++;
        wxListItem stati;
        stati.SetMask(wxLIST_MASK_STATE);
        stati.SetState(wxLIST_STATE_SELECTED);
        stati.SetId(itemsel);
        ListCtrl_Files->SetItem(stati);
    }
}

void DlgAddFrames::OnButton_DelClick(wxCommandEvent& event)
{
    if(itemsel != -1)
    {
        ListCtrl_Files->DeleteItem(itemsel);
        if(itemsel == ListCtrl_Files->GetItemCount()) itemsel--;

        if(itemsel == -1) return;
        wxListItem stati;
        stati.SetMask(wxLIST_MASK_STATE);
        stati.SetState(wxLIST_STATE_SELECTED);
        stati.SetId(itemsel);
        ListCtrl_Files->SetItem(stati);
    }
}

void DlgAddFrames::OnButton_OKClick(wxCommandEvent& event)
{
    this->EndModal(wxID_OK);
}

void DlgAddFrames::OnButton1Click(wxCommandEvent& event)
{
    this->EndModal(wxID_CANCEL);
}
