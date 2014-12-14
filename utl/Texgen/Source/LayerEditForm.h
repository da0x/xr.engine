//---------------------------------------------------------------------------
#ifndef LayerEditFormH
#define LayerEditFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TexLayer;

class TTexLayerEditForm : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPanel *Panel1;
        TImage *TextureImage;
        TButton *Button1;
        TEdit *NameEdit;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *altmin;
        TEdit *altmax;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *altminv;
        TEdit *altmaxv;
        TGroupBox *GroupBox2;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TEdit *slopemin;
        TEdit *slopemax;
        TEdit *slopeminv;
        TEdit *slopemaxv;
        TButton *Button2;
        TButton *Button3;
        TOpenPictureDialog *OpenTextureDlg;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// Anwenderdeklarationen

        TexLayer * clayer;

public:		// Anwenderdeklarationen
        __fastcall TTexLayerEditForm(TComponent* Owner);

        void LoadFromLayer(TexLayer * layer);
        void SaveToLayer(TexLayer * layer);
};
//---------------------------------------------------------------------------
extern PACKAGE TTexLayerEditForm *TexLayerEditForm;
//---------------------------------------------------------------------------
#endif
