//---------------------------------*-C++-*-----------------------------------//
/*!
 * \file   rootlogon.C
 * \author Stefano Tognini
 * \brief  Standard plot style for the Celeritas Project.
 * \note   Copyright (c) 2020 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
/*!
 * To set this as default:
 * Create a .rootrc file in your home directory and add the following line:
 * Rint.Logon: /path/to/rootlogon.C
 *
 * To load this only inside a specific folder:
 * Simply copy this file to the folder you are running your ROOT macros.
 */
//---------------------------------------------------------------------------//


#include "TStyle.h"
#include "TROOT.h"
#include "TColor.h"
#include "TLatex.h"
#include "TH1.h"
#include "TH2.h"


void rootlogon()
{
    printf("Welcome to the ROOT of all evils\n");
    
    
    // Creating the style
    TStyle* celeritasStyle = new TStyle("CeleritasStyle", "Celeritas Project Style");
    
    
    // Removing the colored frame around the plots
    celeritasStyle->SetFrameBorderMode(0);
    celeritasStyle->SetCanvasBorderMode(0);
    celeritasStyle->SetPadBorderMode(0);
    
    // Setting the background color to white
    celeritasStyle->SetFillColor(10);
    celeritasStyle->SetFrameFillColor(10);
    celeritasStyle->SetCanvasColor(10);
    celeritasStyle->SetPadColor(10);
    celeritasStyle->SetTitleFillColor(0);
    celeritasStyle->SetStatColor(10);
    
    // Hidding the histogram info box
    celeritasStyle->SetOptStat(0);
    
    // Using thicker lines
    celeritasStyle->SetHistLineWidth(2);
    celeritasStyle->SetFrameLineWidth(2);
    celeritasStyle->SetFuncWidth(2);
    
    // Setting the number of tick marks to show on axes
    celeritasStyle->SetNdivisions(506, "xyz");
    
    // Adding tick lines on all sides of the plot
    celeritasStyle->SetPadTickX(1);
    celeritasStyle->SetPadTickY(1);
    
    // Using the same font on all elements in the plot
    const int kCeleritasFont = 42;
    celeritasStyle->SetLabelFont(kCeleritasFont, "xyz"); // Labels/numbers
    celeritasStyle->SetTitleFont(kCeleritasFont, "xyz"); // Axes titles
    celeritasStyle->SetTitleFont(kCeleritasFont, "");    // Plot title
    celeritasStyle->SetTextFont(kCeleritasFont);         // Text
    celeritasStyle->SetLegendFont(kCeleritasFont);       // Legend
    
    // Setting axis title sizes
    celeritasStyle->SetTitleSize(.055, "xyz");
    
    // Increasing axis offset to avoid clashing with big numbers
    celeritasStyle->SetTitleOffset(.8, "x");
    celeritasStyle->SetTitleOffset(.9, "y");
    celeritasStyle->SetTitleOffset(.8, "z");
    
    // Applying the same distance settings to plot titles
    celeritasStyle->SetTitleSize(.055, "");
    celeritasStyle->SetTitleOffset(.8, "");
    
    // Defining axes labels' (numbering) size and offset
    celeritasStyle->SetLabelSize(.04, "xyz");
    celeritasStyle->SetLabelOffset(.005, "xyz");
    
    // Centering titles
    celeritasStyle->SetTitleAlign(22);
    celeritasStyle->SetTitleX(.5);
    celeritasStyle->SetTitleY(.95);
    celeritasStyle->SetTitleBorderSize(0);
    
    // Removing borders on legengs
    celeritasStyle->SetLegendBorderSize(0);
    
    // Preventing ROOT from occasionally suppressing the zero
    celeritasStyle->SetHistMinimumZero();
    
    // Setting the default marker as a circle
    celeritasStyle->SetMarkerStyle(kFullCircle);
    
    // Setting the default line color for a fit function as red
    celeritasStyle->SetFuncColor(kRed);
    
    // Setting automatic scientific notation on axes with large numbers
    TGaxis::SetMaxDigits(3);
    
    // Setting the standard color palette to be the rainbow palette
    const Int_t nRGB = 5;
    const Int_t nContours = 255;
    Double_t stops[nRGB] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[nRGB]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[nRGB] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[nRGB]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
   
    celeritasStyle->SetNumberContours(nContours);
    
    // Applying all the settings
    gROOT->SetStyle("CeleritasStyle");

    // Uncomment this to force all plots loaded from files to use this style
    //gROOT->ForceStyle();
}




//---------------------------------------------------------------------------//
//                             Useful functions
//---------------------------------------------------------------------------//
/*!
 *  These are functions designed to speed up the writting of ROOT plot macros.
 *  Feel free to extend this list. Remember to list any new functions in the
 *  help() command as well.
 */
//---------------------------------------------------------------------------//


//-------------------------------- Plot title -------------------------------//
void SetPlotTitle(const char* title)
{
    TLatex* myTitle = new TLatex(0.1, 0.95, title);
    myTitle->SetTextColor(1);
    myTitle->SetNDC();
    myTitle->SetTextSize(2/30.);
    myTitle->SetTextAlign(12);
    myTitle->Draw();
}

void SetPlotTitle(const char* title, double x_position)
{
    TLatex* myTitle = new TLatex(x_position, 0.95, title);
    myTitle->SetTextColor(1);
    myTitle->SetNDC();
    myTitle->SetTextSize(2/30.);
    myTitle->SetTextAlign(12);
    myTitle->Draw();
}


//------------------------------- Axes titles -------------------------------//
void SetAxesTitles(TH1* histogram, const char* titleX)
{
    histogram->GetXaxis()->SetTitle(titleX);
    histogram->GetXaxis()->CenterTitle();
}

void SetAxesTitles(TH1* histogram, const char* titleX, const char* titleY)
{
    histogram->GetXaxis()->SetTitle(titleX);
    histogram->GetXaxis()->CenterTitle();
    histogram->GetYaxis()->SetTitle(titleY);
    histogram->GetYaxis()->CenterTitle();
}

void CenterTitles(TH1* histogram)
{
    histogram->GetXaxis()->CenterTitle();
    histogram->GetYaxis()->CenterTitle();
    histogram->GetZaxis()->CenterTitle();
}


//----------------------------- Color palettes ------------------------------//
void RainbowPalette()
{
    const Int_t nRGB = 5;
    const Int_t nContours = 255;
    Double_t stops[nRGB] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[nRGB]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[nRGB] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[nRGB]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

void SunsetPalette()
{
    const Int_t nRGB = 5;
    const Int_t nContours = 255;
    Double_t stops[nRGB] = { 0.00, 0.20, 0.50, 0.75, 1.00 };
    Double_t red[nRGB]   = { 1.00, 1.00, 1.00, 0.60, 0.00 };
    Double_t green[nRGB] = { 1.00, 1.00, 0.50, 0.00, 0.00 };
    Double_t blue[nRGB]  = { 0.90, 0.00, 0.00, 0.00, 0.00 };
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

void SunsetPalette2()
{
    const Int_t nRGB = 7;
    const Int_t nContours = 255;
    Double_t stops[nRGB] = { 0.00, 0.10, 0.20, 0.40, 0.70, 0.85, 1.00 };
    Double_t red[nRGB]   = { 0.20, 0.60, 0.80, 1.00, 0.81, 0.00, 0.05 };
    Double_t green[nRGB] = { 0.00, 0.00, 0.00, 1.00, 0.95, 0.50, 0.05 };
    Double_t blue[nRGB]  = { 0.00, 0.00, 0.00, 0.00, 1.00, 1.00, 0.30 };
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

void BluePalette()
{
    const Int_t nRGB = 5;
    const Int_t nContours = 255;
    Double_t stops[nRGB] = { 0.00, 0.20, 0.50, 0.75, 1.00 };
    Double_t red[nRGB]   = { 1.00, 0.80, 0.00, 0.00, 0.00 };
    Double_t green[nRGB] = { 1.00, 0.90, 0.50, 0.20, 0.01 };
    Double_t blue[nRGB]  = { 1.00, 1.00, 1.00, 0.40, 0.10 };
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

void GreenToRedPalette()
{
    const Int_t nRGB = 6;
    const Int_t nContours = 255;
    Double_t stops[nRGB] = { 0.00, 0.10, 0.47, 0.53, 0.90, 1.00 };
    Double_t red[nRGB]   = { 0.00, 0.00, 1.00, 1.00, 1.00, 0.65 };
    Double_t green[nRGB] = { 0.65, 1.00, 1.00, 1.00, 0.00, 0.00 };
    Double_t blue[nRGB]  = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 };
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

void GrayPalette()
{
    const Int_t nRGB = 5;
    const Int_t nContours = 255;
    Double_t stops[nRGB] = { 0.00, 0.25, 0.50, 0.75, 1.00 };
    Double_t red[nRGB]   = { 1.00, 0.75, 0.50, 0.25, 0.00 };
    Double_t green[nRGB] = { 1.00, 0.75, 0.50, 0.25, 0.00 };
    Double_t blue[nRGB]  = { 1.00, 0.75, 0.50, 0.25, 0.00 };
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

void GrayPalette2()
{
    const Int_t nRGB = 5;
    const Int_t nContours = 255;
    Double_t stops[nRGB] = { 0.00, 0.25, 0.50, 0.75, 1.00 };
    Double_t red[nRGB]   = { 0.00, 0.25, 0.50, 0.75, 1.00 };
    Double_t green[nRGB] = { 0.00, 0.25, 0.50, 0.75, 1.00 };
    Double_t blue[nRGB]  = { 0.00, 0.25, 0.50, 0.75, 1.00 };
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

/*!
 * Standard options for n are: 0, 29, 50, 51, 53, 54, 56, 93, 97, 107, or 112
 */
void SetStandardPalette(const Int_t n)
{
    TStyle* celeritasStyle = new TStyle("", "");
    celeritasStyle->SetPalette(n);
}


//---------------------------- Preliminary tags -----------------------------//
//
// Adds either a "Preliminary" or a "Celeritas Preliminary" at the top right
// corner of the plot
//

// Horizontal
void Preliminary()
{
    TLatex* prelim = new TLatex(.9, .95, "Preliminary");
    prelim->SetTextColor(38);
    prelim->SetNDC();
    prelim->SetTextSize(2/30.);
    prelim->SetTextAlign(32);
    prelim->Draw();
}

// Vertical
void PreliminarySide()
{
    TLatex* prelim = new TLatex(.93, .9, "Preliminary");
    prelim->SetTextColor(38);
    prelim->SetNDC();
    prelim->SetTextSize(2/30.);
    prelim->SetTextAngle(270);
    prelim->SetTextAlign(12);
    prelim->Draw();
}

// Horizontal
void CPreliminary()
{
    TLatex* prelim = new TLatex(.9, .95, "Celeritas Preliminary");
    prelim->SetTextColor(38);
    prelim->SetNDC();
    prelim->SetTextSize(2/30.);
    prelim->SetTextAlign(32);
    prelim->Draw();
}

// Vertical
void CPreliminarySide()
{
    TLatex* prelim = new TLatex(.93, .9, "Celeritas Preliminary");
    prelim->SetTextColor(38);
    prelim->SetNDC();
    prelim->SetTextSize(2/30.);
    prelim->SetTextAngle(270);
    prelim->SetTextAlign(12);
    prelim->Draw();
}


//------------------------- Miscellaneous functions -------------------------//
//
// EMPTY
//


//---------------------------------- HELP -----------------------------------//
void help()
{
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "        Celeritas rootlogon.C functions        " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << std::endl;
    
    std::cout << "------------------ Plot Title -----------------" << std::endl;
    std::cout << "SetPlotTitle(const char* title)" << std::endl;
    std::cout << "SetPlotTitle(const char* title, double x_position)" <<
    std::endl;
    std::cout << "SetPlotTitle(const char* title, double x_position)" <<
    std::endl;
    std::cout << std::endl;
    
    std::cout << "------------------ Axes Titles ----------------" << std::endl;
    std::cout << "SetAxesTitles(TH1* histogram, const char* titleX)" <<
    std::endl;
    std::cout << "SetAxesTitles(TH1* histogram, const char* titleX, const char* titleY)" <<
    std::endl;
    std::cout << "CenterTitles(TH1* histogram)" << std::endl;
    std::cout << std::endl;
    
    std::cout << "--------------- Preliminary tags --------------" << std::endl;
    std::cout << "Preliminary()" << std::endl;
    std::cout << "PreliminarySide()" << std::endl;
    std::cout << "CPreliminary()" << std::endl;
    std::cout << "CPreliminarySide()" << std::endl;
    std::cout << std::endl;
    
    std::cout << "---------------- Color palettes ---------------" << std::endl;
    std::cout << "RainbowPalette()" << std::endl;
    std::cout << "SunsetPalette()" << std::endl;
    std::cout << "SunsetPalette2()" << std::endl;
    std::cout << "BluePalette()" << std::endl;
    std::cout << "GreenToRedPalette()" << std::endl;
    std::cout << "GrayPalette()" << std::endl;
    std::cout << "GrayPalette2()" << std::endl;
    std::cout << "SetStandardPalette(const Int_t n)" << std::endl;
    std::cout << "  Standard options for n are:" << std::endl;
    std::cout << "  0, 29, 50, 51, 53, 54, 56, 93, 97, 107, or 112" << std::endl;
    std::cout << std::endl;
}
