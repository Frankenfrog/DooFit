#ifndef DOOFIT_PLOTTING_PLOT_PLOT_h
#define DOOFIT_PLOTTING_PLOT_PLOT_h

// STL
#include <string>
#include <vector>

// BOOST

// ROOT

// from RooFit
#include "RooArgList.h"

// from DooCore
#include "doocore/io/MsgStream.h"

// from project
#include "doofit/plotting/Plot/PlotConfig.h"

// forward declarations
class RooAbsRealLValue;
class RooAbsData;
class RooAbsPdf;

namespace doofit {
/** @namespace doofit::plotting
 *
 *  @brief Plotting subsystem namespace.
 *
 *  This namespace is responsible for plotting.
 *
 */
  
namespace plotting {
  
enum ScaleType {
  kLogarithmic,
  kLinear,
  kBoth
};
  
  /** @class Plot
   *  @brief A simple plot based on a dataset and optional PDFs
   *
   *  This class is built to produce a basic plot. It is not intended to suit 
   *  every plotting need someone might ever have. Derived classes are intended
   *  for more specific support. Main focus is convenience and ease of use.
   *
   *  You can supply datasets and PDFs to plot. To plot components, you can 
   *  either directly specify sub PDFs to plot as well as supply regular 
   *  expressions of component PDF names. Any PDF matching the patterns will be
   *  plotted as well. This is especially useful for plotting of simultaneous 
   *  PDFs.
   *
   *  @section usage Usage
   *
   *  Usage is shown via this example:
   *
   * @code
   * #include "doofit/plotting/Plot/Plot.h"
   * #include "doofit/plotting/Plot/PlotConfig.h"
   * #include "RooRealVar.h"
   * #include "RooGaussian.h"
   * #include "RooExponential.h"
   * #include "RooAddPdf.h"
   * #include "RooDataSet.h"
   * #include "RooArgList.h"
   *
   * // for cool vector assignment
   * #include <boost/assign/std/vector.hpp>
   * using namespace boost::assign;
   *
   * int main(int argc, char *argv[]) {
   *   // generate a PDF and a dataset here
   *   RooRealVar mass("mass","mass",5200,5400,"MeV/c^{2}");
   *   RooRealVar mean("mean","mean",5300);
   *   RooRealVar sigma("sigma","sigma",20);
   *   RooGaussian g("pdf_sig_gaussian","g",mass,mean,sigma);
   *
   *   RooRealVar c("c","c",0.01);
   *   RooExponential e("pdf_bkg_exponential","e",mass,c);
   *
   *   RooRealVar f("f","f",0.5);
   *   RooAddPdf p("pdf_all","p",g,e,f);
   *
   *   RooDataSet* data = p.generate(mass, 2000);
   *
   *   // DooFit's plotting usage actually starts here
   *   using namespace doofit::plotting;
   *
   *   PlotConfig cfg_plot("cfg_plot");
   *   cfg_plot.InitializeOptions(argc, argv);
   *
   *   // plot PDF and directly specify components
   *   Plot myplot(cfg_plot, mass, *data, RooArgList(p,g,e));
   *   myplot.PlotIt();
   *
   *   // plot PDF and scale x- and y-axis independently (choose between kLinear, kLogarithmic or kBoth). The default value is kLinear
   *   Plot myplot2(cfg_plot, mass, *data, RooArgList(p,g,e), "different_scaling");
   *   myplot2.set_scaletype_x(doofit::plotting::kBoth);
   *   myplot2.set_scaletype_y(doofit::plotting::kBoth);
   *   myplot2.PlotIt();
   *
   *   // plot PDF and specify components via regular expressions
   *   std::vector<std::string> components;
   *   components += "pdf_sig_.*", "pdf_bkg_.*";
   *   Plot myplot3(cfg_plot, mass, *data, p, components, "mass3");
   *   myplot3.PlotIt();
   * }
   * @endcode
   *
   *  Plot will simply plot the given dataset in the supplied variable. If PDFs
   *  are also supplied (optional), they are plotted as well. The first PDF 
   *  needs to be the overall PDF, all following must be components of the 
   *  first. A pull plot is automatically created if PDFs are supplied. A 
   *  non-pull plot will be created in any way.
   *
   *  Configuration can be done via the associated PlotConfig object that also 
   *  supports config files and command line options using DooFit's Config 
   *  architecture. Refer to PlotConfig for possible options.
   *
   *  doocore::lutils methods are used for plotting assuring nice and shiny plots.
   *
   *  @section stacked_plots Stacked plots feature
   *
   *  Stacked plots are created automatically for all Plot objects associated 
   *  with one PlotConfig object. Every plot being created will be appended to 
   *  a file called AllPlots.pdf in the plot output directory.
   */
  
  class Plot {
  public:
    /**
     *  @brief Constructor for Plot
     *
     *  This will initialise the Plot which can then be plotted via 
     *  Plot::PlotIt()
     *
     *  @param cfg_plot PlotConfig holding plotting configuration
     *  @param dimension the dimension to plot (e.g. a RooRealVar)
     *  @param dataset the dataset to plot (e.g. a RooDataSet)
     *  @param pdfs (optional) a RooArgList of PDFs to plot; the first PDF must be the overall PDF, further PDFs must be components of this PDF
     *  @param plot_name (optional) a name for this plot (i.e. the output files; will be the variable name if empty)
     */
    Plot(const PlotConfig& cfg_plot, const RooAbsRealLValue& dimension, const RooAbsData& dataset, const RooArgList& pdfs=RooArgList(), const std::string& plot_name="");
        
    /**
     *  @brief Constructor for Plot with regular expressions for plotted components
     *
     *  This will initialise the Plot which can then be plotted via
     *  Plot::PlotIt(). A vector of regular expressions with component patterns
     *  can be supplied. Each sub PDF of pdf will be matched against this 
     *  pattern and plotted as a component if matching.
     *
     *  @param cfg_plot PlotConfig holding plotting configuration
     *  @param dimension the dimension to plot (e.g. a RooRealVar)
     *  @param dataset the dataset to plot (e.g. a RooDataSet)
     *  @param pdf main PDF to plot
     *  @param components vector of components to plot as regular expression strings
     *  @param plot_name (optional) a name for this plot (i.e. the output files; will be the variable name if empty)
     */
    Plot(const PlotConfig& cfg_plot, const RooAbsRealLValue& dimension, const RooAbsData& dataset, const RooAbsPdf& pdf, const std::vector<std::string>& components, const std::string& plot_name="");
    
    /**
     *  @brief Actually plot the plot in normal scale
     *
     *  This function will plot the data in the axis scales you set with the ScaleType.
     */
    void PlotIt() const { PlotHandler(scaletype_x_, scaletype_y_); }
    
    /**
     *  @brief Destructor for Plot
     */
    virtual ~Plot();
    
    /**
     *  @brief Add additional RooCmdArgs for plotting (for PDF plotting)
     *
     *  @warning Please note if you want to use ProjWData() as RooCmdArg: 
     *           Unfortunately, RooFit allows you to write very dangerous code
     *           as ProjWData expects a RooArgSet& reference as first parameter.
     *           If this RooArgSet is a temporal object (by calling RooArgSet in
     *           the ProjWData call or by passing a RooRealVar which will 
     *           trigger the creation of a temporal argset) the RooCmdArg will 
     *           not function properly inside Plot. Always make sure to pass 
     *           objects that live long enough!
     *
     *  @param arg RooCmdArg to use for plotting
     */
    void AddPlotArg(RooCmdArg arg) {plot_args_pdf_.push_back(arg);}

    /**
     *  @brief Add additional RooCmdArgs for plotting (for dataset plotting)
     *
     *  @param arg RooCmdArg to use for plotting
     */
    void AddPlotArgData(RooCmdArg arg) {plot_args_data_.push_back(arg);}
    
    /**
     *  @brief Set additional plot label (to be added as splitline under label from PlotConfig)
     *
     *  @param plot_label_additional label as TLatex string
     */
    void set_plot_label_additional(std::string plot_label_additional) {
      plot_label_additional_ = plot_label_additional;
    }

    /**
     *  @brief Set plot range to use for this plot
     *
     *  Set a range to be used for plotting. This range has to be defined on the
     *  appropriate RooRealVars to be used for plotting and projecting.
     *
     *  @param plot_range plot range to use
     */
    void set_plot_range(const std::string& plot_range) { plot_range_ = plot_range; }
    
    /**
     *  @brief Set asymmetry plotting mode
     *
     *  Set true, if an asymmetry shall be plotted. The y-axis  range will be set
     *  from -1 to 1 
     *  
     *  @param plot_asymmetry set true for plotting asymmetry
     */
     void set_plot_asymmetry(bool plot_asymmetry) { plot_asymmetry_ = plot_asymmetry; }

     /**
     *  @brief Set plotting mode for x-axis
     *
     *  @param scaletype set kLogarithmic, kLinear, kBoth 
     */
     void set_scaletype_x(ScaleType scaletype_x) { scaletype_x_ = scaletype_x; }

     /**
     *  @brief Set plotting mode for y-axis
     *
     *  @param scaletype set kLogarithmic, kLinear, kBoth 
     */
     void set_scaletype_y(ScaleType scaletype_y) { scaletype_y_ = scaletype_y; }

    /**
     *  @brief Friend class PlotSimultaneous
     */
    friend class PlotSimultaneous;
    
  protected:
    /**
     *  \brief PlotConfig instance to use
     */
    const PlotConfig& config_plot_;

    /**
     *  @brief Internal plotting handler
     *
     *  This function will perform the actual plotting and is called by public
     *  functions.
     *
     *  @param sc_x ScaleType for x-axis
     *  @param sc_y ScaleType for y-axis
     */
    virtual void PlotHandler(ScaleType sc_x, ScaleType sc_y) const;

    void set_ignore_num_cpu(bool ignore_num_cpu) { ignore_num_cpu_ = ignore_num_cpu; }

    /**
     *  @brief Dimension to plot in
     */
    const RooAbsRealLValue& dimension_;
    
    /**
     *  @brief Dataset to plot
     */
    std::vector<const RooAbsData*> datasets_;
    
    /**
     *  @brief Main PDF to plot
     */
    const RooAbsPdf* pdf_;
    
    /**
     *  @brief Sub components to plot, one RooArgSet per component
     */
    std::vector<RooArgSet> components_;
    
    /**
     *  @brief Plot name
     */
    std::string plot_name_;
    
    /**
     *  @brief Additional plot label (splitlined with label from PlotConfig)
     */
    std::string plot_label_additional_;

    /**
     *  @brief Plot range
     */
    std::string plot_range_;
        
    /**
     *  @brief Vector containing additional RooCmdArgs for plotting (PDF part)
     */
    std::vector<RooCmdArg> plot_args_pdf_;

    /**
     *  @brief Vector containing additional RooCmdArgs for plotting (dataset part)
     */
    std::vector<RooCmdArg> plot_args_data_;

    /**
     *  @brief Flag to ignore setting of NumCPU to avoid plotting problems
     */
    bool ignore_num_cpu_;

    bool plot_asymmetry_;

    ScaleType scaletype_x_;
    ScaleType scaletype_y_;
    
  private:
  };  
} // namespace plotting
} // namespace doofit

#endif // DOOFIT_PLOTTING_PLOT_PLOT_h