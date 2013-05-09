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
/**
* @brief Display the Azpazeta logo
* @returns Nothing
* @verbatim 
Used for exit the map, or loading the map
* @endverbatim
* @note This documentation uses C/C++ style in Lua functions. The return values exists
* @see azpMosaic
*/
void azpLogo();
/**
* @brief Waits the selected milliseconds
* @param Milliseconds The time to wait in milliseconds
* @returns Nothing
* @note This documentation uses C/C++ style in Lua functions. The return values exists
* @see azpLogo
*/
void azpWait(Milliseconds);
/**
* @brief Display the Azpazeta mosaic
* @returns Nothing
* @verbatim 
Used for normal play
* @endverbatim
* @note This documentation uses C/C++ style in Lua functions. The return values exists
* @see azpLogo
*/
void azpMosaic();
/**
* @brief Executes a AZPScript
* @param File The AZPScript file for execute
* @param Securitylevel The security level of the script, by default azpVM_SECURE
* @param The script is in the home folder. You must set it to "TRUE" if you made maps for Azpazeta Market
* @returns Nothing
* @verbatim 
Security level can be: azpVM_FULL, azpVM_SECURE, azpVM_INTERNET, azpVM_INSTALLATION and azpVM_TEST
* @endverbatim
* @note This documentation uses C/C++ style in Lua functions. The return values exists
* @see azpLogo
*/
void azpExecute(File,Securitylevel,Home);
/**
* @brief Gets a var from Database storage
* @param File The DataBase file to open
* @param Var The namw of the var to get
* @param Home If the script is under AZP_HOME instead AZP_ROOT set it to TRUE
* @returns the value of the var
* @note This documentation uses C/C++ style in Lua functions. The return values exists
* @see azpSet
*/
void azpGet(Var,File,Home);

};
