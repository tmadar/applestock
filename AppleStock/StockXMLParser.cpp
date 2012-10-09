#include "stdafx.h"
#include "StockXMLParser.h"
#include "AppleStockUpdater.h"

#pragma once

_COM_SMARTPTR_TYPEDEF(IXMLDOMDocument2, __uuidof(IXMLDOMDocument2));
_COM_SMARTPTR_TYPEDEF(IXMLDOMParseError, __uuidof(IXMLDOMParseError));

StockXMLParser::StockXMLParser(void)
{
	document = NULL;

	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(DOMCLSID, NULL, CLSCTX_INPROC, IID_IXMLDOMDocument2, (LPVOID *)&document);

}

StockXMLParser::~StockXMLParser(void)
{

}

BSTR StockXMLParser::parseXML(_bstr_t xml) {
	StockXMLParser parser;
	AppleStockUpdater stockUpdater;

	BSTR result = NULL;
	VARIANT_BOOL success;
	if (parser.document == NULL)
		result = NULL;

	parser.document->put_validateOnParse(VARIANT_FALSE);
	parser.document->loadXML(xml, &success);
	IXMLDOMNodeList* nodeList = NULL;
	long length = 1;
	if (success == VARIANT_FALSE)
		result = NULL;

	parser.document->setProperty(_T("SelectionLanguage"), _variant_t("XPath"));
	parser.document->selectNodes(_T("//last"), &nodeList); 

	nodeList->get_length(&length);

	if (length >= 1) {
		IXMLDOMNode *node = NULL;
		IXMLDOMNode *innerNode = NULL;

		IXMLDOMNamedNodeMap *stupidMap = NULL;
		ATL::CComBSTR text;

		nodeList->get_item(0, &node);
		node->get_attributes(&stupidMap);
		stupidMap->getNamedItem(_T("data"), &innerNode);
		innerNode->get_text(&text);

		result = text;
	}
	return result;
}
