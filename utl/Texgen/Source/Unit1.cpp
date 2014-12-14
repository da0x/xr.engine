//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "LayerEditForm.h"
#include "fxVector.h"
#include <math.hpp>
#include <math.h>
#include <process.h>
#include <dir.h>

#include "fxTexture.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LoadHeightmapButtonClick(TObject *Sender)
{
if (this->OpenHeightmapDlg->Execute())
        {
        this->HeightmapImage->Picture->LoadFromFile(this->OpenHeightmapDlg->FileName);
        Heightmap_loaded = true;
        Heightmap_filename = OpenHeightmapDlg->FileName;
        HeightmapImage->Visible = true;
        }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
light.Set(0,1,0);
DecimalSeparator = '.';
Heightmap_loaded = false;
LayerList = new TList;
TexSizeCombo->ItemIndex = 3;
Heightmap_filename = "none";

AnsiString path = ExtractFilePath(Application->ExeName);
AnsiString options_name = path+"texgen.cfg";

TIniFile * opt;
opt = new TIniFile(options_name);

gfxserv_path = opt->ReadString("options","gfxserv", "none");
delete opt;

Texture_generated = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
// save options
AnsiString path = ExtractFilePath(Application->ExeName);
AnsiString options_name = path+"texgen.cfg";

TIniFile * opt;
opt = new TIniFile(options_name);

opt->WriteString("options","gfxserv", gfxserv_path);
opt->UpdateFile();
delete opt;

for (int i=0; i < LayerList->Count; i++) delete (TexLayer*)LayerList->Items[i];
delete LayerList;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AddLayerButtonClick(TObject *Sender)
{
TexLayer * l;
l = new TexLayer;
l->name = "Layer";

// default to no altitude blending
l->altitude_min = 0.0F;
l->altitude_max = 1.0F;
l->altitude_min_blend = 1.0F;
l->altitude_max_blend = 1.0F;

// default to no slope blending
l->slope_min = 0.0F;
l->slope_max = 90.0F;
l->slope_min_blend = 1.0F;
l->slope_max_blend = 1.0F;

l->Texture = NULL;
l->filename = "none";

LayerList->Add(l);

TexLayerView->Selected = TexLayerView->Items->AddObject(NULL, "Layer", l);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
TexLayer * layer;
layer = (TexLayer*)TexLayerView->Selected->Data;
TexLayerEditForm->LoadFromLayer(layer);
if (TexLayerEditForm->ShowModal() == mrOk)
        {
        TexLayerView->Selected->Text = layer->name;
        }
}
//---------------------------------------------------------------------------

void TexLayer::LoadFromFile(TIniFile * file, AnsiString section)
{
this->name = file->ReadString(section, "name", "Layer");

// filename
this->filename = file->ReadString(section, "texture","none");
if (this->filename != "none")
        {
        this->Texture = new Graphics::TBitmap;
        try
                {
                this->Texture->LoadFromFile(this->filename);
                }
                catch (EFOpenError&)
                        {
                        delete this->Texture;
                        this->Texture = NULL;
                        Application->MessageBox("Texture file not found.", "Error", MB_OK);
                        }
                catch (EInvalidGraphic&)
                        {
                        delete this->Texture;
                        this->Texture = NULL;
                        Application->MessageBox("Invalid texture file.", "Error", MB_OK);
                        }
        }
        else
        {
        this->Texture = NULL;
        }
// altitude constraints
this->altitude_min = file->ReadFloat(section, "altitude_min", 0.0F);
this->altitude_max = file->ReadFloat(section, "altitude_max", 1.0F);
this->altitude_min_blend = file->ReadFloat(section, "altitude_min_blend", 1.0F);
this->altitude_max_blend = file->ReadFloat(section, "altitude_max_blend", 1.0F);

// slope constraints
this->slope_min = file->ReadFloat(section, "slope_min", 0.0F);
this->slope_max = file->ReadFloat(section, "slope_max", 90.0F);
this->slope_min_blend = file->ReadFloat(section, "slope_min_blend", 1.0F);
this->slope_max_blend = file->ReadFloat(section, "slope_max_blend", 1.0F);
}

void TexLayer::WriteToFile(TIniFile * file, AnsiString section)
{
file->WriteString(section, "name", this->name);

// filename
if (this->Texture == NULL)
        file->WriteString(section, "texture", "none");
else
        file->WriteString(section, "texture", this->filename);

// altitude constraints
file->WriteFloat(section, "altitude_min", this->altitude_min);
file->WriteFloat(section, "altitude_max", this->altitude_max);
file->WriteFloat(section, "altitude_min_blend", this->altitude_min_blend);
file->WriteFloat(section, "altitude_max_blend", this->altitude_max_blend);

// slope constraints
file->WriteFloat(section, "slope_min", this->slope_min);
file->WriteFloat(section, "slope_max", this->slope_max);
file->WriteFloat(section, "slope_min_blend", this->slope_min_blend);
file->WriteFloat(section, "slope_max_blend", this->slope_max_blend);
}

void __fastcall TMainForm::Save2Click(TObject *Sender)
{
if (SaveScriptDlg->Execute())
        {
        TIniFile * file;
        file = new TIniFile(SaveScriptDlg->FileName);

        // write options
        file->WriteString("options","heightmap", this->Heightmap_filename);
        file->WriteInteger("options", "TextureSize" ,TexSizeCombo->ItemIndex);

        file->WriteInteger("options", "SlopeThresh" ,SlopeThresh->Position);
        file->WriteBool("options", "EnableLighting" ,LightCheck->Checked);
        file->WriteFloat("options", "LightX" ,light.GetX());
        file->WriteFloat("options", "LightY" ,light.GetY());
        file->WriteFloat("options", "LightZ" ,light.GetZ());
        file->WriteInteger("options", "LightInfluence" ,LightInfluence->Position);

        // write the layers
        for (int i = 0; i<LayerList->Count; i++)
                {
                AnsiString SectionName("LAYER");
                SectionName += IntToStr(i);
                TexLayer * l = (TexLayer*)LayerList->Items[i];
                l->WriteToFile(file, SectionName);
                }

        file->UpdateFile();
        delete file;
        }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LoadClick(TObject *Sender)
{
if (OpenScriptDlg->Execute())
        {
        // delete everything
        this->New1Click(this);  

        TIniFile * file;
        file = new TIniFile(OpenScriptDlg->FileName);

        // read options
        AnsiString hm = file->ReadString("options","heightmap", "none");
        if (hm != "none")
                {
                try
                        {
                        this->HeightmapImage->Picture->LoadFromFile(hm);
                        Heightmap_loaded = true;
                        }
                        catch(EFOpenError&)
                                {
                                Heightmap_loaded = false;
                                Application->MessageBox("Cant find heightmap image!", "Error", MB_OK);
                                }
                        catch(EInvalidImage&)
                                {
                                Heightmap_loaded = false;
                                Application->MessageBox("Invalid heightmap image!", "Error", MB_OK);
                                }

                }
                else
                {
                Heightmap_loaded = false;
                }

        Heightmap_filename = hm;                
        HeightmapImage->Visible = Heightmap_loaded;

        TexSizeCombo->ItemIndex = file->ReadInteger("options", "TextureSize" ,3);

        SlopeThresh->Position = file->ReadInteger("options", "SlopeThresh" ,5);
        LightCheck->Checked = file->ReadBool("options", "EnableLighting" ,false);

        float x,y,z;

        x = file->ReadFloat("options", "LightX" ,0.0F);
        y = file->ReadFloat("options", "LightY" ,1.0F);
        z = file->ReadFloat("options", "LightZ" ,0.0F);

        light.Set(x,y,z);
        Lightx->Text = FloatToStr(x);
        Lighty->Text = FloatToStr(y);
        Lightz->Text = FloatToStr(z);

        LightInfluence->Position = file->ReadInteger("options", "LightInfluence" ,80);

        // read the layers
        TStringList * secs;
        secs = new TStringList;
        file->ReadSections(secs);

        for (int i = 0; i<secs->Count; i++)
                {
                if (secs->Strings[i] == "options") continue;
                TexLayer * l;
                l = new TexLayer;
                LayerList->Add(l);
                l->LoadFromFile(file, secs->Strings[i]);
                TexLayerView->Selected = TexLayerView->Items->AddObject(NULL, l->name, l);
                }
        delete secs;
        delete file;
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::New1Click(TObject *Sender)
{
for (int i=0; i < LayerList->Count; i++)
        {
        TexLayer * l = (TexLayer*)LayerList->Items[i];
        if (l->Texture) delete l->Texture;
        delete l;
        }
LayerList->Clear();
TexLayerView->Items->Clear();
if (Heightmap_loaded) this->HeightmapImage->Visible = false;
Heightmap_loaded = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GenerateOutputButtonClick(TObject *Sender)
{
// check if all layers have textures assigned
bool everything_ok = true;

for (int i=0; i < LayerList->Count; i++)
        if (((TexLayer *)LayerList->Items[i])->filename == "none")
                {
                Application->MessageBox("Not all layers have textures assigned!", "Error", MB_OK);
                everything_ok = false;
                }

// do we have a heightmap loaded?
if (everything_ok) everything_ok = Heightmap_loaded;

if (!everything_ok)
        {
        Application->MessageBox("No heightmap loaded!", "Error", MB_OK);
        return;
        }

// we now have verified that every layer has a texture and that a heightmap is
// loaded, so lets begin synthesizing the output texture

switch (TexSizeCombo->ItemIndex)
        {
        case 0:
                OutputImage->Picture->Bitmap->Width = 32;
                OutputImage->Picture->Bitmap->Height = 32;
                break;
        case 1:
                OutputImage->Picture->Bitmap->Width = 64;
                OutputImage->Picture->Bitmap->Height = 64;
                break;
        case 2:
                OutputImage->Picture->Bitmap->Width = 128;
                OutputImage->Picture->Bitmap->Height = 128;
                break;
        case 3:
                OutputImage->Picture->Bitmap->Width = 256;
                OutputImage->Picture->Bitmap->Height = 256;
                break;
        case 4:
                OutputImage->Picture->Bitmap->Width = 512;
                OutputImage->Picture->Bitmap->Height = 512;
                break;
        case 5:
                OutputImage->Picture->Bitmap->Width = 1024;
                OutputImage->Picture->Bitmap->Height = 1024;
                break;
        case 6:
                OutputImage->Picture->Bitmap->Width = 2048;
                OutputImage->Picture->Bitmap->Height = 2048;
                break;
        default:
                OutputImage->Picture->Bitmap->Width = 256;
                OutputImage->Picture->Bitmap->Height = 256;
                break;
        }

for (int y = 0; y < OutputImage->Picture->Bitmap->Height; y++)
        {
        for (int x = 0; x < OutputImage->Picture->Bitmap->Width; x++)
                {
                float rel_x = x / (float)OutputImage->Picture->Bitmap->Width;
                float rel_y = y / (float)OutputImage->Picture->Bitmap->Height;

                // get the altitude, ranges from 0.0 (ground) to 1.0 (mountains)
                float altitude  = GetAltitudeInterpolated(HeightmapImage->Picture->Bitmap, rel_x, rel_y);

                // get the slope, ranges from 0.0 (no slope) to 1.0 (straight up)
                float slope     = GetSlopeInterpolated(HeightmapImage->Picture->Bitmap, rel_x, rel_y);

                int num_layers = 0;
                TexLayer * valid_layers[64];

                // now find all the valid layers
                for (int i=0; i<LayerList->Count; i++)
                        {
                        TexLayer * l = (TexLayer*)LayerList->Items[i];
                        if ((altitude >= l->altitude_min) && (altitude <= l->altitude_max) &&
                            (slope >= l->slope_min) && (slope <= l->slope_max))
                                {
                                // this is a valid layer, add it to the list
                                valid_layers[num_layers] = l;
                                num_layers++;
                                }
                        }

                TColor color_array[64];
                float  weight_array[64];

                // valid_layers now contains a list of layers that contribute to that pixel
                // now blend them to get the final color
                for (int i=0; i < num_layers; i++)
                        {
                        // now get the blending weights for slope and altitude by interpolating
                        // min_blend + (blend_max - blend_min / max - min) * (p - min)

                        float alt_t = (valid_layers[i]->altitude_max_blend - valid_layers[i]->altitude_min_blend) /
                                      (valid_layers[i]->altitude_max - valid_layers[i]->altitude_min);

                        float slope_t = (valid_layers[i]->slope_max_blend - valid_layers[i]->slope_min_blend) /
                                        (valid_layers[i]->slope_max - valid_layers[i]->slope_min);

                        float altitude_weight = valid_layers[i]->altitude_min_blend + (alt_t * (altitude - valid_layers[i]->altitude_min));
                        float slope_weight = valid_layers[i]->slope_min_blend + (slope_t * (slope - valid_layers[i]->slope_min));

                        // now that we have the 2 weights, average them to get the final
                        // weight for that texture layer and save it into the weight_array
                        weight_array[i] = (altitude_weight + slope_weight) / 2;

                        // get the texture color and save it into the color array
                        int abs_x = int(valid_layers[i]->Texture->Width * rel_x);
                        int abs_y = int(valid_layers[i]->Texture->Height * rel_y);
                        color_array[i] = valid_layers[i]->Texture->Canvas->Pixels[abs_x][abs_y];
                        }

                // now blend all the values in color_array according to their weights in weight_array

                // first normalize the weights, so that their sum is exactly 1
                float total_weight = 0;
                for (int i=0; i<num_layers; i++) total_weight+=weight_array[i];
                if (total_weight == 0) total_weight = 1.0F;
                float weight_scale = 1 / total_weight;
                for (int i=0; i<num_layers; i++) weight_array[i] *= weight_scale;

                int red = 0;
                int green = 0;
                int blue = 0;

                for (int i=0; i<num_layers; i++)
                        {
                        red += int(GetRed(color_array[i]) * weight_array[i]);
                        green += int(GetGreen(color_array[i]) * weight_array[i]);
                        blue += int(GetBlue(color_array[i]) * weight_array[i]);
                        }

                // if lighting is enabled, compute a color scale factor for this pixel
                float cscale = 1.0F;
                float influence = 0.0F;
                if (LightCheck->Checked)
                        {
                        cscale = (cnormal.DotProduct(&light));
                        if (cscale < 0) cscale = 0;
                        if (cscale > 1) cscale = 1.0F;
                        influence = LightInfluence->Position / 100.0F;
                        }

                float cred    = (cscale*red*influence)+(red*(1-influence));
                float cgreen  = (cscale*green*influence)+(green*(1-influence));
                float cblue   = (cscale*blue*influence)+(blue*(1-influence));

                // we now have succesfully calculated one pixel, write it into the
                // output texture
                OutputImage->Picture->Bitmap->Canvas->Pixels[x][y] = MakeColor(cred, cgreen, cblue);
                }
        OutputImage->Repaint();
        }
Texture_generated = true;
}
//---------------------------------------------------------------------------
float TMainForm::GetAltitude(Graphics::TBitmap * bmp, float x, float y)
{
int r, g, b;
int abs_x = int(x * bmp->Width);
int abs_y = int(y * bmp->Height);
TColor c = bmp->Canvas->Pixels[abs_x][abs_y];
r = GetRed(c);
g = GetGreen(c);
b = GetBlue(c);

float luminance = (r + g + b) / 3.0F;
return (luminance / 255.0F);
}

float TMainForm::GetSlope(Graphics::TBitmap * bmp, float x, float y)
{
int abs_x = int(x * bmp->Width);
int abs_y = int(y * bmp->Height);

float dx, dy;

if ((abs_x > 0) && (abs_x < bmp->Width-1))
        {
        dx = GetLuminance(bmp->Canvas->Pixels[abs_x-1][abs_y]) -GetLuminance(bmp->Canvas->Pixels[abs_x+1][abs_y]);
        }
else if (abs_x > 0)
        {
        dx = 2.0F * GetLuminance(bmp->Canvas->Pixels[abs_x-1][abs_y]) - GetLuminance(bmp->Canvas->Pixels[abs_x][abs_y]);
        }
else
        {
        dx = 2.0F * GetLuminance(bmp->Canvas->Pixels[abs_x][abs_y]) - GetLuminance(bmp->Canvas->Pixels[abs_x+1][abs_y]);
        }

if ((abs_y > 0) && (abs_y < bmp->Height-1))
        {
        dy = GetLuminance(bmp->Canvas->Pixels[abs_x][abs_y-1]) - GetLuminance(bmp->Canvas->Pixels[abs_x][abs_y+1]);
        }
else if (abs_y > 0)
        {
        dy = 2.0F * GetLuminance(bmp->Canvas->Pixels[abs_x][abs_y-1]) - GetLuminance(bmp->Canvas->Pixels[abs_x][abs_y]);
        }
else
        {
        dy = 2.0F * GetLuminance(bmp->Canvas->Pixels[abs_x][abs_y]) - GetLuminance(bmp->Canvas->Pixels[abs_x][abs_y+1]);
        }

fxVector lr(SlopeThresh->Position, dx, 0);
fxVector ud(0, dy, SlopeThresh->Position);

fxVector * normal = lr.CrossProduct(&ud);
normal->Normalize();

cnormal.Set(normal->GetX(),normal->GetY(),normal->GetZ());

// 1 = 90°, 0 = 0°
float angle = (1-normal->DotProduct(0, -1, 0));

return (angle * 90);
}

float TMainForm::GetAltitudeInterpolated(Graphics::TBitmap * bmp, float x, float y)
{
int abs_x = int(x * bmp->Width);
int abs_y = int(y * bmp->Height);

// interpolate in x direction
float lx = abs_x / (float)bmp->Width;
float rx = (abs_x+1) / (float)bmp->Width;
if (rx > 1.0F) rx = 1.0F;

float weightx = (x-lx) * (1.0F / (rx-lx));

float lalt = GetAltitude(bmp, lx, y);
float ralt = GetAltitude(bmp, rx, y);

float altx = (1-weightx)*lalt + weightx*ralt;

// interpolate in y direction
float ly = abs_y / (float)bmp->Height;
float ry = (abs_y+1) / (float)bmp->Height;
if (ry > 1.0F) ry = 1.0F;

float weighty = (y-ly) * (1.0F / (ry-ly));

float lalty = GetAltitude(bmp, x, ly);
float ralty = GetAltitude(bmp, x, ry);

float alty = (1-weighty)*lalty + weighty*ralty;

// average results
return (altx+alty) / 2.0F;
}


float TMainForm::GetSlopeInterpolated(Graphics::TBitmap * bmp, float x, float y)
{
int abs_x = int(x * bmp->Width);
int abs_y = int(y * bmp->Height);

// interpolate in x direction
float lx = abs_x / (float)bmp->Width;
float rx = (abs_x+1) / (float)bmp->Width;
if (rx > 1.0F) rx = 1.0F;

float weightx = (x-lx) * (1.0F / (rx-lx));

float lalt = GetSlope(bmp, lx, y);
float ralt = GetSlope(bmp, rx, y);

float altx = (1-weightx)*lalt + weightx*ralt;

// interpolate in y direction
float ly = abs_y / (float)bmp->Height;
float ry = (abs_y+1) / (float)bmp->Height;
if (ry > 1.0F) ry = 1.0F;

float weighty = (y-ly) * (1.0F / (ry-ly));

float lalty = GetSlope(bmp, x, ly);
float ralty = GetSlope(bmp, x, ry);

float alty = (1-weighty)*lalty + weighty*ralty;

// average results
return (altx+alty) / 2.0F;
}

int TMainForm::GetRed(TColor c)
{
return (c & 0x000000ff);
}

int TMainForm::GetGreen(TColor c)
{
return ((c & 0x0000ff00) >> 8);
}

int TMainForm::GetBlue(TColor c)
{
return ((c & 0x00ff0000) >> 16);
}

int TMainForm::MakeColor(int r, int g, int b)
{
int t = 0;
t = b;
t <<= 8;
t |= g;
t<<=8;
t|=r;
return t;
}

int TMainForm::GetLuminance (TColor c)
{
float r = GetRed(c);
float g = GetGreen(c);
float b = GetBlue(c);
float erg = (r+g+b) / 3.0F;
return int(erg);
}

void __fastcall TMainForm::SaveTextureBtnClick(TObject *Sender)
{
if (!Texture_generated)
        {
        Application->MessageBox("Generate the texture first!", "Error", MB_OK);
        return;
        }

if (SaveTextureDlg->Execute())
        {
//        OutputImage->Picture->SaveToFile(SaveTextureDlg->FileName);

        fxTexture * tex;
        tex = new fxTexture;
        tex->LoadFromBmp(OutputImage->Picture->Bitmap);
        tex->SaveBMP(SaveTextureDlg->FileName.c_str(), NULL);
        delete tex;
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PreviewBtnClick(TObject *Sender)
{
if (!Heightmap_loaded)
        {
        Application->MessageBox("No heightmap loaded!", "Error", MB_OK);
        return;
        }

if (!Texture_generated)
        {
        Application->MessageBox("Generate the output texture first!", "Error", MB_OK);
        return;
        }

AnsiString path = ExtractFilePath(Application->ExeName);
AnsiString template_name = path+"template.n";

AnsiString height_file = path+"heightmap.bmp";
AnsiString output_file = path+"texture.bmp";

//HeightmapImage->Picture->Bitmap->SaveToFile(height_file);
//OutputImage->Picture->Bitmap->SaveToFile(output_file);

fxTexture * tex;

tex = new fxTexture;
tex->LoadFromBmp(OutputImage->Picture->Bitmap);
tex->SaveBMP(output_file.c_str(), NULL);
delete tex;

tex = new fxTexture;
tex->LoadFromBmp(HeightmapImage->Picture->Bitmap);
tex->SaveBMP(height_file.c_str(), NULL);
delete tex;


if ((gfxserv_path == "none") || (!FileExists(gfxserv_path)))
        {
        if (LocateGfxDlg->Execute())
                {
                gfxserv_path = LocateGfxDlg->FileName;
                chdir(path.c_str());
                spawnlp(P_WAIT, gfxserv_path.c_str(), gfxserv_path.c_str(), "-startup", template_name.c_str(),"-nogrid", NULL);
                }
        }
        else
        {
        chdir(path.c_str());
        spawnlp(P_WAIT, gfxserv_path.c_str(), gfxserv_path.c_str(), "-startup", template_name.c_str(),"-nogrid", NULL);
        }


}

//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteLayerButtonClick(TObject *Sender)
{
if (!this->TexLayerView->Selected) return;

TexLayer * l = (TexLayer*)this->TexLayerView->Selected->Data;
LayerList->Remove(l);
this->TexLayerView->Items->Delete(this->TexLayerView->Selected);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::LightCheckClick(TObject *Sender)
{
LightGroup->Enabled = LightCheck->Checked;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LightChange(TObject *Sender)
{
float x,y,z;

try
        {
        x = StrToFloat(Lightx->Text);
        }
        catch(EConvertError&)
                {
                x = 0;
                }

try
        {
        y = StrToFloat(Lighty->Text);
        }
        catch(EConvertError&)
                {
                y = 1;
                }

try
        {
        z = StrToFloat(Lightz->Text);
        }
        catch(EConvertError&)
                {
                z = 0;
                }
light.Set(x,y,z);
}
//---------------------------------------------------------------------------



