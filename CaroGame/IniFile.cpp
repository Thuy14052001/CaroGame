#include "IniFile.h"

IniFile::IniFile()
{
}

IniFile::IniFile(string strFileDir, string strFileName)
{
    _strFileDir = strFileDir;
    _strFileName = strFileName;
    _strFullFileDir = strFileDir + "\\" + strFileName;

    // Read and Parsing information in file
    ifstream inStream(_strFullFileDir);
    _ini.parse(inStream);
}

//////////////////////////////////////////////////////////////////////////////
/// Write Value to INI file

void IniFile::WriteStringValue(string strSection, string strKey, string strValue)
{
    _ini.sections[strSection][strKey] = strValue;

    // Write data to file.
    ofstream outStream(_strFullFileDir);
    _ini.generate(outStream);
}

void IniFile::WriteBoolValue(string strSection, string strKey, bool bValue)
{
    _ini.sections[strSection][strKey] = bValue ? "true" : "false";

     // Write data to file.
    ofstream outStream(_strFullFileDir);
    _ini.generate(outStream);
}

void IniFile::WriteIntValue(string strSection, string strKey, int nValue)
{
    _ini.sections[strSection][strKey] = to_string(nValue);

     // Write data to file.
     ofstream outStream(_strFullFileDir);
    _ini.generate(outStream);
}

void IniFile::WriteDoubleValue(string strSection, string strKey, double dValue)
{
    _ini.sections[strSection][strKey] = to_string(dValue);

    // Write data to file.
    ofstream outStream(_strFullFileDir);
    _ini.generate(outStream);
}

/// End Write Value to INI file
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/// Read Values from INI file
///
string IniFile::ReadStringValue(string strSection, string strKey, string strDefaultValue)
{
    string strReturn = strDefaultValue;
    inipp::extract(_ini.sections[strSection][strKey], strReturn);

    return  strReturn;
}

bool IniFile::ReadBoolValue(string strSection, string strKey, bool bDefaultValue)
{
    bool bReturn = bDefaultValue;
    inipp::extract(_ini.sections[strSection][strKey], bReturn);

    return bReturn;
}

int IniFile::ReadIntValue(string strSection, string strKey, int nDefaultValue)
{
    int nReturn = nDefaultValue;
    inipp::extract(_ini.sections[strSection][strKey], nReturn);

    return nReturn;
}

double IniFile::ReadDoubleValue(string strSection, string strKey, double dDefaultValue)
{
    double dReturn = dDefaultValue;
    inipp::extract(_ini.sections[strSection][strKey], dReturn);

    return dReturn;
}

/// Read Values from INI file
//////////////////////////////////////////////////////////////////////////////
