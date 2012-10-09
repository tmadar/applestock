#include "stdafx.h"
#include "CppUnitTest.h"
#include "AppleStockUpdater.h"
#include "StockXMLParser.h"
#include <regex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:


		TEST_METHOD(VerifyAppleStockUpdaterIsConstructed)
		{
			AppleStockUpdater apple;
			Assert::IsFalse(apple.timeToDie);
		}

		TEST_METHOD(VerifyStockXMLParserIsConstructed)
		{
			StockXMLParser parser;
			Assert::IsNotNull(parser.document);
		}


		TEST_METHOD(TestMethodLoadHtml)
		{
			StockXMLParser parser;
			AppleStockUpdater stockUpdater;
			stockUpdater.GetStockInfo();
			WTL::CString result = parser.parseXML((_bstr_t) stockUpdater.stockPriceXml);
			const char *reg_esp = "\\d+\\.\\d+";
			std::regex rgx(reg_esp);

			CT2CA converter(result);
			std::string cppResult(converter);
			bool match = std::regex_match(cppResult, rgx);
			Assert::IsTrue(match);
		}

		TEST_METHOD(TestMethodLoadHtmlPreloaded)
		{
			StockXMLParser parser;
			_bstr_t xml = "<?xml version=\"1.0\"?><xml_api_reply version=\"1\"><finance module_id=\"0\" tab_id=\"0\" mobile_row=\"0\" mobile_zipped=\"1\" row=\"0\" section=\"0\" ><symbol data=\"AAPL\"/><pretty_symbol data=\"AAPL\"/><symbol_lookup_url data=\"/finance?client=ig&amp;q=AAPL\"/><company data=\"Apple Inc.\"/><exchange data=\"Nasdaq\"/><exchange_timezone data=\"ET\"/><exchange_utc_offset data=\"+05:00\"/><exchange_closing data=\"960\"/><divisor data=\"2\"/><currency data=\"USD\"/><last data=\"638.17\"/><high data=\"647.56\"/><low data=\"636.11\"/><volume data=\"22759442\"/><avg_volume data=\"16351\"/><market_cap data=\"598224.37\"/><open data=\"646.88\"/><y_close data=\"652.59\"/><change data=\"-14.42\"/><perc_change data=\"-2.21\"/><delay data=\"0\"/><trade_timestamp data=\"2 hours ago\"/><trade_date_utc data=\"20121008\"/><trade_time_utc data=\"200000\"/><current_date_utc data=\"20121008\"/><current_time_utc data=\"222704\"/><symbol_url data=\"/finance?client=ig&amp;q=AAPL\"/><chart_url data=\"/finance/chart?q=NASDAQ:AAPL&amp;tlf=12\"/><disclaimer_url data=\"/help/stock_disclaimer.html\"/><ecn_url data=\"\"/><isld_last data=\"636.00\"/><isld_trade_date_utc data=\"20121008\"/><isld_trade_time_utc data=\"221001\"/><brut_last data=\"\"/><brut_trade_date_utc data=\"\"/><brut_trade_time_utc data=\"\"/><daylight_savings data=\"true\"/></finance></xml_api_reply>";
			WTL::CString result = parser.parseXML(xml);
			Assert::AreEqual(_T("638.17"), result);
		}

	};
}