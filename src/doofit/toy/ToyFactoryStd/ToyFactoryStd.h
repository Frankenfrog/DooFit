#ifndef TOYFACTORYSTD_h
#define TOYFACTORYSTD_h

// STL
#include <cstring>
#include <csetjmp>

// ROOT
#include "TClass.h"

// from RooFit
#include "RooAbsPdf.h"
#include "RooArgSet.h"

// from project
#include "doofit/toy/ToyFactoryStd/ToyFactoryStdConfig.h"

// forward declarations
class RooDataSet;
class RooArgSet;
class TFile;
namespace doofit { namespace builder { class EasyPdf; }}
namespace doofit {
namespace config {
  class CommonConfig; 
}
  
namespace toy {
  /** \class ToyFactoryStd
   *  \brief Standard toy factory for DooFit generating toy samples
   *
   *  This class handles generation of toy samples for a given pdf. Generation 
   *  should be as smart as possible involving automatic decomposition of more 
   *  complex pdfs and generation of proto datasets based on given distributions.
   * 
   *  @section general General usage
   *
   *  General configuration is handled via Toy::ToyFactoryStdConfig. One needs
   *  to set the PDF for generation (either via pointer to a RooAbsPdf or via 
   *  combination of workspace pointer and PDF name on workspace or via 
   *  specifying a file containing the workspace and PDF name on workspace). The 
   *  set of observables to generate the toy dataset needs to be set as well 
   *  (again either directly or via name on workspace). 
   *
   *  Although a workspace is not necessarily needed for generation, some 
   *  features (like proto dataset generation) need a workspace to contain PDFs
   *  and argument sets.
   *
   *  Generation of the dataset can be invoked via ToyFactoryStd::Generate(). 
   *  This will return a dataset pointer with the generated data (can also be 
   *  configured to write dataset to a file). ToyFactoryStd::Generate() will 
   *  try to invoke specialised generator functions which are able to decompose
   *  the PDF into sub PDFs and generate those independently.
   *
   *  @section proto-sets Proto dataset generation
   *
   *  The need for proto datasets cannot be detected automatically. Therefore, 
   *  one needs to specify for each sub PDF a section name. Based on the 
   *  settings in this section in the config file, a new toy factory will be 
   *  created to generate the proto dataset. Workspace and observables argset 
   *  are taken from the mother toy factory. Yield and fixed size are set 
   *  automatically. The toy factory will read other settings from the specified 
   *  section. The generated proto data will then be used for the specified 
   *  sub PDF.
   *
   *  @see Toy::ToyFactoryStdConfig::set_proto_sections(const std::vector<config::CommaSeparatedPair>&)
   *  @see Toy::ToyFactoryStdConfig::AddProtoSections(const config::CommaSeparatedPair&)
   *
   *  @todo Proto sets need to be split for sub PDFs.
   *  @todo Test proto generation without externally set yield.
   *
   *  @bug If an external yield is given for extended PDFs, the PDFs will be 
   *       generated correctly according to this number. However, the pulls will 
   *       all be wrong as the internal PDF yield will be used to calculate the
   *       pull.
   *
   *  @author Florian Kruse
   */
  
  class ToyFactoryStd {
  public:
    /**
     *  \brief Default constructor for ToyFactoryStd
     *
     *  This is the default constructor for ToyFactoryStd involving general 
     *  configuration @a cfg_com and specific configuration @a cfg_tfac.
     *
     *  @param cfg_com CommonConfig for the general configuration.
     *  @param cfg_tfac ToyFactoryStdConfig for this specific toy factory.
     */
    ToyFactoryStd(const config::CommonConfig& cfg_com, const ToyFactoryStdConfig& cfg_tfac);
    
    /**
     *  \brief Destructor for ToyFactoryStd
     */
    ~ToyFactoryStd();
    
    /**
     *  \brief Generate a toy sample
     *
     *  Based on all settings in the supplied ToyFactoryStdConfig object, generate
     *  a toy sample. Please note comment on ownership of returned dataset.
     *
     *  \return Pointer to the generated sample. ToyFactoryStd does not assume 
     *          ownership of this sample. Therefore, the invoker of this function
     *          must take care of proper deletion afterwards. If configured to
     *          write dataset to a file, this function will return a null 
     *          pointer.
     */
    RooDataSet* Generate();

    const RooArgSet& set_constrained_parameters() const { return set_constrained_parameters_; }
    
  protected:
    
  private:
    /** @name PDF type functions
     *  Functions to check for specific PDF types.
     */
    ///@{
    /**
     *  @brief Checks if a RooAbsPdf is decomposable
     *
     *  @param pdf pdf to check for decomposability
     *  @return whether pdf is decomposable or not
     */
    bool PdfIsDecomposable(const RooAbsPdf& pdf) const;
    
    /**
     *  @brief Checks if a RooAbsPdf is an extended pdf
     *
     *  @param pdf pdf to check for extended pdf
     *  @return whether pdf is extended or not
     */
    bool PdfIsExtended(const RooAbsPdf& pdf) const {
      if (std::strcmp(pdf.IsA()->GetName(),"RooExtendPdf") == 0) {
        return true;
      } else {
        return false;
      }
    }
    
    /**
     *  @brief Checks if a RooAbsPdf is an added pdf
     *
     *  @param pdf pdf to check for added pdf
     *  @return whether pdf is added or not
     */
    bool PdfIsAdded(const RooAbsPdf& pdf) const {
      if (std::strcmp(pdf.IsA()->GetName(),"RooAddPdf") == 0) {
        return true;
      } else {
        return false;
      }
    }
    
    /**
     *  @brief Checks if a RooAbsPdf is a product pdf
     *
     *  @param pdf pdf to check for product pdf
     *  @return whether pdf is product or not
     */
    bool PdfIsProduct(const RooAbsPdf& pdf) const {
      if (std::strcmp(pdf.IsA()->GetName(),"RooProdPdf") == 0) {
        return true;
      } else {
        return false;
      }
    }
    
    /**
     *  @brief Checks if a RooAbsPdf is a simultaneous pdf
     *
     *  @param pdf pdf to check for simultaneous pdf
     *  @return whether pdf is product or not
     */
    bool PdfIsSimultaneous(const RooAbsPdf& pdf) const {
      if (std::strcmp(pdf.IsA()->GetName(),"RooSimultaneous") == 0) {
        return true;
      } else {
        return false;
      }
    }
    ///@}
    
    /** @name Parameter value functions
     *  Functions to set parameter values before and after generation
     */
    ///@{
    /**
     *  @brief Set parameters according to the specified parameter file
     *
     *  All parameters of the PDF to generate will be set according to the 
     *  parameter file set in the Config object.
     */
    void ReadParametersFromFile();
    
    /**
     *  @brief Draw constrained parameters from constraining PDFs
     *
     *  Parameters described via constraining PDFs will be drawn accordingly to
     *  assure that a constrained fit situation is handled correctly.
     */
    void DrawConstrainedParameters();
    ///@}
    
    /** @name Dataset combination functions
     *  Functions to combine sub datasets together (merge, append)
     */
    ///@{
    /**
     *  @brief Merge two datasets
     *
     *  This functions merges a dataset into another. A sanity check for 
     *  compatibility is applied (if not, a DatasetsNotDisjointException is 
     *  thrown). After merging, the second or slave dataset is deleted (if not
     *  specified otherwise).
     *
     *  For some columns overlap might be acceptable (e.g. for proto datasets).
     *  An ignore argset can be supplied. Any column which is also in the ifnore
     *  set will not create an exception. The caller must make sure that the 
     *  data with these columns is identical in both datasets (otherwise, 
     *  merging does not make sense).
     *
     *  @param master_dataset first dataset to merge the second dataset into
     *  @param slave_dataset second dataset to merge into the first
     *  @param ignore_argset argset with columns to ignore in sanity check
     *  @param delete_slave whether slave dataset is to be deleted (default: 
     *                      yes)
     */
    void MergeDatasets(RooDataSet* master_dataset, RooDataSet* slave_dataset, const std::vector<RooDataSet*>* ignore_sets=NULL, bool delete_slave=true) const;

    /**
     *  @brief Mix two datasets with overlapping columns
     *
     *  This functions merges a dataset into another. A full overlap of 
     *  variables is assumed and the slave dataset must be smaller or of equal
     *  size compared to the master dataset.
     *
     *  In case the slave is smaller only a fraction of its events is mixed into
     *  the master set.
     *
     *  @warning Both individual datasets will not be changed or deleted!
     *
     *  @param master_dataset first dataset to merge the second dataset into
     *  @param slave_dataset second dataset to merge into the first
     *                      yes)
     *
     *  @return the merged dataset
     */
    RooDataSet* MixMergeDatasets(RooDataSet* master_dataset, RooDataSet* slave_dataset) const;
    
    /**
     *  @brief Append a dataset to another
     *
     *  This functions appends a dataset to another. A sanity check for 
     *  compatibility is applied (i.e. if datasets contain identical columns; if
     *  not, a DatasetsNotAppendableException is thrown). 
     * 
     *  The new dataset will be returned with mixed entries, i.e. for any random
     *  drawn sample the expected distribution of master vs. slave entries is 
     *  according the ratio of both sample sizes. This is done to avoid samples
     *  where only a few entries are drawn (e.g. from proto datasets) and 
     *  drawing from only master or slave will bias the results. Example:
     *  The sets MMMMMM and SSSSS will be merged to MSSMMSMSSMM and not 
     *  MMMMMMSSSSS.
     *
     *  @warning Both individual datasets will not be changed or deleted!
     *
     *  @param master_dataset first dataset to append the second dataset to
     *  @param slave_dataset second dataset to append to the first
     */
    RooDataSet* AppendDatasets(RooDataSet* master_dataset, RooDataSet* slave_dataset) const;
    
    /**
     *  @brief Merge dataset vector into new dataset
     *
     *  This functions merges separate datasets in a dataset vector into a new
     *  dataset. The new dataset has no connection to the datasets in the 
     *  vector. The caller takes ownership of this new dataset and is 
     *  responsible for deleting it after use. Deleting this dataset will not
     *  affect the datasets in the vector.
     *
     *  @param datasets vectors of datasets to merge
     *  @return a new dataset merged from all elements of the vector 
     */
    RooDataSet* MergeDatasetVector(const std::vector<RooDataSet*>& datasets) const;
    ///@}
    
    /** @name Proto dataset functions
     *  Functions specific fot proto dataset generation
     */
    ///@{
    /**
     *  @brief Check if PDF name has an entry in proto sections and return those
     *
     *  For a given PDF name the vector of proto section is checked for a match.
     *  The sub vector of matches is returned.
     *
     *  @param pdf_name The PDF name to be tested
     *  @return the sub vector of sections for this PDF name
     */
    std::vector<config::CommaSeparatedPair<std::string>> GetPdfProtoSections(const std::string& pdf_name) const;
    ///@}
    
    /** @name Generator functions
     *  Functions to generate toy samples for specific PDF (types).
     */
    ///@{
    /**
     *  @brief Generate a toy sample for a given PDF.
     *
     *  Helper function to be used by ToyFactoryStd::Generate().
     *
     *  @param pdf PDF to generate sample for
     *  @param argset_generation_observables argument set with variables in which 
     *                                       dimensions to generate
     *  @param expected_yield Expected yield to generate (if equals 0, then get 
     *                        yield from PDF itself)
     *  @param extended determine if PDF is to be generated with Extended() 
     *                  RooCmdArg. If so, the generated yield will be poisson 
     *                  distributed around the expected value.
     *  @param proto_data Proto dataset to use for this PDF. 
     *  @return Pointer to the generated sample. ToyFactoryStd does not assume 
     *          ownership of this sample. Therefore, the invoker of this function
     *          must take care of proper deletion afterwards.
     */
    RooDataSet* GenerateForPdf(RooAbsPdf& pdf, const RooArgSet& argset_generation_observables, double expected_yield=0, bool extended=true, std::vector<RooDataSet*> proto_data=std::vector<RooDataSet*>()) const;
    
    /**
     *  @brief Generate a toy sample for a given RooAddPdf.
     *
     *  Helper function to be used by ToyFactoryStd::GenerateForPdf().
     *
     *  @param pdf PDF to generate sample for
     *  @param argset_generation_observables argument set with variables in which 
     *                                       dimensions to generate
     *  @param expected_yield Expected yield to generate (if equals 0, then get 
     *                        yield from PDF itself)
     *  @param extended determine if PDF is to be generated with Extended() 
     *                  RooCmdArg. If so, the generated yield will be poisson 
     *                  distributed around the expected value.
     *  @param proto_data Proto dataset to use for this PDF. 
     *  @return Pointer to the generated sample. ToyFactoryStd does not assume 
     *          ownership of this sample. Therefore, the invoker of this function
     *          must take care of proper deletion afterwards.
     */
    RooDataSet* GenerateForAddedPdf(RooAbsPdf& pdf, const RooArgSet& argset_generation_observables, double expected_yield=0, bool extended=true, std::vector<RooDataSet*> proto_data=std::vector<RooDataSet*>()) const;
    
    /**
     *  @brief Generate a toy sample for a given RooProdPdf.
     *
     *  Helper function to be used by ToyFactoryStd::GenerateForPdf().
     *
     *  @param pdf PDF to generate sample for
     *  @param argset_generation_observables Argument set with variables in which 
     *                                       dimensions to generate
     *  @param expected_yield Expected yield to generate (if equals 0, then get 
     *                        yield from PDF itself)
     *  @param extended determine if PDF is to be generated with Extended() 
     *                  RooCmdArg. If so, the generated yield will be poisson 
     *                  distributed around the expected value.
     *  @param proto_data Proto dataset to use for this PDF. 
     *  @return Pointer to the generated sample. ToyFactoryStd does not assume 
     *          ownership of this sample. Therefore, the invoker of this function
     *          must take care of proper deletion afterwards.
     *  @todo check for PDF arguments to be uncorrelated
     */
    RooDataSet* GenerateForProductPdf(RooAbsPdf& pdf, const RooArgSet& argset_generation_observables, double expected_yield=0, bool extended=true, std::vector<RooDataSet*> proto_data=std::vector<RooDataSet*>()) const;
    
    /**
     *  @brief Generate a toy sample for a given RooSimultaneous.
     *
     *  Helper function to be used by ToyFactoryStd::GenerateForPdf().
     *
     *  @param pdf PDF to generate sample for
     *  @param argset_generation_observables Argument set with variables in which 
     *                                       dimensions to generate
     *  @param expected_yield Expected yield to generate (if equals 0, then get 
     *                        yield from PDF itself)
     *  @param extended determine if PDF is to be generated with Extended() 
     *                  RooCmdArg. If so, the generated yield will be poisson 
     *                  distributed around the expected value.
     *  @param proto_data Proto dataset to use for this PDF. 
     *  @return Pointer to the generated sample. ToyFactoryStd does not assume 
     *          ownership of this sample. Therefore, the invoker of this function
     *          must take care of proper deletion afterwards.
     *  @todo check for PDF arguments to be uncorrelated
     */
    RooDataSet* GenerateForSimultaneousPdf(RooAbsPdf& pdf, const RooArgSet& argset_generation_observables, double expected_yield=0, bool extended=true, std::vector<RooDataSet*> proto_data=std::vector<RooDataSet*>()) const;
    
    /**
     *  @brief Generate a toy sample for discrete variables.
     *
     *  Helper function to be used by ToyFactoryStd::Generate().
     *
     *  @param discrete_probabilities Vector of DiscreteProbabilityDistribution to 
     *                                generate sample for
     *  @param argset_generation_observables Argument set with variables in which 
     *                                       dimensions to generate
     *  @param argset_already_generated Argument set with variables already 
     *                                  generated
     *  @param yield Yield to generate
     *  @return Pointer to the generated sample. ToyFactoryStd does not assume 
     *          ownership of this sample. Therefore, the invoker of this function
     *          must take care of proper deletion afterwards.
     *  @todo check for PDF arguments to be uncorrelated
     */
    RooDataSet* GenerateDiscreteSample(const std::vector<config::DiscreteProbabilityDistribution>& discrete_probabilities, const RooArgSet& argset_generation_observables, const RooArgSet& argset_already_generated, int yield) const;
    
    /**
     *  @brief Generate a proto sample for a given proto section
     *
     *  Helper function to be used by ToyFactoryStd::GenerateForPdf(). For a 
     *  given proto section as config::CommaSeparatedPair it will create a new
     *  ToyFactoryStd that will generate the proto set itself. The proto_section
     *  is a section in the config file that configures this proto set. 
     *  Workspace and observables argset are taken from this toy factory. Yield 
     *  and fixed size are set automatically.
     *
     *  @param pdf PDF to generate sample for
     *  @param proto_section Section in the config file to configure the proto
     *                       dataset
     *  @param argset_generation_observables Argument set with variables in which 
     *                                       dimensions to generate
     *  @param easypdf EasyPdf builder to use for generation
     *  @param workspace RooWorkspace to use for generation
     *  @param yield Yield to generate
     *  @return Pointer to the generated sample. ToyFactoryStd does not assume 
     *          ownership of this sample. Therefore, the invoker of this function
     *          must take care of proper deletion afterwards.
     */
    RooDataSet* GenerateProtoSample(const RooAbsPdf& pdf, const config::CommaSeparatedPair<std::string>& proto_section, const RooArgSet& argset_generation_observables, doofit::builder::EasyPdf* easypdf, RooWorkspace* workspace, int yield) const;
    ///@}
    
    /** @name Helper functions
     *  Functions to do other helper tasks
     */
    ///@{
    /**
     *  @brief Signal handler for RooFit raising SIGABRT
     */    
    static void SignalHandler(int signum);
    ///@}

    /**
     *  \brief CommonConfig instance to use
     */
    const config::CommonConfig& config_common_;
    /**
     *  \brief ToyFactoryStdConfig instance to use
     */
    const ToyFactoryStdConfig& config_toyfactory_;

    /**
     *  @brief Argset of drawn constrained parameters
     */
    RooArgSet set_constrained_parameters_;

    static bool signal_caught_;
    static jmp_buf jump_buffer_;
  };
  
  /** \struct NotGeneratingDataException
   *  \brief Exception for not generating any data
   */
  struct NotGeneratingDataException: public virtual boost::exception, public virtual std::exception { 
    virtual const char* what() const throw() { return "Not generating any data"; }
  };

  /** \struct NotGeneratingDataException
   *  \brief Exception for not generating any data
   */
  struct RooFitSendingSIGABRTException: public virtual boost::exception, public virtual std::exception { 
    virtual const char* what() const throw() { return "RooFit sent SIGABRT"; }
  };
  
  /** \struct NotGeneratingDiscreteData
   *  \brief Exception for not generating discrete data
   */
  struct NotGeneratingDiscreteData: public virtual boost::exception, public virtual std::exception { 
    virtual const char* what() const throw() { return "Not generating discrete data"; }
  };
  
  /** \struct DatasetsNotDisjointException
   *  \brief Exception for trying to merge non-disjoint datasets
   */
  struct DatasetsNotDisjointException: public virtual boost::exception, public virtual std::exception { 
    virtual const char* what() const throw() { return "Trying to merge non-disjoint datasets"; }
  };
  
  /** \struct DatasetsNotAppendableException
   *  \brief Exception for trying to merge non-appendable datasets
   */
  struct DatasetsNotAppendableException: public virtual boost::exception, public virtual std::exception { 
    virtual const char* what() const throw() { return "Trying to merge non-appendable datasets"; }
  };
} // namespace toy
} // namespace doofit

#endif // TOYFACTORYSTD_h
