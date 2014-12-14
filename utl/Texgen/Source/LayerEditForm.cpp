//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "LayerEditForm.h"
#include "Unit1.h"
#include <sysutils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTexLayerEditForm *TexLayerEditForm;
//---------------------------------------------------------------------------
__fastcall TTexLayerEditForm::TTexLayerEditForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void
TTexLayerEditForm::LoadFromLayer(TexLayer * layer)
{
// name
clayer = layer;
this->NameEdit->Text = layer->name;

if (layer->filename != "none")
        this->OpenTextureDlg->FileName = layer->filename;

// texture
this->TextureImage->Visible = false;
if (layer->Texture != NULL)
        {
        this->TextureImage->Picture->Bitmap->Assign(layer->Texture);
        this->TextureImage->Visible = true;
        }

// altitude parameters

altmin->Text  = FloatToStrF(layer->altitude_min,ffGeneral,3,1);
altmax->Text  = FloatToStrF(layer->altitude_max,ffGeneral,3,1);
altminv->Text = FloatToStrF(layer->altitude_min_blend,ffGeneral,3,1);
altmaxv->Text = FloatToStrF(layer->altitude_max_blend,ffGeneral,3,1);

// slope parameters
slopemin->Text  = FloatToStrF(layer->slope_min,ffGeneral,3,1);
slopemax->Text  = FloatToStrF(layer->slope_max,ffGeneral,3,1);
slopeminv->Text = FloatToStrF(layer->slope_min_blend,ffGeneral,3,1);
slopemaxv->Text = FloatToStrF(layer->slope_max_blend,ffGeneral,3,1);
}

void
TTexLayerEditForm::SaveToLayer(TexLayer * layer)
{
// name
layer->name = NameEdit->Text;

// filename
layer->filename = OpenTextureDlg->FileName;

// texture
if (TextureImage->Visible)
        {
        if (layer->Texture == NULL) layer->Texture = new Graphics::TBitmap;
        layer->Texture->Assign(TextureImage->Picture->Bitmap);
        }
// altitude parameters
try
        {
        layer->altitude_min       = StrToFloat(altmin->Text);
        layer->altitude_max       = StrToFloat(altmax->Text);
        layer->altitude_min_blend = StrToFloat(altminv->Text);
        layer->altitude_max_blend = StrToFloat(altmaxv->Text);
        }
        catch(EConvertError&) {};

// slope parameters
try
        {
        layer->slope_min       = StrToFloat(slopemin->Text);
        layer->slope_max       = StrToFloat(slopemax->Text);
        layer->slope_min_blend = StrToFloat(slopeminv->Text);
        layer->slope_max_blend = StrToFloat(slopemaxv->Text);
        }
        catch(EConvertError&) {};
}

void __fastcall TTexLayerEditForm::Button2Click(TObject *Sender)
{
SaveToLayer(clayer);
clayer = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TTexLayerEditForm::Button1Click(TObject *Sender)
{
if (OpenTextureDlg->Execute())
        {
        TextureImage->Picture->LoadFromFile(OpenTextureDlg->FileName);
        TextureImage->Visible = true;
        }
}
//---------------------------------------------------------------------------

