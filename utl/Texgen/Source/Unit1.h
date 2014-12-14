//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <graphics.hpp>
#include <inifiles.hpp>
#include "fxVector.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TPageControl *PageControl;
        TTabSheet *HeighmapTab;
        TTabSheet *TexLayersTab;
        TPanel *HeightmapPanel;
        TTabSheet *OptionsTab;
        TImage *HeightmapImage;
        TButton *LoadHeightmapButton;
        TPanel *TexLayersPanel;
        TTreeView *TexLayerView;
        TButton *AddLayerButton;
        TButton *DeleteLayerButton;
        TOpenPictureDialog *OpenHeightmapDlg;
        TButton *Button1;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *Load;
        TMenuItem *Save2;
        TMenuItem *N1;
        TMenuItem *Exit1;
        TTabSheet *OutputTab;
        TPanel *OutputPanel;
        TImage *OutputImage;
        TButton *GenerateOutputButton;
        TGroupBox *GroupBox1;
        TComboBox *TexSizeCombo;
        TButton *PreviewBtn;
        TButton *SaveTextureBtn;
        TSaveDialog *SaveScriptDlg;
        TOpenDialog *OpenScriptDlg;
        TSavePictureDialog *SaveTextureDlg;
        TOpenDialog *LocateGfxDlg;
        TGroupBox *GroupBox2;
        TTrackBar *SlopeThresh;
        TGroupBox *LightGroup;
        TCheckBox *LightCheck;
        TEdit *Lightx;
        TLabel *Label1;
        TEdit *Lighty;
        TEdit *Lightz;
        TLabel *Label2;
        TTrackBar *LightInfluence;
        void __fastcall LoadHeightmapButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall AddLayerButtonClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Save2Click(TObject *Sender);
        void __fastcall LoadClick(TObject *Sender);
        void __fastcall New1Click(TObject *Sender);
        void __fastcall GenerateOutputButtonClick(TObject *Sender);
        void __fastcall SaveTextureBtnClick(TObject *Sender);
        void __fastcall PreviewBtnClick(TObject *Sender);
        void __fastcall DeleteLayerButtonClick(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall LightCheckClick(TObject *Sender);
        void __fastcall LightChange(TObject *Sender);
private:	// Anwenderdeklarationen

        bool            Heightmap_loaded;
        AnsiString      Heightmap_filename;
        TList * LayerList;

        AnsiString      gfxserv_path;

        bool            Texture_generated;

        float GetAltitude(Graphics::TBitmap * bmp, float x, float y);
        float GetSlope(Graphics::TBitmap * bmp, float x, float y);

        float GetAltitudeInterpolated(Graphics::TBitmap * bmp, float x, float y);
        float GetSlopeInterpolated(Graphics::TBitmap * bmp, float x, float y);

        fxVector        light;
        fxVector        cnormal;

        int GetRed(TColor c);
        int GetGreen(TColor c);
        int GetBlue(TColor c);
        int MakeColor(int r, int g, int b);
        int GetLuminance (TColor c);


public:		// Anwenderdeklarationen
        __fastcall TMainForm(TComponent* Owner);
};

class TexLayer
        {
        public:
                Graphics::TBitmap * Texture;

                AnsiString name;
                AnsiString filename;

                float altitude_min; 
                float altitude_max;
                float altitude_min_blend;
                float altitude_max_blend;

                float slope_min;
                float slope_max;
                float slope_min_blend;
                float slope_max_blend;

                void LoadFromFile(TIniFile * file, AnsiString section);
                void WriteToFile(TIniFile * file, AnsiString section);
        };

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
