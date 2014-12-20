#include "FocusSequence.h"
#include "wx/msgdlg.h"
#include "wx/spinctrl.h"

void FocusSequence::AddWindow(wxWindow *wnd, bool Enabled)
{
    if(first == NULL)
    {
        first = new WndElm();
        current = first;

        first->wnd = wnd;
        first->ID = wnd->GetId();
        first->enabled = Enabled;
        first->next = first;
    }
    else
    {
        current->next = new WndElm();
        current = current->next;

        current->wnd = wnd;
        current->ID = wnd->GetId();
        current->enabled = Enabled;
        current->next = first;
    }
    size++;
}
bool FocusSequence::SetNextFocuse(wxWindow *wnd)
{
    if(first == NULL || wnd == NULL) return false;

    int id = wnd->GetId();
    long idx;
    WndElm *temp;
    wxWindow *reswnd = NULL;

    //find next window
    temp = first;
    idx = -1;
    for(size_t i = 0; i < size; i++)
    {
        if(temp->ID == id)
        {
            idx = (long)i;
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    if(idx == -1)return false;

    //check whether disabled,if disabled,find next
    if(!temp->next->wnd->IsEnabled() || !temp->next->enabled)
    {
        temp = temp->next;
        //find first enabled window in loop.
        for(size_t c = 0; c < size; c++)
        {
            if(temp->wnd->IsEnabled() && temp->enabled)
            {
                temp->wnd->SetFocus();
                reswnd = temp->wnd;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }
        if(reswnd == NULL) return false;
    }
    else
    {
        temp->next->wnd->SetFocus();
        reswnd = temp->next->wnd;
    }

    if(reswnd->IsKindOf(CLASSINFO(wxSpinCtrl)))
    {
        wxSpinCtrl* spc = (wxSpinCtrl*)reswnd;
        spc->SetSelection(-1, -1);
    }
    return true;
}
bool FocusSequence::SetNextFocuse(size_t index)
{
    wxWindow *wnd = GetWindow(index);
    if(wnd != NULL)
    {
        return SetNextFocuse(wnd);
    }
    return true;
}
bool FocusSequence::isWndIn(wxWindow *wnd)
{
    if(first == NULL || wnd == NULL) return false;

    int id = wnd->GetId();
    long idx;
    WndElm *temp;

    //find next window
    temp = first;
    idx = -1;
    for(size_t i = 0; i < size; i++)
    {
        if(temp->ID == id)
        {
            idx = (long)i;
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    if(idx == -1)return false;
    else return true;
}
wxWindow* FocusSequence::GetWindow(size_t index)
{
    if(index < size && size > 0)
    {
        WndElm *temp = first;
        for(size_t i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->wnd;
    }
    else
    {
        return NULL;
    }

}
void FocusSequence::DeleteStorage()
{
    if(first == NULL) return;

    WndElm *temp1 = first, *temp2;
    for(size_t i = 0; i < size; i++)
    {
        temp2 = temp1->next;
        delete temp1;
        temp1 = temp2;
    }
}
