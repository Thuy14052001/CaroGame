#ifndef INIFILE_H
#define INIFILE_H

#include <iostream>
#include "inipp.h"
#include <fstream>

using namespace std;

class IniFile
{
private:
    IniFile();

public:
    IniFile(string strFileDir, string strFileName);

private:
    inipp::Ini<char> _ini;
    string _strFullFileDir;
    string _strFileDir;
    string _strFileName;

public:
    void WriteStringValue(string strSection, string strKey, string strValue);
    void WriteBoolValue(string strSection, string strKey, bool bValue);
    void WriteIntValue(string strSection, string strKey, int nValue);
    void WriteDoubleValue(string strSection, string strKey, double dValue);

    string ReadStringValue(string strSection, string strKey, string strDefaultValue);
    bool ReadBoolValue(string strSection, string strKey, bool bDefaultValue);
    int ReadIntValue(string strSection, string strKey, int nDefaultValue);
    double ReadDoubleValue(string strSection, string strKey, double dDefaultValue);
};

#endif // INIFILE_H
