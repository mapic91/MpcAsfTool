#ifndef TABSEQUENCE_H
#define TABSEQUENCE_H

#include "wx/window.h"

struct WndElm
{
    int ID;
    bool enabled;
    wxWindow *wnd;
    WndElm *next;
};

class FocusSequence
{
    public:
        FocusSequence(){Init();}
        ~FocusSequence(){DeleteStorage();}
        void Init(){size = 0;first = NULL;current = NULL;}
        //The sequence is same to the add sequence
        //if Enabled is false, this wnd is in list but not considerd
        void AddWindow(wxWindow *wnd, bool Enabled = true);
        //Set window focuse which after wnd,if wnd is not added,nothing happan
        bool SetNextFocuse(wxWindow *wnd);
        //Set window focuse at index+1,if index out of range,nothing happan
        bool SetNextFocuse(size_t index);
        //Return true if wnd is in added window list
        bool isWndIn(wxWindow *wnd);
        //if out of range,return NULL
        wxWindow* GetWindow(size_t index);
        size_t GetCount(){return size;}
    protected:
    private:
        //free heap
        void DeleteStorage();

        size_t size;
        WndElm *first, *current;
};

#endif // TABSEQUENCE_H
