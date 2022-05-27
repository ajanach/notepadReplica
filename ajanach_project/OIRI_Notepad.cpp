//uključena zaglavlja:
#include <wx/wx.h>
#include <wx/printdlg.h>
#include <wx/string.h>
#include <wx/fdrepdlg.h>
#include <wx/numdlg.h>
#include <wx/fontdlg.h>
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h>
#include <string>

class Notepad : public wxFrame {
public:
    Notepad() : wxFrame(NULL, wxID_ANY, wxT("Oiri Notepad"), wxDefaultPosition, wxSize(650, 500)) {
        wxMenuBar* menu = new wxMenuBar();
        wxMenu* file = new wxMenu();
        wxMenu* edit = new wxMenu();
        wxMenu* format = new wxMenu();
        wxMenu* view = new wxMenu();
        wxMenu* help = new wxMenu();
        wxMenu* PowerShell = new wxMenu();

        menu->Append(file, wxT("&File"));
        menu->Append(edit, wxT("&Edit"));
        menu->Append(format, wxT("&Format"));
        menu->Append(view, wxT("&View"));
        menu->Append(help, wxT("&Help"));
        menu->Append(PowerShell, wxT("&PowerShell"));

        file->Append(idFileNew, wxT("&New File\tCtrl+N"));
        file->Append(idFileNewWindow, wxT("&New Window\tCtrl+Shift+N"));
        file->Append(idFileOpen, wxT("&Open File\tCtrl+O"));
        file->Append(idFileSave, wxT("&Save\tCtrl+S"));
        file->Append(idFileSaveAs, wxT("&Save As...\tCtrl+Shift+S"));
        file->AppendSeparator();
        file->Append(idFilePageSetup, wxT("&Page Setup"));
        file->Append(idFilePrint, wxT("&Print\tCtrl+P"));
        file->AppendSeparator();
        file->Append(idFileExit, wxT("&Exit\tCtrl+W"));
        
        edit->Append(idEditUndo, wxT("&Undo\tCtrl+Z"));
        edit->AppendSeparator();
        edit->Append(idEditCut, wxT("&Cut\tCtrl+X"));
        edit->Append(idEditCopy, wxT("&Copy\tCtrl+C"));
        edit->Append(idEditPaste, wxT("&Paste\tCtrl+V"));
        edit->Append(idEditDelete, wxT("&Delete\tDel"));
        edit->AppendSeparator();
        edit->Append(idEditFind, wxT("&Find\tCtrl+F"));
        edit->Append(idEditReplace, wxT("&Replace\tCtrl+H"));
        edit->Append(idEditGoto, wxT("&Goto\tCtrl+G"));
        edit->AppendSeparator();
        edit->Append(idEditSelectAll, wxT("&Select All\tCtrl+A"));
        edit->Append(idEditTimeDate, wxT("&Time Date\tF5"));
        
        format->Append(idFormatAutoLine, "&Auto Line");
        format->Append(idFormatWordWrap, wxT("&Word wrap"));
        format->Append(idFormatFont, wxT("&Font..."));

        view->Append(idViewStatBar, wxT("&Status bar"));

        help->Append(idHelpAbout, wxT("&About"));

        PowerShell->Append(idPS, wxT("&Start"));

        text = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_MULTILINE);
        this->text->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));
        this->text->SetForegroundColour(*wxBLACK);
        this->text->SetBackgroundColour(*wxWHITE);

        this->SetIcon(wxIcon(wxT("note.ico"), wxBITMAP_TYPE_ICO)); //postavljanje ikone okvira
        this->SetLabel("Untitled - Oiri Notepad"); //Postavljanje naslova okvira
        this->SetMenuBar(menu);

        this->filePath = ""; //dodijeljena vrijednost varijabli
        this->isStatusShow = false;

        //kreiranje status bar-a:
        const int size = 2;
        this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE | wxSB_SUNKEN);
        this->SetStatusText(wxT("Status: Ready!"), 0);
        this->SetStatusText(wxT("Welcome to Oiri Notepad"), 1);
        int a[size] = { -1, 200 };
        this->GetStatusBar()->SetStatusWidths(size, a);
        this->GetStatusBar()->Show();
    }

private:
    wxTextCtrl* text;
    wxString filePath; 
    bool isStatusShow;
    
    void OnFileNew(wxCommandEvent& event) {
        text->SetValue("");
        SetLabel("Untitled - Oiri Notepad");
        filePath = "";
        
        //status:
        PushStatusText(wxT("Status: New file"));
        wxSleep(1.5);
        PopStatusText();
    }

    void OnFileNewWindow(wxCommandEvent& event) {
        Notepad* newWindow = new Notepad();
        newWindow->Show();
        
        //status:
        PushStatusText(wxT("Status: Opening new window"));
        wxSleep(1.5);
        PopStatusText();
    }

    void OnFileOpen(wxCommandEvent& event) {
        wxFileDialog* openDialog = new wxFileDialog(this, wxT("Open"), wxT(""), wxT(""), wxT("Text Files (*.txt)|*.txt|All Files (*.*)|*.*|C++ Files (*.cpp)|*.cpp"), wxFD_OPEN);
        if (openDialog->ShowModal() == wxID_OK) {
            this->text->LoadFile(openDialog->GetPath());
            filePath = openDialog->GetPath();
            SetLabel(openDialog->GetFilename() + " - Oiri Notepad");
            
            //status:
            PushStatusText(wxT("Status: ") + openDialog->GetFilename() + wxT(" is opened"));
            wxSleep(2);
            PopStatusText();
        }
    }

    void OnFileSave(wxCommandEvent& event) {
        if (filePath != "") {
            text->SaveFile(filePath);
            
            //status:
            PushStatusText(wxT("Status: File is saved"));
            wxSleep(1.5);
            PopStatusText();

            return;
        }  
        
        wxFileDialog* saveDialog = new wxFileDialog(this, wxT("Save As"), wxEmptyString, wxT(""), wxT("Text Files (*.txt)|*.txt|All Files (*.*)|*.*|C++ Files (*.cpp)|*.cpp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        saveDialog->SetFilterIndex(1);
        if (saveDialog->ShowModal() == wxID_OK) {
            text->SaveFile(saveDialog->GetPath().c_str());
            filePath = saveDialog->GetPath();
            SetLabel(saveDialog->GetFilename() + " - Oiri Notepad");
            
            //status:
            PushStatusText(wxT("Status: File is saved as ") + saveDialog->GetFilename());
            wxSleep(2);
            PopStatusText();
        }
    }

    void OnFileSaveAs(wxCommandEvent& event) {
        wxFileDialog* saveAsDialog = new wxFileDialog(this, wxT("Save File~"), wxT(""), wxT(""), wxT("Text Files (*.txt)|*.txt|All Files (*.*)|*.*|C++ Files (*.cpp)|*.cpp"), wxFD_SAVE);
        saveAsDialog->SetFilterIndex(1);
        if (saveAsDialog->ShowModal() == wxID_OK) {
            text->SaveFile(saveAsDialog->GetPath().c_str());
            filePath = saveAsDialog->GetPath();
            SetLabel(saveAsDialog->GetFilename() + " - Oiri Notepad");

            //status:
            PushStatusText(wxT("Status: File is saved as ") + saveAsDialog->GetFilename());
            wxSleep(2);
            PopStatusText();
        }
    } 

    void OnFilePageSetup(wxCommandEvent& event) {
        PushStatusText(wxT("Status: Page setup"));
        wxSleep(1.5);
        PopStatusText();
        wxPageSetupDialog* pageSetupDialog = new wxPageSetupDialog(this);
        pageSetupDialog->ShowModal();

        //status:
        PushStatusText(wxT("Status: Page setup configuration is saved."));
        wxSleep(1.5);
        PopStatusText();
    }

    void OnFilePrint(wxCommandEvent& event) {
        PushStatusText(wxT("Status: Print"));
        wxSleep(1.5);
        PopStatusText();
        wxPrintDialog* printDialog = new wxPrintDialog(this);
        printDialog->ShowModal();

        //status:
        PushStatusText(wxT("Status: Printing..."));
        wxSleep(1.5);
        PopStatusText();
    }

    void OnFileExit(wxCommandEvent& event) {
        if (text->GetValue() == "")
        {
            //status:
            PushStatusText(wxT("Status: Exiting..."));
            wxSleep(1.5);

            this->Destroy();
        }

        else
        {
            wxMessageDialog* messageDialog = new wxMessageDialog(this, wxT("Do you want to save changes?"), wxT("Info"), wxYES_NO | wxCANCEL | wxYES_DEFAULT | wxICON_QUESTION);

            switch (messageDialog->ShowModal())
            {
            case wxID_YES:
                if (filePath != "") {
                    text->SaveFile(filePath);

                    //status:
                    PushStatusText(wxT("Status: File is saved"));
                    wxSleep(1.5);
                    PushStatusText(wxT("Status: Exiting..."));
                    wxSleep(1.5);

                    this->Destroy();
                    return;
                }

                if (filePath == "")
                {
                    wxFileDialog* saveDialog = new wxFileDialog(this, wxT("Save As"), wxEmptyString, wxT(""), wxT("Text Files (*.txt)|*.txt|All Files (*.*)|*.*|C++ Files (*.cpp)|*.cpp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
                    saveDialog->SetFilterIndex(1);
                    if (saveDialog->ShowModal() == wxID_OK) {
                        text->SaveFile(saveDialog->GetPath().c_str());
                        filePath = saveDialog->GetPath();
                        SetLabel(saveDialog->GetFilename() + " - Oiri Notepad");

                        //status:
                        PushStatusText(wxT("Status: File is saved as ") + saveDialog->GetFilename());
                        wxSleep(2);
                        PushStatusText(wxT("Status: Exiting..."));
                        wxSleep(1.5);

                        this->Destroy();
                    }
                }
                break;
            case wxID_NO:
                //status:
                PushStatusText(wxT("Status: Exiting..."));
                wxSleep(1.5);

                this->Destroy();
                break;
            case wxID_CANCEL:
                PushStatusText(wxT("Status: Action is canceled"));
                wxSleep(1.5);
                PopStatusText();

                break;
            default:
                PushStatusText(wxT("Status: Error"));
                wxSleep(1.5);
                PopStatusText();
                break;
            }
        }
    }

    void OnXButton(wxCloseEvent& event) {
        if (text->GetValue() == "")
        {
            //status:
            PushStatusText(wxT("Status: Exiting..."));
            wxSleep(1.5);

            this->Destroy();
        }

        else
        {
            wxMessageDialog* messageDialog = new wxMessageDialog(this, wxT("Do you want to save changes?"), wxT("Info"), wxYES_NO | wxCANCEL | wxYES_DEFAULT | wxICON_QUESTION);

            switch (messageDialog->ShowModal())
            {
            case wxID_YES:
                if (filePath != "") {
                    text->SaveFile(filePath);

                    //status:
                    PushStatusText(wxT("Status: File is saved"));
                    wxSleep(1.5);
                    PushStatusText(wxT("Status: Exiting..."));
                    wxSleep(1.5);

                    this->Destroy();
                    return;
                }

                if (filePath == "")
                {
                    wxFileDialog* saveDialog = new wxFileDialog(this, wxT("Save As"), wxEmptyString, wxT(""), wxT("Text Files (*.txt)|*.txt|All Files (*.*)|*.*|C++ Files (*.cpp)|*.cpp"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
                    saveDialog->SetFilterIndex(1);
                    if (saveDialog->ShowModal() == wxID_OK) {
                        text->SaveFile(saveDialog->GetPath().c_str());
                        filePath = saveDialog->GetPath();
                        SetLabel(saveDialog->GetFilename() + " - Oiri Notepad");

                        //status:
                        PushStatusText(wxT("Status: File is saved as ") + saveDialog->GetFilename());
                        wxSleep(2);
                        PushStatusText(wxT("Status: Exiting..."));
                        wxSleep(1.5);

                        this->Destroy();
                    }
                }
                break;
            case wxID_NO:
                //status:
                PushStatusText(wxT("Status: Exiting..."));
                wxSleep(1.5);

                this->Destroy(); 
                break;
            case wxID_CANCEL:
                PushStatusText(wxT("Status: Action is canceled"));
                wxSleep(1.5);
                PopStatusText();

                break;
            default:
                PushStatusText(wxT("Status: Error"));
                wxSleep(1.5);
                PopStatusText();
                break;
            }
        }
    }

    void OnEditUndo(wxCommandEvent& event) {
        //status:
        PushStatusText(wxT("Status: undo"));
        wxSleep(1);
        PopStatusText();

        text->Undo();
    }

    void OnEditCut(wxCommandEvent& event) {
        //status:
        PushStatusText(wxT("Status: Cut"));
        wxSleep(1);
        PopStatusText();

        text->Cut();
    }

    void OnEditCopy(wxCommandEvent& event) {
        //status:
        PushStatusText(wxT("Status: Copy"));
        wxSleep(1);
        PopStatusText();

        text->Copy();
    }

    void OnEditPaste(wxCommandEvent& event) {
        //status:
        PushStatusText(wxT("Status: Paste"));
        wxSleep(1);
        PopStatusText();

        text->Paste();
    }

    void OnEditDelete(wxCommandEvent& event) {
        //status:
        PushStatusText(wxT("Status: Delete"));
        wxSleep(1);
        PopStatusText();

        text->RemoveSelection();
    }

    void OnEditFind(wxCommandEvent& event) {
            wxFindReplaceData* findData = new wxFindReplaceData();
            PushStatusText(wxT("Status: Find"));
            wxSleep(1.5);
            PopStatusText();
            wxFindReplaceDialog* find = new wxFindReplaceDialog(this, findData, wxT("Find dialog"), wxFR_MATCHCASE);
            find->Show(true);

            //status:
            PushStatusText(wxT("Status: Finding words"));
            wxSleep(1.5);
            PopStatusText();
    }

    void OnEditReplace(wxCommandEvent& event) {
        wxFindReplaceData* findData = new wxFindReplaceData();
        PushStatusText(wxT("Status: Replace"));
        wxSleep(1.5);
        PopStatusText();
        wxFindReplaceDialog* replace = new wxFindReplaceDialog(this, findData, wxT("Find and Replace Dialog"), wxFR_REPLACEDIALOG | wxFR_NOWHOLEWORD);
        replace->Show(true);

        //status:
        PushStatusText(wxT("Status: Replacing words"));
        wxSleep(1.5);
        PopStatusText();
    }

    void OnEditGoto(wxCommandEvent& event) {
        PushStatusText(wxT("Status: Go to"));
        wxSleep(1.5);
        PopStatusText();
        long lineNumber = wxGetNumberFromUser(wxT(""), wxT(""), wxT("Go to the following line"), 1, 0, 100000, this); //moze se koristiti i int, ali XYToPosition zahtijeva long tip podatka
        if (lineNumber >= 0)
        {
            text->SetInsertionPoint(text->XYToPosition(0, lineNumber)); 

            //status:
            PushStatusText(wxT("Status: Go to line number: ") + std::to_string(lineNumber));
            wxSleep(1.5);
            PopStatusText();
        }
    }

    void OnEditSelectAll(wxCommandEvent& event) {

        //status:
        PushStatusText(wxT("Status: Select all"));
        wxSleep(1.5);
        PopStatusText();
        text->SelectAll();
    }

    void OnEditTimeDate(wxCommandEvent& event) {
        long from, to;
        text->GetSelection(&from, &to);
        wxDateTime* dateAndTime = new wxDateTime();
        dateAndTime->SetToCurrent();
        text->Replace(from, to, dateAndTime->Format());

        //status:
        PushStatusText(wxT("Status: Current time and date: " + dateAndTime->Format()));
        wxSleep(1.5);
        PopStatusText();
    }

    void OnFormatAutoLine(wxCommandEvent& event) {
        long flag = text->GetWindowStyle();
        flag = wxHSCROLL;
        text->SetWindowStyle(flag);
        
        //status:
        PushStatusText(wxT("Status: Setting text into one line..."));
        wxSleep(1.5);
        PopStatusText();

        wxTextCtrl* textNew = new wxTextCtrl(this, wxID_ANY, text->GetValue(), wxPoint(0, 0), text->GetSize(), flag | wxTE_MULTILINE);
        text->Destroy();
        text = textNew;
        textNew->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

        int w, h;
        GetVirtualSize(&w, &h);
        SetVirtualSize(w, h + 200);
        wxSize sz = GetSize();
        sz.SetHeight(sz.GetHeight() - 1);
        this->SetSize(sz);
        sz.SetHeight(sz.GetHeight() + 1);
        SetSize(sz);
    }

    void OnFormatWordWrap(wxCommandEvent& event) {
        wxTextCtrl* textNew = new wxTextCtrl(this, wxID_ANY, text->GetValue(), wxPoint(0, 0), text->GetSize(), wxTE_PROCESS_ENTER | wxTE_MULTILINE);
        text->Destroy();
        text = textNew;
        textNew->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString));

        wxSize sz = this->GetSize();
        sz.SetHeight(sz.GetHeight() - 1);
        this->SetSize(sz);
        sz.SetHeight(sz.GetHeight() + 1);
        this->SetSize(sz);

        //status:
        PushStatusText(wxT("Status: Word wrap"));
        wxSleep(1.5);
        PopStatusText();
    }

    void OnFormatFont(wxCommandEvent& event) {
        //status:
        PushStatusText(wxT("Status: Format font"));
        wxSleep(1.5);
        PopStatusText();

        wxFontDialog* fontDialog = new wxFontDialog(this);
        fontDialog->ShowModal();

        //status:
        PushStatusText(wxT("Status: Font is formated..."));
        wxSleep(1.5);
        PopStatusText();
    }

    void OnViewStatBar(wxCommandEvent& event) {
        if (this->GetStatusBar()->IsShown())
        {
            //status: 
            PushStatusText(wxT("Status: Hide status bar"));
            wxSleep(1.5);
            PopStatusText();

            this->GetStatusBar()->Hide();
            isStatusShow = false;
        }
        else
        {
            this->GetStatusBar()->Show();
            isStatusShow = true;

            //status: 
            PushStatusText(wxT("Status: Show status bar"));
            wxSleep(1.5);
            PopStatusText();
        }
        wxSize sz = this->GetSize();
        sz.SetHeight(sz.GetHeight() - 1);
        this->SetSize(sz);
        sz.SetHeight(sz.GetHeight() + 1);
        this->SetSize(sz);
    }

    void OnHelpAbout(wxCommandEvent& event) {
        wxAboutDialogInfo info;  
        info.SetName("Oiri Notepad");
        info.SetVersion("1.1");
        info.SetDescription("Example of implementing the Notepad using wxWidgets library");
        info.SetCopyright("(C) ajanach (2022.)");
        info.AddDeveloper("Antonio Janach");
        wxAboutBox(info, this);
    }

    void OnUpdateUIUndo(wxUpdateUIEvent& event) {
        event.Enable(text->CanUndo());
    }

    void OnUpdateUICut(wxUpdateUIEvent& event) {
        event.Enable(text->CanCut());
    }

    void OnUpdateUICopy(wxUpdateUIEvent& event) {
        event.Enable(text->CanCopy());
    }

    void OnUpdateUIPaste(wxUpdateUIEvent& event) {
        event.Enable(text->CanPaste());
    }

    void OnPowerShell(wxCommandEvent& event) {
        //wxShell("powershell New-Item -Path C:\\Users\\Antonio\\Desktop\\Test.txt");
        //wxExecute("powershell.exe New-Item -Path C:\\Users\\Antonio\\Desktop\\Test.txt", wxEXEC_ASYNC, NULL, NULL);
        //wxExecute("PowerShell -ExecutionPolicy bypass .\\Test.ps1 - windowstyle hidden", wxEXEC_ASYNC, NULL, NULL);
        wxExecute("powershell start -process powershell -ArgumentList \" -file .test.ps1\"", wxEXEC_ASYNC, NULL, NULL);

    }

    enum MenuControls {
        idFileNew = 1000,
        idFileNewWindow = 1001,
        idFileSave = 1002,
        idFileSaveAs = 1003,
        idFilePageSetup = 1004,
        idFilePrint = 1005,
        idEditUndo = 1006,
        idEditCut = 1007,
        idEditCopy = 1008,
        idEditPaste = 1009,
        idEditDelete = 1010,
        idEditFind = 1011,
        idEditReplace = 1012,
        idEditGoto = 1013,
        idEditSelectAll = 1014,
        idEditTimeDate = 1015,
        idFormatAutoLine = 1016,
        idFormatWordWrap = 1017,
        idFormatFont = 1018,
        idViewStatBar = 1019,
        idHelpAbout = 1020,
        idFileOpen = 1021, 
        idFileExit = 1022,
        idPS = 1023
    };

    DECLARE_EVENT_TABLE()
};

class MainApp : public wxApp {
public:
    virtual bool OnInit() {
        Notepad* main = new Notepad();
        main->Show(true);
        return true;
    }
};

BEGIN_EVENT_TABLE(Notepad, wxFrame) //početak event tablice za Notepad klasu:
//Kartica file:
EVT_MENU(idFileNew, Notepad::OnFileNew)
EVT_MENU(idFileNewWindow, Notepad::OnFileNewWindow)
EVT_MENU(idFileOpen, Notepad::OnFileOpen) 
EVT_MENU(idFileSave, Notepad::OnFileSave)
EVT_MENU(idFileSaveAs, Notepad::OnFileSaveAs)
EVT_MENU(idFilePageSetup, Notepad::OnFilePageSetup)
EVT_MENU(idFilePrint, Notepad::OnFilePrint)
EVT_MENU(idFileExit, Notepad::OnFileExit)

//kartica edit:
EVT_MENU(idEditUndo, Notepad::OnEditUndo)
EVT_MENU(idEditCut, Notepad::OnEditCut)
EVT_MENU(idEditCopy, Notepad::OnEditCopy)
EVT_MENU(idEditPaste, Notepad::OnEditPaste)
EVT_MENU(idEditDelete, Notepad::OnEditDelete)
EVT_MENU(idEditFind, Notepad::OnEditFind)
EVT_MENU(idEditReplace, Notepad::OnEditReplace)
EVT_MENU(idEditGoto, Notepad::OnEditGoto)
EVT_MENU(idEditSelectAll, Notepad::OnEditSelectAll)
EVT_MENU(idEditTimeDate, Notepad::OnEditTimeDate)

//kartica format:
EVT_MENU(idFormatAutoLine, Notepad::OnFormatAutoLine)
EVT_MENU(idFormatWordWrap, Notepad::OnFormatWordWrap)
EVT_MENU(idFormatFont, Notepad::OnFormatFont)

//kartica view:
EVT_MENU(idViewStatBar, Notepad::OnViewStatBar)

//kartica about:
EVT_MENU(idHelpAbout, Notepad::OnHelpAbout)

EVT_MENU(idPS, Notepad::OnPowerShell)

//event na klik X gumba okvira:
EVT_CLOSE(Notepad::OnXButton)

//wxUpdateUIEvent:
EVT_UPDATE_UI(idEditUndo, Notepad::OnUpdateUIUndo)
EVT_UPDATE_UI(idEditCut, Notepad::OnUpdateUICut)
EVT_UPDATE_UI(idEditCopy, Notepad::OnUpdateUICopy)
EVT_UPDATE_UI(idEditPaste, Notepad::OnUpdateUIPaste)

END_EVENT_TABLE() // kraj event tablice

//implementacija glavnog programa:
IMPLEMENT_APP(MainApp)
