#include "Builder/FitModelBrewery/Recipe/Recipe.h"

// from STL

// from project
/// from Utils
#include "Utils/MsgStream.h"

/// from Builder/FitModelBrewery
#include "Builder/FitModelBrewery/Recipe/Dimension/DiscreteDimension.h"
#include "Builder/FitModelBrewery/Recipe/Dimension/RealDimension.h"

#include "Builder/FitModelBrewery/Recipe/Parameter/StandardParameter.h"
#include "Builder/FitModelBrewery/Recipe/Parameter/UnblindUniformParameter.h"
#include "Builder/FitModelBrewery/Recipe/Parameter/FormulaParameter.h"

namespace builder {
namespace fitmodelbrewery {

Recipe::Recipe() 
    : dims_real_(),
      dims_discrete_(),
      params_std_(),
      params_bldunif_(),
      params_formula_(),
      is_ready(false),
      is_consistent(false)
{
  
}

Recipe::~Recipe() {
  
}

// templating?
void Recipe::RegisterRecipeElement(const DiscreteDimension& dim_discrete) {
  // check if any element with the same name exists
  if (RecipeElementExists(dim_discrete.GetName())){
    throw ExcRecipeRegistrationFailed();
  }  
}

void Recipe::RegisterRecipeElement(const RealDimension& dim_real) {
  // check if any element with the same name exists
  if (RecipeElementExists(dim_real.GetName())){
    throw ExcRecipeRegistrationFailed();
  }
  else {
    pair<string,RealDimension> dim_real_entry(dim_real.GetName(), RealDimension(dim_real));
    dims_real_.insert(dim_real_entry);
  }
}

void Recipe::RegisterRecipeElement(const StandardParameter& param_std) {
  // check if any element with the same name exists
  if (RecipeElementExists(param_std.GetName())){
    throw ExcRecipeRegistrationFailed();
  }
  else {
    pair<string,StandardParameter> param_std_entry(param_std.GetName(), StandardParameter(param_std));
    params_std_.insert(param_std_entry);
  }
  
}
// 
// void Recipe::RegisterRecipeElement(const UnblindUniformParameter& param_bldunif) {
//   // check if any element with the same name exists
//   if (RecipeElementExists(param_bldunif.GetName())){
//     throw ExcRecipeRegistrationFailed();
//   }
// }
// 
// void Recipe::RegisterRecipeElement(const FormulaParameter& param_formula) {
//   // check if any element with the same name exists
//   if (RecipeElementExists(param_formula.GetName())){
//     throw ExcRecipeRegistrationFailed();
//   }
//}

bool Recipe::RecipeElementExists(const std::string& search_name) {
  if (dims_real_.find(search_name) != dims_real_.end()) return true;
  else if (dims_discrete_.find(search_name) != dims_discrete_.end()) return true;
  else if (params_std_.find(search_name) != params_std_.end()) return true;
  else if (params_bldunif_.find(search_name) != params_bldunif_.end()) return true;
  else if (params_formula_.find(search_name) != params_formula_.end()) return true;
  else return false;
}


} // namespace fitmodelbrewery
} // namespace builder
