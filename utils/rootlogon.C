//----------------------------------*-C++-*----------------------------------//
// Copyright 2020-2022 UT-Battelle, LLC, and other Celeritas developers.
// See the top-level COPYRIGHT file for details.
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file rootlogon.C
//---------------------------------------------------------------------------//
/*!
 * To set this as default:
 * Create a .rootrc file in your home directory with:
 *
 * \code
 *   Rint.Logon: /path/to/rootlogon.C
 * \endcode
 *
 * To use it only for specific plots: copy rootlogon.C to the macro folder.
 */
//---------------------------------------------------------------------------//
#include <iostream>
#include <TColor.h>
#include <TGaxis.h>
#include <TH1.h>
#include <TH2.h>
#include <TLatex.h>
#include <TROOT.h>
#include <TStyle.h>

void rootlogon()
{
    std::cout << "Welcome to the ROOT of all evils" << std::endl;

    // Create style
    TStyle* celeritas_style
        = new TStyle("celeritas_style", "Celeritas plot style");

    // Remove colored frame around plots
    celeritas_style->SetFrameBorderMode(0);
    celeritas_style->SetCanvasBorderMode(0);
    celeritas_style->SetPadBorderMode(0);

    // Set background color to white
    celeritas_style->SetFillColor(kWhite);
    celeritas_style->SetFrameFillColor(kWhite);
    celeritas_style->SetCanvasColor(kWhite);
    celeritas_style->SetPadColor(kWhite);
    celeritas_style->SetStatColor(kWhite);
    celeritas_style->SetTitleFillColor(0);

    // Hide histogram stats box
    celeritas_style->SetOptStat(0);

    // Use thicker lines
    celeritas_style->SetHistLineWidth(2);
    celeritas_style->SetFrameLineWidth(2);
    celeritas_style->SetFuncWidth(2);

    // Set number of tick marks to show on axes
    celeritas_style->SetNdivisions(506, "xyz");

    // Add tick lines on all sides of the plot
    celeritas_style->SetPadTickX(true);
    celeritas_style->SetPadTickY(true);

    // Add grey grid lines as standard
    celeritas_style->SetPadGridX(true);
    celeritas_style->SetPadGridY(true);
    celeritas_style->SetGridColor(kGray);
    celeritas_style->SetGridStyle(0);

    // Use the same font on all elements in the plot
    const int celeritas_font = 42;
    celeritas_style->SetLabelFont(celeritas_font, "xyz");
    celeritas_style->SetTitleFont(celeritas_font, "xyz");
    celeritas_style->SetTitleFont(celeritas_font, "");
    celeritas_style->SetTextFont(celeritas_font);
    celeritas_style->SetLegendFont(celeritas_font);

    // Set axis title sizes
    celeritas_style->SetTitleSize(.06, "xyz");

    // Increase axis offset to avoid clashing with big numbers
    celeritas_style->SetTitleOffset(.8, "x");
    celeritas_style->SetTitleOffset(.9, "y");
    celeritas_style->SetTitleOffset(.8, "z");

    // Apply the same distance settings to plot titles
    celeritas_style->SetTitleSize(.055, "");
    celeritas_style->SetTitleOffset(.8, "");

    // Define axes labels' (numbering) size and offset
    celeritas_style->SetLabelSize(.05, "xyz");
    celeritas_style->SetLabelOffset(.005, "xyz");

    // Center plot titles
    celeritas_style->SetTitleAlign(22);
    celeritas_style->SetTitleX(.5);
    celeritas_style->SetTitleY(.95);
    celeritas_style->SetTitleBorderSize(0);

    // Setup legends
    celeritas_style->SetLegendBorderSize(1);
    celeritas_style->SetLegendTextSize(0.05);

    // Prevent ROOT from occasionally suppressing the zero
    celeritas_style->SetHistMinimumZero();

    // Set default marker as a circle
    celeritas_style->SetMarkerStyle(kFullCircle);

    // Set default fit line color as red
    celeritas_style->SetFuncColor(kRed);

    // Set automatic scientific notation on axes with large numbers
    TGaxis::SetMaxDigits(3);

    // Set Viridis palette as standard and increase number of contours
    celeritas_style->SetPalette(kViridis);
    celeritas_style->SetNumberContours(255);

    // Apply all settings
    gROOT->SetStyle("celeritas_style");

    // Uncomment this to force all plots loaded from files to use this style
    // gROOT->ForceStyle();
}

//---------------------------------------------------------------------------//
// Free functions
//---------------------------------------------------------------------------//
/*!
 * Helper functions to speed up writing plot macros.
 */

//---------------------------------------------------------------------------//
/*!
 * Adds either a "Preliminary" or a "Celeritas Preliminary" at the top right
 * corner of the plot.
 */
// Horizontal
void Preliminary()
{
    TLatex* prelim = new TLatex(.9, .95, "Preliminary");
    prelim->SetTextColor(38);
    prelim->SetNDC();
    prelim->SetTextSize(2 / 30.);
    prelim->SetTextAlign(32);
    prelim->Draw();
}

// Vertical
void PreliminarySide()
{
    TLatex* prelim = new TLatex(.93, .9, "Preliminary");
    prelim->SetTextColor(38);
    prelim->SetNDC();
    prelim->SetTextSize(2 / 30.);
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
    prelim->SetTextSize(2 / 30.);
    prelim->SetTextAlign(32);
    prelim->Draw();
}

// Vertical
void CPreliminarySide()
{
    TLatex* prelim = new TLatex(.93, .9, "Celeritas Preliminary");
    prelim->SetTextColor(38);
    prelim->SetNDC();
    prelim->SetTextSize(2 / 30.);
    prelim->SetTextAngle(270);
    prelim->SetTextAlign(12);
    prelim->Draw();
}

//---------------------------------------------------------------------------//
void RainbowPalette()
{
    const Int_t nRGB        = 5;
    const Int_t nContours   = 255;
    Double_t    stops[nRGB] = {0.00, 0.34, 0.61, 0.84, 1.00};
    Double_t    red[nRGB]   = {0.00, 0.00, 0.87, 1.00, 0.51};
    Double_t    green[nRGB] = {0.00, 0.81, 1.00, 0.20, 0.00};
    Double_t    blue[nRGB]  = {0.51, 1.00, 0.12, 0.00, 0.00};
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

//---------------------------------------------------------------------------//
void SunsetPalette()
{
    const Int_t nRGB        = 5;
    const Int_t nContours   = 255;
    Double_t    stops[nRGB] = {0.00, 0.20, 0.50, 0.75, 1.00};
    Double_t    red[nRGB]   = {1.00, 1.00, 1.00, 0.60, 0.00};
    Double_t    green[nRGB] = {1.00, 1.00, 0.50, 0.00, 0.00};
    Double_t    blue[nRGB]  = {0.90, 0.00, 0.00, 0.00, 0.00};
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

//---------------------------------------------------------------------------//
void SunsetPalette2()
{
    const Int_t nRGB        = 7;
    const Int_t nContours   = 255;
    Double_t    stops[nRGB] = {0.00, 0.10, 0.20, 0.40, 0.70, 0.85, 1.00};
    Double_t    red[nRGB]   = {0.20, 0.60, 0.80, 1.00, 0.81, 0.00, 0.05};
    Double_t    green[nRGB] = {0.00, 0.00, 0.00, 1.00, 0.95, 0.50, 0.05};
    Double_t    blue[nRGB]  = {0.00, 0.00, 0.00, 0.00, 1.00, 1.00, 0.30};
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

//---------------------------------------------------------------------------//
void BluePalette()
{
    const Int_t nRGB        = 5;
    const Int_t nContours   = 255;
    Double_t    stops[nRGB] = {0.00, 0.20, 0.50, 0.75, 1.00};
    Double_t    red[nRGB]   = {1.00, 0.80, 0.00, 0.00, 0.00};
    Double_t    green[nRGB] = {1.00, 0.90, 0.50, 0.20, 0.01};
    Double_t    blue[nRGB]  = {1.00, 1.00, 1.00, 0.40, 0.10};
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

//---------------------------------------------------------------------------//
void GreenToRedPalette()
{
    const Int_t nRGB        = 6;
    const Int_t nContours   = 255;
    Double_t    stops[nRGB] = {0.00, 0.10, 0.47, 0.53, 0.90, 1.00};
    Double_t    red[nRGB]   = {0.00, 0.00, 1.00, 1.00, 1.00, 0.65};
    Double_t    green[nRGB] = {0.65, 1.00, 1.00, 1.00, 0.00, 0.00};
    Double_t    blue[nRGB]  = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

//---------------------------------------------------------------------------//
void GrayPalette()
{
    const Int_t nRGB        = 5;
    const Int_t nContours   = 255;
    Double_t    stops[nRGB] = {0.00, 0.25, 0.50, 0.75, 1.00};
    Double_t    red[nRGB]   = {1.00, 0.75, 0.50, 0.25, 0.00};
    Double_t    green[nRGB] = {1.00, 0.75, 0.50, 0.25, 0.00};
    Double_t    blue[nRGB]  = {1.00, 0.75, 0.50, 0.25, 0.00};
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

//---------------------------------------------------------------------------//
void GrayPalette2()
{
    const Int_t nRGB        = 5;
    const Int_t nContours   = 255;
    Double_t    stops[nRGB] = {0.00, 0.25, 0.50, 0.75, 1.00};
    Double_t    red[nRGB]   = {0.00, 0.25, 0.50, 0.75, 1.00};
    Double_t    green[nRGB] = {0.00, 0.25, 0.50, 0.75, 1.00};
    Double_t    blue[nRGB]  = {0.00, 0.25, 0.50, 0.75, 1.00};
    TColor::CreateGradientColorTable(nRGB, stops, red, green, blue, nContours);
}

//---------------------------------------------------------------------------//
/*!
 * Print help.
 */
void help()
{
    std::cout << "-----------------------" << std::endl;
    std::cout << " Celeritas rootlogon.C " << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << std::endl;
    std::cout << ">>> Preliminary tags" << std::endl;
    std::cout << "Preliminary()" << std::endl;
    std::cout << "PreliminarySide()" << std::endl;
    std::cout << "CPreliminary()" << std::endl;
    std::cout << "CPreliminarySide()" << std::endl;
    std::cout << std::endl;
    std::cout << ">>> Extra color palettes" << std::endl;
    std::cout << "RainbowPalette()" << std::endl;
    std::cout << "SunsetPalette()" << std::endl;
    std::cout << "SunsetPalette2()" << std::endl;
    std::cout << "BluePalette()" << std::endl;
    std::cout << "GreenToRedPalette()" << std::endl;
    std::cout << "GrayPalette()" << std::endl;
    std::cout << "GrayPalette2()" << std::endl;
    std::cout << "For a full list of ROOT standard pallettes see "
                 "https://root.cern/doc/master/classTColor.html#C06"
              << std::endl;
    std::cout << std::endl;
}
