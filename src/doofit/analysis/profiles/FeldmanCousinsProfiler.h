#ifndef DOOFIT_PLOTTING_PROFILES_FELDMANCOUSINSPROFILER_H
#define DOOFIT_PLOTTING_PROFILES_FELDMANCOUSINSPROFILER_H

// STL
#include <string>
#include <vector>
#include <map>

// BOOST

// ROOT

// from RooFit

// from DooCore

// from project
#include "doofit/plotting/Plot/PlotConfig.h"
#include "doofit/toy/ToyStudyStd/ToyStudyStd.h"
#include "doofit/fitter/easyfit/EasyFitResult.h"

// forward declarations
namespace doofit { namespace fitter {
  class AbsFitter;
}}
namespace doofit { namespace toy {
  class ToyStudyStd;
}}
class RooRealVar;
class RooFitResult;
class TGraph;

namespace doofit {
namespace plotting {
namespace profiles {
  
/** @class FeldmanCousinsProfiler
 *  @brief Plotter for likelihood profiles for a given AbsFitter
 *
 *  This class plots a likelihood profile for a given AbsFitter and one or more
 *  RooRealVars to scan. For each scan point the AbsFitter will fit the data 
 *  with only the parameters of interest fixed to the appropriate value.
 *
 *  @section usage Usage
 *
 *  Usage is shown via this example:
 *
 * @code
 * - tbd -
 * @endcode
 *
 *  @author Florian Kruse
 */

class FeldmanCousinsProfiler {
 public:
  /**
   *  @brief Default constructor for FeldmanCousinsProfiler
   */
  FeldmanCousinsProfiler(const PlotConfig& cfg_plot);
  
  /**
   *  @brief Destructor for FeldmanCousinsProfiler
   *
   *  Detailed description.
   *
   */
  ~FeldmanCousinsProfiler() {}
  
  void AddScanVariable(RooRealVar* variable) {
    scan_vars_.push_back(variable);
  }

  /**
   *  @brief Read the nominal data fit result from a ToyStudyStd
   */
  void ReadFitResultDataNominal(doofit::toy::ToyStudyStd& toy_study);

  /**
   *  @brief Read the scanned data fit results from a ToyStudyStd
   */
  void ReadFitResultsDataScan(doofit::toy::ToyStudyStd& toy_study);

  /**
   *  @brief Read the scanned toy fit results from a ToyStudyStd
   */
  void ReadFitResultsToy(doofit::toy::ToyStudyStd& toy_study);

  const doofit::fitter::easyfit::EasyFitResult& GetDataScanResult(const std::vector<double>& scan_point) const;
  
  void ReleaseAllFitResults(doofit::toy::ToyStudyStd& toy_study);

  /**
   *  @brief Plot likelihood profile
   *
   *  @param plot_path path for the plots
   */
  void Plot(const std::string& plot_path) {
    PlotHandler(plot_path);
  }
  
 protected:

  /**
   *  @brief Plot likelihood profile (internal handler)
   *
   *  @param plot_path path for the plots
   */
  void PlotHandler(const std::string& plot_path);
  
  /**
   *  @brief Evaluate fit result quality
   *
   *  For a given fit result evaluate the fit quality (i.e. convergence, 
   *  covariance matrix quality and so on).
   *
   *  @param fit_result EasyFitResult to use for evaluation
   *  @return true if fit result is okay, false if not
   */
  bool FitResultOkay(const doofit::fitter::easyfit::EasyFitResult& fit_result) const;

  double FindGraphXValues(TGraph& graph, double xmin, double xmax, double value, double direction=+1.0) const;

 private:
  int ProcessToyFitResult(const doofit::fitter::easyfit::EasyFitResult& fr0, const doofit::fitter::easyfit::EasyFitResult& fr1);

  /**
   *  @brief PlotConfig instance to use
   */
  const PlotConfig& config_plot_;

  std::vector<RooRealVar*> scan_vars_;
  std::vector<std::string> scan_vars_titles_;
  std::vector<std::string> scan_vars_names_;

  double nll_data_nominal_;
  std::map<std::vector<double>, double> delta_nlls_data_scan_;
  std::map<std::vector<double>, doofit::fitter::easyfit::EasyFitResult> fit_results_data_scan_;
  std::set<std::vector<double>> scan_vals_data_;
  std::map<std::vector<double>, std::vector<double>> delta_nlls_toy_scan_;
  std::set<std::vector<double>> scan_vals_toy_;
  std::map<std::vector<double>, unsigned int> num_neglected_fits_;

  unsigned int num_samples_;

  double time_total_;
};

} // namespace profiles
} // namespace plotting
} // namespace doofit

#endif //DOOFIT_PLOTTING_PROFILES_FELDMANCOUSINSPROFILER_H