#ifndef DOOFIT_PLOTTING_PLOT_PLOTCONFIG_h
#define DOOFIT_PLOTTING_PLOT_PLOTCONFIG_h

// STL
#include <vector>
#include <map>
#include <string>

// BOOST

// ROOT

// from RooFit

// from project
#include "doofit/config/AbsConfig.h"
#include "doofit/config/CommaSeparatedList.h"
#include "doofit/config/CommaSeparatedPair.h"

// forward declarations
class TCanvas;

namespace doofit {
namespace plotting {
/** @class PlotConfig
 *  @brief DooFit Config class for the Plot class
 *
 *  This class is responsible for all Plot related configuration options
 *  which are not covered by CommonConfig.
 */
class PlotConfig : public config::AbsConfig {
 public:  
  /**
   *  @brief Standard constructor for PlotConfig
   *
   *  Sets all members to default values.
   *
   *  @param name Name of this Config object.
   */
  PlotConfig(const std::string& name);
  
  /**
   *  @brief Destructor for PlotConfig
   */
  ~PlotConfig();
  
  /**
   *  @brief Return a color for PDF at given index
   *
   *  If index is larger than internal color map, this function will just return
   *  1.
   *
   *  @param index number of the PDF to get the color for
   *  @return the appropriate color value
   */
  int GetPdfLineColor(int index) const;
  
  /**
   *  @brief Return a line style for PDF at given index
   *
   *  If index is larger than internal line style map, this function will just 
   *  return 1.
   *
   *  @param index number of the PDF to get the line style for
   *  @return the appropriate line style value
   */
  int GetPdfLineStyle(int index) const;
  
  /** @name Getter functions
   *  Implementation of getter functions.
   */
  ///@{
  /**
   * @brief Getter for num_cpu_
   *
   * @see set_num_cpu()
   **/
  int num_cpu() const { return num_cpu_; }
  
  /**
   * @brief Getter for pdf_linecolor_map_
   * 
   * @see set_pdf_linecolor_map()
   **/
  const config::CommaSeparatedList<int>& pdf_linecolor_map() const { return pdf_linecolor_map_; }
  /**
   * @brief Getter for pdf_linestyle_map_
   *
   * @see set_pdf_linestyle_map()
   **/
  const config::CommaSeparatedList<int>& pdf_linestyle_map() const { return pdf_linestyle_map_; }
  
  /**
   * @brief Getter for plot_directory_
   *
   * @see set_plot_directory()
   **/
  std::string plot_directory() const { return plot_directory_; }

  /**
   * @brief Getter for plot_style_
   *
   * @see set_plot_style()
   **/
  std::string plot_style() const { return plot_style_; }

  /**
   * @brief Getter for label_text_
   *
   * @see set_label_text()
   **/
  std::string label_text() const { return label_text_; }

  /**
   * @brief Getter for label_x_
   *
   * @see set_label_x()
   **/
  double label_x() const { return label_x_; }

  /**
   * @brief Getter for label_y_
   *
   * @see set_label_y()
   **/
  double label_y() const { return label_y_; }

  /**
   * @brief Getter for y_axis_label
   *
   * @see set_y_axis_label()
   **/
  std::string y_axis_label() const { return y_axis_label_; }

  /**
   * @brief Getter for plot_appendix_
   *
   * @see set_plot_appendix()
   **/
  std::string plot_appendix() const { return plot_appendix_; }

  /**
   *  @brief Getter for x plot range (where applicable)
   */
  std::pair<double, double> plot_range_x() const { return std::make_pair(plot_range_x_.first(), plot_range_x_.second()); }

  /**
   *  @brief Getter for y plot range (where applicable)
   */
  std::pair<double, double> plot_range_y() const { return std::make_pair(plot_range_y_.first(), plot_range_y_.second()); }

  /**
   *  @brief Getter for additional normalization
   */
  double additional_normalization() const { return additional_normalization_; } 
  ///@}

  /** @name Simultaneous PDF plotting getters
   *  Functions to setup plotting of simultaneous PDFs
   */
  ///@{
  /**
   * @brief Getter for plotting of all individual sub categories of a simultaneous PDF (i.e. long,tagged,2011 vs. down,tagged,2011 vs. ...)
   **/
  bool simultaneous_plot_all_categories() const { return simultaneous_plot_all_categories_; }

  /**
   * @brief Getter for plotting of each slice of a simultaneous PDF (i.e. all long, all tagged, etc.)
   **/
  bool simultaneous_plot_all_slices() const { return simultaneous_plot_all_slices_; }

  /**
   * @brief Getter for simultaneous category labels
   **/
  const std::map<std::string, std::string>& simultaneous_category_labels() const { return simultaneous_category_labels_; }
  ///@}


  /** @name Setter functions
   *  Implementation of setter functions.
   */
  ///@{
  /**
   * @brief Setter for num_cpu_
   *
   * Set number of CPUs to be used in plotting.
   *
   * @param num_cpu number of CPUs to use
   **/
  void set_num_cpu(int num_cpu) { num_cpu_ = num_cpu; }
  
  /**
   * @brief Setter for pdf_linecolor_map_ with config::CommaSeparatedList
   *
   * Set line colors for plotted PDFs as config::CommaSeparatedList. This can 
   * also be set via command line or config file.
   * 
   * @param pdf_linecolors colors to use in same order as PDFs are supplied
   **/
  void set_pdf_linecolor_map(const config::CommaSeparatedList<int>& pdf_linecolors) { pdf_linecolor_map_ = pdf_linecolors; }
  /**
   * @brief Setter for pdf_linecolor_map_ with string
   *
   * Set line colors for plotted PDFs as comma-separated string, e.g. like 
   * "1,4,2,3,5". This option can also be set via command line or config file.
   *
   * @param pdf_linecolors colors to use in same order as PDFs are supplied as comma-separated string (e.g. "1,4,2,3,5")
   **/
  void set_pdf_linecolor_map(const std::string& pdf_linecolors) {
    pdf_linecolor_map_.Parse(pdf_linecolors);
  }
  /**
   * @brief Setter for pdf_linestyle_map_ with config::CommaSeparatedList
   *
   * Set line syles for plotted PDFs as config::CommaSeparatedList. This can
   * also be set via command line or config file.
   *
   * @param pdf_linestyles line styles to use in same order as PDFs are supplied
   **/
  void set_pdf_linestyle_map(const config::CommaSeparatedList<int>& pdf_linestyles) { pdf_linestyle_map_ = pdf_linestyles; }

  /**
   * @brief Setter for pdf_linestyle_map_ with string
   *
   * Set line sytle for plotted PDFs as comma-separated string, e.g. like
   * "1,4,2,3,5". This option can also be set via command line or config file.
   *
   * @param pdf_linestyles line styles to use in same order as PDFs are supplied as comma-separated string (e.g. "1,4,2,3,5")
   **/
  void set_pdf_linestyle_map(const std::string& pdf_linestyles) {
    pdf_linestyle_map_.Parse(pdf_linestyles);
  }
  
  /**
   * @brief Setter for plot_directory_
   *
   * Set plot output directory.
   *
   * @param plot_directory the plot output directory to use
   **/
  void set_plot_directory(const std::string& plot_directory) {
    plot_directory_ = plot_directory;
  }

  /**
   * @brief Setter for plot_style_
   *
   * Set plot style.
   *
   * @param plot_style the plot output directory to use
   **/
  void set_plot_style(const std::string& plot_style) {
    plot_style_ = plot_style;
  }

  /**
   * @brief Setter for label_text_
   *
   * Set text displayed in the label.
   *
   * @param label_text the plot output directory to use
   **/
  void set_label_text(const std::string& label_text) {
    label_text_ = label_text;
  }

  /**
   * @brief Setter for label_x_
   *
   * Set x position of label.
   *
   * @param label_x the x position of the label
   **/
  void set_label_position_x(double label_x) { label_x_ = label_x; }

  /**
   * @brief Setter for label_y_
   *
   * Set y position of label.
   *
   * @param label_y the y position of the label
   **/
  void set_label_position_y(double label_y) { label_y_ = label_y; }

  /**
   * @brief Setter for y_axis_label_
   *
   * Set replacement text of Events in y axis label.
   *
   * @param y_axis_label the string to replace "Events" in y axis label
   **/
  void set_y_axis_label(const std::string& y_axis_label) {
    y_axis_label_ = y_axis_label;
  }

  /**
   * @brief Setter for plot_appendix_ 
   *
   * Set appendix for stacked plot output file name
   * 
   * @param pdf_linecolors colors to use in same order as PDFs are supplied
   **/
  void set_plot_appendix(const std::string& plot_appendix) { plot_appendix_ = plot_appendix; }

  /**
   *  @brief Setter for x plot range (where applicable)
   */
  void set_plot_range_x(double min_x, double max_x) { plot_range_x_.set_first(min_x); plot_range_x_.set_second(max_x); } 

  /**
   *  @brief Setter for y plot range (where applicable)
   */
  void set_plot_range_y(double min_y, double max_y) { plot_range_y_.set_first(min_y); plot_range_y_.set_second(max_y); } 

  /**
   *  @brief Setter for additional normalization
   */
  void set_additional_normalization(double additional_normalization) const { additional_normalization_ = additional_normalization; } 
  ///@}

  /** @name Simultaneous PDF plotting setters/configuration
   *  Functions to setup plotting of simultaneous PDFs
   */
  ///@{
  /**
   * @brief Setter for plotting of all individual sub categories of a simultaneous PDF (i.e. long,tagged,2011 vs. down,tagged,2011 vs. ...)
   **/
  void set_simultaneous_plot_all_categories(bool simultaneous_plot_all_categories) { simultaneous_plot_all_categories_ = simultaneous_plot_all_categories; }

  /**
   * @brief Setter for plotting of each slice of a simultaneous PDF (i.e. all long, all tagged, etc.)
   **/
  void set_simultaneous_plot_all_slices(bool simultaneous_plot_all_slices) { simultaneous_plot_all_slices_ = simultaneous_plot_all_slices; }

  /**
   * @brief Add simultaneous category or slice label
   *
   * @param category string identifying simultaneous category or slice
   * @param label as TLatex string to add on plots
   **/
  void AddSimultaneousCategoryLabel(std::string category, std::string label) { 
    simultaneous_category_labels_.emplace(category, label);
  }
  ///@}

  
  /** @name Stacked plotting support functions
   *  Functions to support stacked plotting into one file
   */
  ///@{
  /**
   *  @brief Open plot stack on demand
   *
   *  This helper function will be called by Plot objects before plotting. If
   *  not openend already, it will open a ROOT plot stack called AllPlots.pdf in
   *  which all be put.
   */
  void OnDemandOpenPlotStack() const;
  
  /**
   *  @brief Close plot stack (for saving plots)
   *
   *  This helper function can be called to close the plot stack in order to 
   *  save the all plots file.
   */
  void ClosePlotStack() const;
  ///@}
  
 protected:
  /** @name Virtual functions
   *  Implementation of pure virtual functions.
   */
  ///@{
  /**
   *  \brief Define options for the derived class.
   *
   *  This function will define all options for the derived CommonConfig class.
   *
   *  @see config::AbsConfig::DefineOptions()
   */
  void DefineOptions();
  
  /**
   *  \brief Load program options into own member variables.
   *
   *  This function will store all options from the variable map into own
   *  members.
   *
   *  @see config::AbsConfig::LoadOptions()
   */
  void LoadOptions();
  
  /**
   *  \brief Print all options for this object.
   *
   *  Virtual function that will print all options for this Config object.
   */
  void PrintOptions() const;
  ///@}
  
 private:
  /**
   *  @brief Color map for PDF lines
   */
  config::CommaSeparatedList<int> pdf_linecolor_map_;
  /**
   *  @brief Line style map for PDF lines
   */
  config::CommaSeparatedList<int> pdf_linestyle_map_;
  /**
   *  @brief Plot output directory
   */
  std::string plot_directory_;

  /**
   *  @brief Plot style to use for plots
   */
  std::string plot_style_;

  /**
   *  @brief TLatex plot label text
   */
  std::string label_text_;

  /**
   *  @brief x position of label
   */
  double label_x_;

  /**
   *  @brief y position of label
   */
  double label_y_;

  /**
   *  @brief TLatex y axis label
   */
  std::string y_axis_label_;

  /**
   *  @brief Number of CPUs to use for plotting
   */
  int num_cpu_;
  
  /** @name Stacked plotting support members
   *  Members to support stacked plotting into one file.
   */
  ///@{
  /**
   *  @brief Stack already opened
   */
  mutable bool plot_stack_open_;
  
  /**
   *  @brief Dummy canvas to create plot stack
   */
  mutable TCanvas* plot_stack_canvas_;

  /**
   *  @brief Appendix for stacked plot file name
   */
  std::string plot_appendix_;
  ///@}

  /**
   *  @brief Plot all individual sub categories of a simultaneous PDF (i.e. long,tagged,2011 vs. down,tagged,2011 vs. ...)
   */
  bool simultaneous_plot_all_categories_;

  /**
   *  @brief Plot each slice of a simultaneous PDF (i.e. all long, all tagged, etc.)
   */
  bool simultaneous_plot_all_slices_;  

  /**
   *  @brief Map for labels for simultaneous categories and slices
   */
  std::map<std::string,std::string> simultaneous_category_labels_;

  /**
   *  @brief x plot range (where applicable)
   */
  config::CommaSeparatedPair<double> plot_range_x_;

  /**
   *  @brief y plot range (where applicable)
   */
  config::CommaSeparatedPair<double> plot_range_y_;

  /**
   *  @brief Additional normalization (where applicable)
   */
  mutable double additional_normalization_;
};

} // namespace plotting
} // namespace doofit
  
#endif // DOOFIT_PLOTTING_PLOT_PLOTCONFIG_h