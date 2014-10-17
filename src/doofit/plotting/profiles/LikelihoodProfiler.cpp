#include "LikelihoodProfiler.h"

// from STL
#include <set>

// from ROOT
#include "TCanvas.h"
#include "TGraph.h"
#include "TH2D.h" 
#include "TAxis.h"
#include "TStyle.h"
#include "TColor.h"

// from RooFit
#include "RooFitResult.h"

// from DooCore
#include <doocore/io/MsgStream.h>
#include <doocore/io/Progress.h>
#include <doocore/lutils/lutils.h>

// from DooFit
#include "doofit/fitter/AbsFitter.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStd.h"

doofit::plotting::profiles::LikelihoodProfiler::LikelihoodProfiler()
: num_samples_(30)
{}

std::vector<double> doofit::plotting::profiles::LikelihoodProfiler::SetSamplePoint(unsigned int step) {
  using namespace doocore::io;

  std::vector<double> sample_vals;
  int i(scan_vars_.size() - 1);

  //sdebug << "step = " << step << endmsg;

  for (auto var : scan_vars_) {
    int step_this = step/std::pow(num_samples_,i);
    step -= step_this*std::pow(num_samples_,i);
    --i;

    double val(start_vals_[var->GetName()] + 3*var->getError()*(-1.0 + 2.0/static_cast<double>(num_samples_)*step_this));
    var->setVal(val);
    var->setConstant(true);

    sample_vals.push_back(val);
    //sdebug << "  " << var->GetName() << " = " << step_this << " @ " << var->getVal() << endmsg;
  }

  return sample_vals;
}

void doofit::plotting::profiles::LikelihoodProfiler::Scan() {
  using namespace doocore::io;

  //RooRealVar* parameter_scan = scan_vars_.front();

  //num_samples_                   = 12;
  unsigned int num_dimensions    = scan_vars_.size();
  unsigned int num_total_samples = std::pow(num_samples_,num_dimensions);
  unsigned int step              = 0;

  // double value_start = parameter_scan->getVal();
  // double value_scan  = value_start - 5.0*parameter_scan->getError();

  for (auto var : scan_vars_) {
    start_vals_[var->GetName()] = var->getVal();
  }

  Progress p("Sampling likelihood", num_total_samples);
  while (step < num_total_samples) {
    //parameter_scan->setVal(value_scan);
    //parameter_scan->setConstant(true);

    //sinfo << "PROFILE: " << value_scan << endmsg;

    std::vector<double> sample_vals(SetSamplePoint(step));

    fitter_->set_shutup(true);
    fitter_->Fit();  

    fit_results_.push_back(fitter_->fit_result());

    //sinfo << fitter_->NegativeLogLikelihood() << endmsg;
    //value_scan += 1*parameter_scan->getError();
    ++step;
    ++p;
  }  
  p.Finish();
}

void doofit::plotting::profiles::LikelihoodProfiler::ReadFitResults(doofit::toy::ToyStudyStd& toy_study) {
  using namespace doofit::toy;
  using namespace doocore::io;

  FitResultContainer fit_result_container(toy_study.GetFitResult());
  const RooFitResult* fit_result(std::get<0>(fit_result_container));
  int i = 0;
  while (fit_result != nullptr && i < 1000) {
    fit_results_.push_back(fit_result);

    fit_result_container = toy_study.GetFitResult();
    fit_result = std::get<0>(fit_result_container);
    //++i;
  }
}

bool doofit::plotting::profiles::LikelihoodProfiler::FitResultOkay(const RooFitResult& fit_result) const {
  using namespace doocore::io;
  if (fit_result.covQual() < 2) {
    return false;
  } else if (fit_result.statusCodeHistory(0) < 0) {
    return false;
  } else {
    return true;
  }
}

void doofit::plotting::profiles::LikelihoodProfiler::PlotHandler(const std::string& plot_path) {
  using namespace doocore::io;

  std::map<std::string, std::vector<double>> val_scan;
  std::vector<double> val_nll;

  for (auto var : scan_vars_) {
    RooRealVar* var_fixed = dynamic_cast<RooRealVar*>(fit_results_.front()->constPars().find(var->GetName()));
    scan_vars_titles_.push_back(var_fixed->GetTitle());
  }

  int i = 0;
  double min_nll(0.0);

  Progress p("Processing read in fit results", fit_results_.size());
  for (auto result : fit_results_) {
    if (FitResultOkay(*result)) {
      for (auto var : scan_vars_) {
        RooRealVar* var_fixed = dynamic_cast<RooRealVar*>(result->constPars().find(var->GetName()));

        if (var_fixed == nullptr) {
          serr << "Error in LikelihoodProfiler::PlotHandler(): Cannot find fixed parameter " 
               << var->GetName() << " in fit result!" << endmsg;
          throw;
        }

        val_scan[var->GetName()].push_back(var_fixed->getVal());
      }

      if (min_nll == 0.0 || min_nll > result->minNll()) {
        min_nll = result->minNll();
      }
      val_nll.push_back(result->minNll());

      ++p;
    }
  }
  p.Finish();

  for (auto &nll : val_nll) {
    if (nll != 0.0) {
      nll -= min_nll;
    }
  }

  if (val_scan.size() == 1) {
    doocore::lutils::setStyle();
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetTitleOffset(0.75, "y");
  } else if (val_scan.size() == 2) {
    doocore::lutils::setStyle("2d");
    //gStyle->SetNumberContours(999);
    gStyle->SetPadRightMargin(0.16);
    gStyle->SetTitleOffset(0.75, "z");
  }

  TCanvas c("c", "c", 800, 600);

  if (val_scan.size() == 1) {
    const std::vector<double>& val_x = val_scan.begin()->second;

    TGraph graph(val_nll.size(), &val_x[0], &val_nll[0]);
    graph.Draw("AP");
    graph.GetXaxis()->SetTitle(scan_vars_titles_.at(0).c_str());
    graph.GetYaxis()->SetTitle("#DeltaLL");
    graph.SetMarkerStyle(1);
    //graph.SetMarkerSize(10);
    graph.SetMarkerColor(kBlue+3);

    //c.SaveAs("profile.pdf");
    doocore::lutils::printPlot(&c, "profile", plot_path);
  } else if (val_scan.size() == 2) {

    const std::vector<double>& val_x = val_scan.begin()->second;
    const std::vector<double>& val_y = val_scan.rbegin()->second;

    auto minmax_x = std::minmax_element(val_x.begin(), val_x.end());
    auto minmax_y = std::minmax_element(val_y.begin(), val_y.end());

    Progress p_distinct("Counting distinct x and y values", val_x.size()+val_y.size());
    std::set<double> distinct_x, distinct_y;
    for (auto x : val_x) {
      distinct_x.insert(x);
      ++p_distinct;
    }
    for (auto y : val_y) {
      distinct_y.insert(y);
      ++p_distinct;
    }
    p_distinct.Finish();

    double min_nll(0.0), max_nll(0.0);
    for (auto nll : val_nll) {
      if (nll != 0 && (min_nll == 0.0 || nll < min_nll)) {
        min_nll = nll;
      }
      if (nll != 0 && (max_nll == 0.0 || nll > max_nll)) {
        max_nll = nll;
      }
    }

    double min_x = *minmax_x.first  - (*minmax_x.second-*minmax_x.first)/(distinct_x.size()-1)*0.5;
    double max_x = *minmax_x.second + (*minmax_x.second-*minmax_x.first)/(distinct_x.size()-1)*0.5;
    double min_y = *minmax_y.first  - (*minmax_y.second-*minmax_y.first)/(distinct_y.size()-1)*0.5;
    double max_y = *minmax_y.second + (*minmax_y.second-*minmax_y.first)/(distinct_y.size()-1)*0.5;

    TH2D histogram("histogram", "histogram", distinct_x.size(), min_x, max_x, distinct_y.size(), min_y, max_y);

    // sdebug << "histogram x: " << *minmax_x.first << " - " <<  *minmax_x.second << endmsg;
    // sdebug << "histogram y: " << *minmax_y.first << " - " <<  *minmax_y.second << endmsg;

    Progress p_hist("Filling 2D profile histogram", val_nll.size());
    for (int i=0; i<val_nll.size(); ++i) {
      // sdebug << val_x.at(i) << ", " << val_y.at(i) << " - " << val_nll.at(i) << endmsg;
      // sdebug << "Bin: " << histogram.FindBin(val_x.at(i), val_y.at(i)) << endmsg;
      
      int nbin_x, nbin_y, nbin_z;
      histogram.GetBinXYZ(histogram.FindBin(val_x.at(i), val_y.at(i)), nbin_x, nbin_y, nbin_z);

      // sdebug << "Bin center x: " << histogram.GetXaxis()->GetBinCenter(nbin_x) << endmsg;
      // sdebug << "Bin center y: " << histogram.GetYaxis()->GetBinCenter(nbin_y) << endmsg;

      histogram.SetBinContent(histogram.FindBin(val_x.at(i), val_y.at(i)), val_nll.at(i));
      ++p_hist;
    }
    p_hist.Finish();

    const Int_t NRGBs = 6;
    const Int_t NCont = 6;
    
    // Double_t stops[NRGBs] = { 0.00 , 0.50 , 2.00 , 4.50 , 8.00 , 12.5 };
    // Double_t red[NRGBs]   = { 0.00 , 0.00 , 0.20 , 1.00 , 1.00 , 1.00 };
    // Double_t green[NRGBs] = { 0.00 , 0.00 , 0.20 , 1.00 , 1.00 , 1.00 };
    // Double_t blue[NRGBs]  = { 0.20 , 1.00 , 1.00 , 1.00 , 1.00 , 1.00 };
    // TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    // gStyle->SetNumberContours(NCont);
    // gStyle->SetPaintTextFormat(".1f");

    sinfo << "LikelihoodProfiler::PlotHandler(): Drawing histogram." << endmsg;
    histogram.Draw("COLZ");
    histogram.GetZaxis()->SetRangeUser(min_nll, max_nll);
    histogram.SetXTitle(scan_vars_titles_.at(0).c_str());
    histogram.SetYTitle(scan_vars_titles_.at(1).c_str());
    histogram.SetZTitle("#DeltaLL");

    //c.SaveAs("profile.pdf");
    sinfo << "LikelihoodProfiler::PlotHandler(): Saving linear histograms to output files." << endmsg;
    doocore::lutils::printPlot(&c, "profile", plot_path, true);
    sinfo << "LikelihoodProfiler::PlotHandler(): Saving logarithmic histograms to output files." << endmsg;
    c.SetLogz(true);
    doocore::lutils::printPlot(&c, "profile_log", plot_path, true);
    sinfo << "LikelihoodProfiler::PlotHandler(): All done." << endmsg;
  } else {
    serr << "Error in LikelihoodProfiler::PlotHandler(): Cannot (yet) plot 3D likelihood." << endmsg;
    throw;
  }
}


