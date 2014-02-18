#include "doofit/plotting/Plot/Plot.h"

// STL
#include <string>
#include <sstream>
#include <vector>

// boost
#include <boost/regex.hpp>

// ROOT
#include "TIterator.h" 
#include "TString.h"
#include "TAxis.h"

// from RooFit
#include "RooArgList.h"
#include "RooAbsRealLValue.h"
#include "RooAbsData.h"
#include "RooAbsPdf.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooBinning.h"
#include <RooMsgService.h>

// from Project
#include "doocore/io/MsgStream.h"
#include "doocore/lutils/lutils.h"
#include "doofit/plotting/Plot/PlotConfig.h"

using namespace ROOT;
using namespace RooFit;
using namespace doocore::io;

namespace doofit {
namespace plotting {

Plot::Plot(const PlotConfig& cfg_plot, const RooAbsRealLValue& dimension, const RooAbsData& dataset, const RooArgList& pdfs, const std::string& plot_name)
: config_plot_(cfg_plot),
  dimension_(dimension),
  datasets_(),
  plot_name_(plot_name)
{
  datasets_.push_back(&dataset);
  pdf_ = dynamic_cast<RooAbsPdf*>(pdfs.first());
  
  if (&dimension_ == NULL) {
    serr << "Plot::Plot(): Dimension is invalid." << endmsg;
    throw 1;
  }
  if (datasets_.front() == NULL) {
    serr << "Plot::Plot(): Dataset is invalid." << endmsg;
    throw 1;
  }
  if (plot_name_ == "") {
    plot_name_ = dimension_.GetName();
  }
  
  for (int i=1; i<pdfs.getSize(); ++i) {
    RooAbsArg* sub_arg = pdfs.at(i);
    const RooAbsPdf* sub_pdf = dynamic_cast<RooAbsPdf*>(sub_arg);
    
    if (sub_pdf != NULL) {
      components_.push_back(RooArgSet(*sub_pdf));
    }
  }
}

Plot::Plot(const PlotConfig& cfg_plot, const RooAbsRealLValue& dimension, const RooAbsData& dataset, const RooAbsPdf& pdf, const std::vector<std::string>& components, const std::string& plot_name)
: config_plot_(cfg_plot),
  dimension_(dimension),
  datasets_(),
  plot_name_(plot_name)
{
  datasets_.push_back(&dataset);
  pdf_ = &pdf;
  
  if (pdf_ == NULL) {
    serr << "Plot::Plot(): Main PDF is invalid." << endmsg;
    throw 1;
  }
  if (&dimension_ == NULL) {
    serr << "Plot::Plot(): Dimension is invalid." << endmsg;
    throw 1;
  }
  if (datasets_.front() == NULL) {
    serr << "Plot::Plot(): Dataset is invalid." << endmsg;
    throw 1;
  }
  if (plot_name_ == "") {
    plot_name_ = dimension_.GetName();
  }
  
  // iterate over sub PDFs and match supplied regular expressions
  RooArgSet nodes;
  pdf.branchNodeServerList(&nodes);
  
  for (std::vector<std::string>::const_iterator it = components.begin();
       it != components.end(); ++it) {
    boost::regex r(*it);
    components_.push_back(RooArgSet());
    
    TIterator* it_nodes = nodes.createIterator();
    RooAbsArg* node = NULL;
    
    while ((node = dynamic_cast<RooAbsArg*>(it_nodes->Next()))) {
      RooAbsPdf* pdf_node = dynamic_cast<RooAbsPdf*>(node);
      if (pdf_node != NULL) {
        std::string pdf_name = pdf_node->GetName();

        // exclude resolution models generated by RooFit and match the rest
        if (pdf_name.find("_conv_") == -1 && regex_match(pdf_name,r)) {
          components_.back().add(*pdf_node);
        }
      }
    }
    delete it_nodes;
  }
}
  
void Plot::PlotHandler(ScaleType sc_y, std::string suffix) const {
  if (suffix == "") suffix = "_log";
  
  std::string plot_name = plot_name_;
  
  std::stringstream log_plot_name_sstr;
  log_plot_name_sstr << plot_name << suffix;
  std::string log_plot_name = log_plot_name_sstr.str();
  
  std::stringstream pull_plot_sstr;
  pull_plot_sstr << plot_name << "_pull";
  std::string pull_plot_name = pull_plot_sstr.str();
  
  std::stringstream log_pull_plot_sstr;
  log_pull_plot_sstr << plot_name << "_pull" << suffix;
  std::string log_pull_plot_name = log_pull_plot_sstr.str();

  sinfo << "Plotting " << dimension_.GetName() << " into directory " << config_plot_.plot_directory() << " as " << plot_name << endmsg;
  
  doocore::lutils::setStyle("LHCb");
  
  RooCmdArg range_arg;
  
  // x range
  if (!dimension_.hasMin() && !dimension_.hasMax()) {
    double min, max;
    
    // ugly const_cast because RooFit is stupid (RooDataSet::getRange needs non-const RooRealVar)
    RooRealVar* dimension_non_const = const_cast<RooRealVar*>(dynamic_cast<const RooRealVar*>(&dimension_));
    datasets_.front()->getRange(*dimension_non_const, min, max);
    
    double min_t, max_t;
    for (std::vector<const RooAbsData*>::const_iterator it = datasets_.begin()+1;
         it != datasets_.end(); ++it) {
      (*it)->getRange(*dimension_non_const, min_t, max_t);
      if (min_t < min) min = min_t;
      if (max_t > max) max = max_t;
    }
    
    range_arg = Range(min, max);
  }
  
  RooCmdArg cut_range_arg, projection_range_arg, frame_range_arg;
  RooBinning* binning = NULL;
  RooAbsData* dataset_reduced = NULL;
  if (plot_range_.length() > 0) {
    sinfo << "doofit::plotting: Plotting on named range " << plot_range_ << endmsg;
    cut_range_arg = CutRange(plot_range_.c_str());
    projection_range_arg = ProjectionRange(plot_range_.c_str());
    range_arg = Range(plot_range_.c_str());
    binning = new RooBinning(dimension_.getBinning().numBins(), dimension_.getMin(plot_range_.c_str()), dimension_.getMax(plot_range_.c_str()));

    // ugly const cast as RooFit (once again) gives a shit about const correctness
    RooAbsData* dataset = const_cast<RooAbsData*>(datasets_.front());
    //dataset_reduced = dataset->reduce(cut_range_arg);
    dataset_reduced = dataset->reduce(CutRange(plot_range_.c_str()));
        
    //sdebug << "Created reduced dataset with " << dataset_reduced->numEntries() << " (original dataset has " << dataset->numEntries() << ")" << endmsg;
  }

  RooPlot* plot_frame = dimension_.frame(range_arg);
  
  RooCmdArg weight_arg;
  
  if (dataset_reduced != NULL) {
    if (dataset_reduced->isWeighted()) {
      //sdebug << "Spotted a weighted dataset, setting SumW2 errors." << endmsg;
      weight_arg = DataError(RooAbsData::SumW2);
    }
    
    RooMsgService::instance().setStreamStatus(1, false);
    if (binning != NULL) {
      dataset_reduced->plotOn(plot_frame, Binning(*binning), cut_range_arg, weight_arg/*, Rescale(1.0/(*it)->sumEntries())*/);
    } else {
      dataset_reduced->plotOn(plot_frame, Binning(dimension_.getBinning()), cut_range_arg, weight_arg/*, Rescale(1.0/(*it)->sumEntries())*/);
    }
    RooMsgService::instance().setStreamStatus(1, true);
  } else {
    for (std::vector<const RooAbsData*>::const_iterator it = datasets_.begin();
         it != datasets_.end(); ++it) {
      if ((*it)->isWeighted()) {
        sdebug << "Weighted dataset, setting SumW2 errors." << endmsg;
        weight_arg = DataError(RooAbsData::SumW2);
      }
      
      RooMsgService::instance().setStreamStatus(1, false);
      if (binning != NULL) {
        (*it)->plotOn(plot_frame, Binning(*binning), cut_range_arg, weight_arg/*, Rescale(1.0/(*it)->sumEntries())*/);
      } else {
        (*it)->plotOn(plot_frame, Binning(dimension_.getBinning()), cut_range_arg, weight_arg/*, Rescale(1.0/(*it)->sumEntries())*/);
      }
      RooMsgService::instance().setStreamStatus(1, true);
    }
  }
  
  // y range adaptively for log scale
  RooHist * data = (RooHist*) plot_frame->findObject(0,RooHist::Class());
  double x,y;
  data->GetPoint(0,x,y);
  double min_data_entry = y;
  for (unsigned int i = 1; i < data->GetN(); ++i) {
    data->GetPoint(i,x,y);
    if (min_data_entry > y) min_data_entry = y;
  }
  if (min_data_entry == 0.0) min_data_entry = 1.0;
  if (min_data_entry < 0.0) min_data_entry = 0.01;
//  sdebug << "minimum data entry in dataset: " << min_data_entry << endmsg;
  double min_plot = TMath::Power(10.0,TMath::Log10(min_data_entry)-0.9);
  
//  sdebug << "minimum entry in histogram: " << min_data_entry << endmsg;
//  sdebug << "minimum for plot range: " << min_plot << endmsg;
  
  TLatex label(0.65,0.85,"LHCb");
  
  config_plot_.OnDemandOpenPlotStack();
  if (pdf_ != NULL) {
//    RooPlot* plot_frame_pull = dimension_.frame(range_arg);
    
    // I feel so stupid doing this but apparently RooFit leaves me no other way...
    RooCmdArg arg1, arg2, arg3, arg4, arg5, arg6, arg7;
    if (plot_args_.size() > 0) arg1 = plot_args_[0];
    if (plot_args_.size() > 1) arg2 = plot_args_[1];
    if (plot_args_.size() > 2) arg3 = plot_args_[2];
    if (plot_args_.size() > 3) arg4 = plot_args_[3];
    if (plot_args_.size() > 4) arg5 = plot_args_[4];
    if (plot_args_.size() > 5) arg6 = plot_args_[5];
//    if (plot_args_.size() > 6) arg7 = plot_args_[6];
    
//    if (dataset_reduced != NULL) {
//      serr << "Reduced dataset available. Plotting this." << endmsg;
//      if (binning != NULL) {
//        dataset_reduced->plotOn(plot_frame_pull, Binning(*binning), cut_range_arg);
//      } else {
//        dataset_reduced->plotOn(plot_frame_pull, Binning(dimension_.getBinning()), cut_range_arg);
//      }
//    } else {
//      for (std::vector<const RooAbsData*>::const_iterator it = datasets_.begin();
//           it != datasets_.end(); ++it) {
//        if (binning != NULL) {
//          (*it)->plotOn(plot_frame_pull, Binning(*binning), cut_range_arg);
//        } else {
//          (*it)->plotOn(plot_frame_pull, Binning(dimension_.getBinning()), cut_range_arg);
//        }
//      }
//    }
    
    int i=1;
    for (std::vector<RooArgSet>::const_iterator it = components_.begin();
         it != components_.end(); ++it) {
      if (it->getSize() > 0) {
        //sinfo << "Plotting component " << it->first()->GetName() << endmsg;
        RooMsgService::instance().setStreamStatus(1, false);
        RooMsgService::instance().setStreamStatus(0, false);
        pdf_->plotOn(plot_frame, Components(*it), LineColor(config_plot_.GetPdfLineColor(i)), LineStyle(config_plot_.GetPdfLineStyle(i)), projection_range_arg/*, NumCPU(8)*/, arg1, arg2, arg3, arg4, arg5, arg6);
//        pdf_->plotOn(plot_frame_pull, Components(*it), LineColor(config_plot_.GetPdfLineColor(i)), LineStyle(config_plot_.GetPdfLineStyle(i)), projection_range_arg/*, NumCPU(8)*/, arg1, arg2, arg3, arg4, arg5, arg6);
        RooMsgService::instance().setStreamStatus(1, true);
        RooMsgService::instance().setStreamStatus(0, true);
        ++i;
      }
    }
    
    RooMsgService::instance().setStreamStatus(1, false);
    RooMsgService::instance().setStreamStatus(0, false);
    pdf_->plotOn(plot_frame, LineColor(config_plot_.GetPdfLineColor(0)), LineStyle(config_plot_.GetPdfLineStyle(0)), projection_range_arg/*, NumCPU(8)*/, arg1, arg2, arg3, arg4, arg5, arg6);
//    pdf_->plotOn(plot_frame_pull, LineColor(config_plot_.GetPdfLineColor(0)), LineStyle(config_plot_.GetPdfLineStyle(0)), projection_range_arg/*, NumCPU(8)*/, arg1, arg2, arg3, arg4, arg5, arg6);
    RooMsgService::instance().setStreamStatus(1, true);
    RooMsgService::instance().setStreamStatus(0, true);
    
    // =10^(ln(11)/ln(10)-0.5)
    //plot_frame_pull->SetMinimum(0.5);
    
    plot_frame->SetMinimum(0.0);
    plot_frame->SetMaximum(1.3*plot_frame->GetMaximum());
    
    TString ylabel = plot_frame->GetYaxis()->GetTitle();
    ylabel.ReplaceAll("Events","Candidates");
    plot_frame->GetYaxis()->SetTitle(ylabel);
    
    if (sc_y == kLinear || sc_y == kBoth) {
      doocore::lutils::PlotSimple(plot_name, plot_frame, label, config_plot_.plot_directory(), false);
      doocore::lutils::PlotSimple("AllPlots"+config_plot_.plot_appendix(), plot_frame, label, config_plot_.plot_directory(), false);
    }
    
    plot_frame->SetMinimum(min_plot);
    if (sc_y == kLogarithmic || sc_y == kBoth) {
      doocore::lutils::PlotSimple(log_plot_name, plot_frame, label, config_plot_.plot_directory(), true);
      doocore::lutils::PlotSimple("AllPlots"+config_plot_.plot_appendix(), plot_frame, label, config_plot_.plot_directory(), true);
    }
    
    plot_frame->SetMinimum(0.5);
    plot_frame->SetMaximum(1.3*plot_frame->GetMaximum());
    
//    TString ylabel = plot_frame->GetYaxis()->GetTitle();
//    ylabel.ReplaceAll("Events","Candidates");
//    plot_frame->GetYaxis()->SetTitle(ylabel);
    
    if (sc_y == kLinear || sc_y == kBoth) {
      doocore::lutils::PlotPulls(pull_plot_name, plot_frame, label, config_plot_.plot_directory(), false, false, true);
      doocore::lutils::PlotPulls("AllPlots"+config_plot_.plot_appendix(), plot_frame, label, config_plot_.plot_directory(), false, false, true, "");
    }
    
//    sdebug << "Plot y axis minimum for log scale plot: " << min_plot << endmsg;
    plot_frame->SetMinimum(min_plot);
    if (sc_y == kLogarithmic || sc_y == kBoth) {
      doocore::lutils::PlotPulls(log_pull_plot_name, plot_frame, label, config_plot_.plot_directory(), true, false, true);
      doocore::lutils::PlotPulls("AllPlots"+config_plot_.plot_appendix(), plot_frame, label, config_plot_.plot_directory(), true, false, true, "");
    }
    
//    delete plot_frame_pull;
  } else {
    plot_frame->SetMinimum(0.0);
    plot_frame->SetMaximum(1.3*plot_frame->GetMaximum());
    
    TString ylabel = plot_frame->GetYaxis()->GetTitle();
    ylabel.ReplaceAll("Events","Candidates");
    plot_frame->GetYaxis()->SetTitle(ylabel);
    
    if (sc_y == kLinear || sc_y == kBoth) {
      doocore::lutils::PlotSimple(plot_name, plot_frame, label, config_plot_.plot_directory(), false);
      doocore::lutils::PlotSimple("AllPlots"+config_plot_.plot_appendix(), plot_frame, label, config_plot_.plot_directory(), false);
    }
    
    plot_frame->SetMinimum(min_plot);
    if (sc_y == kLogarithmic || sc_y == kBoth) {
      doocore::lutils::PlotSimple(log_plot_name, plot_frame, label, config_plot_.plot_directory(), true);
      doocore::lutils::PlotSimple("AllPlots"+config_plot_.plot_appendix(), plot_frame, label, config_plot_.plot_directory(), true);
    }
  }
  
  if (dataset_reduced != NULL) delete dataset_reduced;
  if (binning != NULL) delete binning;
  delete plot_frame;
}
  
Plot::~Plot() {}

} // namespace plotting
} // namespace doofit
