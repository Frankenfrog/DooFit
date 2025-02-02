#ifndef DOOFIT_FITTER_EASYFIT_FITRESULTPRINTER_h
#define DOOFIT_FITTER_EASYFIT_FITRESULTPRINTER_h

// STL
#include <string>
#include <vector>

// BOOST

// ROOT

// from RooFit

// from DooCore
#include <doocore/io/MsgStream.h>

// from project
#include "doofit/fitter/easyfit/EasyFitResult.h"

// forward declarations
class RooFitResult;

namespace doofit {
namespace fitter {
namespace easyfit {

/** @class FitResultPrinter
 *  @brief Flexible plotter for fitresults
 *
 *  This class plots a RooFitResult in a more flexible way than the 
 *  RooFitResult::Print functionality.
 *
 *  @section usage Usage
 *
 *  Usage is shown via this example:
 *
 * @code
 * doofit::fitter::easyfit::EasyFit efit_full("fit_toy")
 * efit_full.Fit();
 * fit_result = efit_full.GetFitResult();
 * doofit::plotting::fitresult::FitResultPrinter printer(*fit_result);
 * printer.Print();
 * @endcode
 *
 *  @author Florian Kruse
 */

class FitResultPrinter {
 public:
  /**
   *  @brief Default constructor for FitResultPrinter
   *
   *  @param fit_result the fit result to print
   */
  FitResultPrinter(const RooFitResult& fit_result);

  /**
   *  @brief Default constructor for FitResultPrinter
   *
   *  @param fit_result the fit result to print
   */
  FitResultPrinter(const doofit::fitter::easyfit::EasyFitResult& fit_result);
  
  ~FitResultPrinter() {}
  
  /**
   *  @brief Print the RooFitResult
   */
  void Print() const {
    PlotHandler();
  }

  FitResultPrinter& set_full_precision_printout(bool full_precision_printout) {
    full_precision_printout_ = full_precision_printout;
    return *this;
  }

  FitResultPrinter& set_print_pulls(bool print_pulls) {
    print_pulls_ = print_pulls;
    return *this;
  }

  FitResultPrinter& set_print_const_pars(bool print_const_pars) {
    print_const_pars_ = print_const_pars;
    return *this;
  }
  
 protected:
  
  /**
   *  @brief Get a terminal color code (if tty terminal)
   *
   *  @param color the color (0: green, 1: yellow, 2: red)
   */
  std::string TerminalColorCode(int color) const {
    std::vector<std::string> str_colors;
    str_colors.push_back("\033[1;32m");
    str_colors.push_back("\033[1;33m");
    str_colors.push_back("\033[1;31m");
    str_colors.push_back("\033[1;34m");

    if (!doocore::io::TerminalIsRedirected()) {
      return str_colors.at(color);
    } else {
      return "";
    }
  }

  /**
   *  @brief Get a terminal reset string (if tty terminal)
   */
  std::string TerminalResetCode() const {
    if (!doocore::io::TerminalIsRedirected()) {
      return "\033[0m";
    } else {
      return "";
    }
  }

  /**
   *  @brief Print the RooFitResult (internal handler)
   */
  void PlotHandler() const;
  
 private:
  doofit::fitter::easyfit::EasyFitResult fit_result_;

  bool full_precision_printout_;
  bool print_pulls_;
  bool print_const_pars_;
};


} // namespace easyfit
} // namespace fitter
} // namespace doofit

#endif //DOOFIT_FITTER_EASYFIT_FITRESULTPRINTER_h