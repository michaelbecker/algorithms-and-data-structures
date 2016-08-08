/**
 *  @file
 *
 *  Example code splitting a string into substrings using a given token array.
 *  This leverages the C++ string libraries. This is an alternate 
 *  implementation of an interview question I had over a year ago.
 *
 *  To compile for unit testing:
 *  g++ -DUNIT_TEST -std=c++11 -g string_split.cpp -o string_split
 *
 *  To test:
 *  valgrind --leak-check=full ./string_split
 *
 *  MIT License
 *
 *  Copyright (c) 2016, Michael Becker (michael.f.becker@gmail.com)
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a 
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 *  and/or sell copies of the Software, and to permit persons to whom the 
 *  Software is furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included 
 *  in all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 *  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT 
 *  OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
 *  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <iostream>
#include <string>
#include <vector>


using namespace std;


/**
 *  C++ function to split a string into a vector of strings using 
 *  a string (list) of tokens. Each character in the string is 
 *  a token. 
 */
vector<string> split(const string str, const string token_list)
{
    vector<string> result;
    size_t prior_position = 0;

    //
    //  If the string is empty, we are done.
    //
    if (str.size() == 0) {
		return result;
	}
    
    while (true) {
        //
        //  find_first_of() requires that the position be less than the 
        //  length of the string. If it's not, we consumed the entire 
        //  string so we can exit the loop.
        //
        if (prior_position >= str.size()) {
            break;
        }

        size_t position = str.find_first_of(token_list, prior_position);

        //
        //  We are sitting on a delimiting token, skip ahead.
        //
        if (position == prior_position) {

            prior_position = position + 1;
			
            //
            //  If we walked off the string, we are done.
            //
            if (prior_position >= str.size()) {
				break;
			}
        }
        //
        //  We found something.
        //
        else if (position != string::npos) {
            //
            //  If we have more than 1 character, we are guaranteed to be 
            //  able to copy this.
            //
            if (position > prior_position + 1)
                result.push_back(   str.substr(prior_position, 
                                    position - prior_position));
            //
            //  Our substring of interest is only one character, make sure 
            //  this isn't a delimiting token.
            //
            else if (token_list.find(str[prior_position]) == string::npos)
                result.push_back(str.substr(prior_position, 
                                            position - prior_position));
            //
            //  No matter what skip the delimiter.
            //
            prior_position = position + 1;

            //
            //  If we walked off the string, we are done.
            //
            if (prior_position >= str.size()) {
				break;
			}
        }
        //
        //  We didn't find anything in the remaining string.
        //  We are at the end.
        //
        else {
            //
            //  If we have more than 1 character remaining, we are guaranteed
            //  to be able to copy this.
            //
            if (str.size() - prior_position > 1)
                result.push_back(str.substr(prior_position, string::npos));
            //
            //  We only have one character remaining, make sure this isn't 
            //  a delimiting token.
            //
            else if (token_list.find(str[prior_position]) == string::npos)
                result.push_back(str.substr(prior_position, string::npos));
            //
            //  Exit the loop.
            //
            break;
        }
    }

    return result;
}


#ifdef UNIT_TEST 

void print_result(string str, vector<string> result)
{
    cout << "STRING:\"" << str << "\"" << endl;
    cout << "\tVector holds " << result.size() << " strings" << endl;
    for (vector<string>::iterator it = result.begin();
         it != result.end();
         it++) {
        string str = *it;
        cout << "\t\"" << str << "\"" << endl;
    }
}


int main()
{
    vector<string> result;
    string s1;

    s1 = " ";
    result = split(s1, " ");
    print_result(s1, result);

    s1 = "";
    result = split(s1, " ");
    print_result(s1, result);
    
    s1 = "   ";
    result = split(s1, " ");
    print_result(s1, result);

    s1 = "This is a string";
    result = split(s1, " ");
    print_result(s1, result);


    s1 = "3 trailing spaces   ";
    result = split(s1, " ");
    print_result(s1, result);


    s1 = "   3 leading spaces";
    result = split(s1, " ");
    print_result(s1, result);


    s1 = "X X xxx-\tHelloXXXWorl-d\n\n";
    result = split(s1, "xX \t-\n");
    print_result(s1, result);

    return 0;
}


#endif


