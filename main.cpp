#include <wx/wx.h>

#include <locale.h>

class MainFrame : public wxFrame {
public:
    MainFrame() : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8("Офисная утилита"), wxDefaultPosition, wxSize(600, 400)) {
		// setlocale(LC_CTYPE, "ru_RU.UTF-8");
        auto* panel = new wxPanel(this);
        auto* sizer = new wxBoxSizer(wxVERTICAL);

        auto* btn = new wxButton(panel, wxID_ANY, wxString::FromUTF8("Нажми меня"));
        btn->Bind(wxEVT_BUTTON, [](wxCommandEvent&) {
            wxMessageBox(wxString::FromUTF8("Работает на чистом C++!"), wxString::FromUTF8("Инфо"), wxOK | wxICON_INFORMATION);
        });

        sizer->Add(btn, 0, wxALL | wxCENTER, 20);
        panel->SetSizer(sizer);
        Centre();
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() override {
        auto* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);