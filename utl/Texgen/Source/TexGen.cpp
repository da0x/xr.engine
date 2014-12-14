//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("TexGen.res");
USEFORM("Unit1.cpp", MainForm);
USEFORM("LayerEditForm.cpp", TexLayerEditForm);
USEUNIT("fxVector.cpp");
USEUNIT("fxTexture.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TTexLayerEditForm), &TexLayerEditForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
