/**
 * @file FatBugTest.cpp
 * @author Jared Bloch
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Item.h>
#include <Level.h>
#include <GarbageBug.h>
#include <Feature.h>
#include <NullBug.h>
#include <RedundancyFly.h>
#include <Bug.h>
#include <wx/filename.h>
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/xml/xml.h>
#include <BugVisitor.h>
#include <wx/regex.h>

using namespace std;

/**
 * Code Class for content of xml file
 */
class Code {
private:
	wxXmlNode * mNode = nullptr;
	wxString mCodeContent = "";
	wxString mCodeFix = "";
public:
	Code(wxXmlNode * node) : mNode(node), mCodeContent(node->GetNodeContent()), mCodeFix(node->GetAttribute(L"pass", L"")){}

	void SetCode(wxString fixed){mCodeContent = fixed;}

	bool Passes()
	{

		wxRegEx regExp(mCodeFix, wxRE_NEWLINE);
		return regExp.Matches(mCodeContent);

	}

};

/**
 * Code Testing Class
 */
class CodeTest : public ::testing::Test{
protected:
	std::shared_ptr<Code> mCode;
	std::vector<std::wstring> mAnswers;

	/**
	 * Load in XML File
	 * @param filename Name of XML File
	 */
	void Load(std::wstring filename)
	{
		wxXmlDocument doc;
		ASSERT_TRUE(doc.Load(filename));
		auto node = doc.GetRoot();
		mCode = std::make_shared<Code>(node);

		auto child = node->GetChildren();

		for( ; child; child=child->GetNext())
		{
			if (child->GetName() == L"answer")
			{
				auto answer = child->GetNodeContent();
				mAnswers.push_back(answer.ToStdWstring());
			}
		}

	}

	/**
	 * Check if answers match xml file answer
	 */
	void AssertAnswers(){

		for (int i=0; i<mAnswers.size();i++)
		{
			mCode->SetCode(mAnswers[i]);
			ASSERT_TRUE(mCode->Passes());
		}

	}




};

TEST_F(CodeTest, GarbageBug2){
	Load(L"../Tests/Test-Data/garbage-bug-2.xml");
	ASSERT_FALSE(mCode->Passes());
	AssertAnswers();
}

TEST_F(CodeTest, GarbageBug3){
	Load(L"../Tests/Test-Data/garbage-bug-3.xml");
	ASSERT_FALSE(mCode->Passes());
	AssertAnswers();
}