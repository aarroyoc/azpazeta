/**
* @file azpapilua.hpp
* @brief Description of AzpAPI functions avalible trough AzpVM in AZPScript
* @author Adrián Arroyo Calle
* @date 03/03/2013
*/
/**
* @class AzpAPI
* @brief Imaginary class for AzpAPI Lua docs
* @verbatim
AzpAPI is a imaginary class for the AzpAPI functions in Lua avalible trough AzpVM in AZPScript. This class is not a C++ class.
* @endverbatim
*/
class AzpAPI {
public:
/**
* @brief Start a AZPScript context
* @param Name The name of the Script
* @param Author The authors name
* @param Version The version of the script
* @returns The operating system and the version of Azpazeta
* @returns The version of Azpazeta
* @note This documentation uses C/C++ style in Lua functions. The return values exists
* @see azpConsole
*/
void azpInit(Name,Author,Version);
/**
* @brief Writes a Phrase in the Log Window
* @param Phrase The phrase to the Log Window
* @returns Nothing
* @note This documentation uses C/C++ style in Lua functions. The return values exists
* @see azpInit
*/
void azpConsole(Phrase);
};
