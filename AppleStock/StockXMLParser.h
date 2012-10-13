#include <atlbase.h>
#include <atlapp.h>
#include <atlmisc.h>
#include <atlstr.h>
#include <atlmisc.h>
#include "INet.h"
#include <MsXml6.h>
#include <comdef.h>

#define DOMCLSID CLSID_DOMDocument60
#pragma comment(lib, "msxml6.lib")

class StockXMLParser
{
	public:
		WTL::CString test;
		IXMLDOMDocument2* document;
		StockXMLParser(void);
		~StockXMLParser(void);
		BSTR StockXMLParser::parseXML(_bstr_t xml);
};