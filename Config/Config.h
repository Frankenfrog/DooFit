/** \class Config
 *  \brief DooFit Config base class.
 *
 *  This is the base class for all DooFit config objects. It offers
 *  configuration via the boost::program_options package.
 */

#ifndef CONFIG_h
#define CONFIG_h

// STL
#include <string>
#include <vector>

// Boost
#include <boost/program_options.hpp>

// ROOT

// RooFit

// forward declarations


class Config {
  
 public:
  
  /**
   *  \brief Standard constructor.
   *
   *  Sets all memebers to default values.
   */
  Config();
  
  /**
   *  \brief Destructor.
   */
  virtual ~Config();
  
  /**
   *  \brief Initialize options with input from command line.
   *
   *  Using argc and argv this function initializes all options using 
   *  boost::program_options.
   *
   *  @param argc Number of arguments.
   *  @param argv char* array with arguments.
   */
  void InitializeOptions(int argc, char* argv[]);

  /**
   *  \brief Initialize options with with string vector.
   *
   *  Using option_vector this function initializes all options using 
   *  boost::program_options.
   *
   *  @param option_vector vector of options not parsed by any other Config
   *                       classes (i.e. unrecognized options).
   */
  void InitializeOptions(const std::vector<std::string>& option_vector);
  
  /**
   *  \brief Print all options.
   *
   *  Virtual function that will print all options for this config object.
   */
  virtual void Print() = 0;
      
  
  /**
   *  \brief Getter for program options description.
   */
  const boost::program_options::options_description& desc(){
    return desc_;
  }

  /**
   *  \brief Getter for program options variables map.
   */
  const boost::program_options::variables_map& var_map(){
    return var_map_;
  }
  
  /**
   *  \brief Getter for options that could not be parsed by this module.
   */
  const std::vector<std::string>& unrec_options(){
    return unrec_options_;
  }
  
 protected:
  /** @defgroup virt-functs Pure virtual functions for derived classes 
   *  These are pure virtual functions to be implemented in derived classes.
   *  @{
   */
  
  /**
   *  \brief Define all program options.
   *
   *  Virtual function that will define all program options for this config 
   *  object. It is automatically called by constructors. All option 
   *  descriptions need to be added to Config::descs_ and Config::descs_hidden_
   *  (depending on if sections are to be visible or not). Individual entries
   *  in these vectors are for individual option categories/sections.
   */
  virtual void DefineOptions() = 0;
  
  /**
   *  \brief Load program options into own member variables.
   *
   *  Virtual function that will load all program options for this config 
   *  object from the internal variables map into own member variables. It is 
   *  automatically called by Config::InitializeOptions(). 
   */
  virtual void LoadOptions() = 0;
  /** @} */ // end of virt-functs

  
  /**
   *  \brief Name of the configuration object.
   */
  std::string name_;
  
  /** 
   *  \brief Program options description for all options.
   */
  boost::program_options::options_description desc_;
  /** 
   *  \brief Program options variables map for all options.
   */
  boost::program_options::variables_map var_map_;
  
  /** 
   *  \brief Program options description for non-hidden options.
   */
  boost::program_options::options_description desc_visible_;
  /** 
   *  \brief Container for all non-hidden program option descriptions.
   *
   *  Each entry is for one group/category of options to be set. All entries 
   *  will be merged into Config::desc_. As the boost developers were so 
   *  prospective to build boost::program_options::options_description
   *  in such a way that they cannot be copied or assigned, we need to keep a 
   *  vector of pointers instead of a vector of real objects.
   */
  std::vector <boost::program_options::options_description*> descs_visible_;
  
  /** 
   *  \brief Program options description for hidden options.
   */
  boost::program_options::options_description desc_hidden_;
  /** 
   *  \brief Container for all hidden program option descriptions.
   *
   *  Each entry is for one group/category of options to be set. All entries 
   *  will be merged into \link Config::desc_hidden_. As the boost developers
   *  were so prospective to build boost::program_options::options_description
   *  in such a way that they cannot be copied or assigned, we need to keep a 
   *  vector of pointers instead of a vector of real objects.
   */
  std::vector <boost::program_options::options_description*> descs_hidden_;
  
  /** 
   *  \brief Vector of unrecognized program options.
   */
  std::vector<std::string> unrec_options_;
  
 private: 
  /**
   *  \brief Combine all previously defined option descriptions.
   *
   *  Iteratre through Config::descs_ and Config::descs_hidden_ and combine them
   *  into Config::desc_ and Config::desc_hidden_. This function will be called
   *  automatically through the constructors.
   */
  void CombineOptions();
};

#endif //CONFIG_h
