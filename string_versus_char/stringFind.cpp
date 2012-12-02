/*
  The assignment is to write a parser for a simplified form of XML, 
  containing only start-tags, end-tags, content, and namespaces.

 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#include <boost/regex.hpp>

int main () 
{

    //string  str("<root>Stuff.<n1:c1 xmlns:n1=\"http://www.woof.org\"></c1></root>");
    
      //NEED A LOOKUP TABLE FOR MULTIPLE NAMESPACES 
      
    //string  str("<elem1 xmlns:ns1=\"http://www.foo1.org\">\n
    string  str("<elem1 xmlns:ns1=\"http://www.foo1.org\" xmlns:ns2=\"http://www.foo2.org\" >\
                  This is some content.\n\
                  <ns1:elem2 xmlns:ns1=\"http://www.foo.org\" >Content       \n\
                  with a newline.</ns1:elem2   >\n\
                  <ns2:elem3 ></ns2:elem3>\n\
                  <e3>element3</e3>\n\
                  Some more content.\n\
                  </elem1       >");

//······


    string tagName, rawTag, tagNamespace, content;
    //string  str("<a><b>T</b></a>");
cout<<"----------------------------------------"<<endl;
cout<<str<<endl<<"----------------------------------------"<<endl;
    int pos1, pos2, taglength, clsPos, namePos, xPos, spot, 
        nsPos1, nsPos2, afterTxt, nextNsps;     

    // Assuming doc might begin with spaces, 
    // but but first meaningful thing is assumed to be root element.
    pos1 = str.find_first_not_of(" \t\n\v\f\r");

   /***********************
    * PARSE ENTIRE STRING *
    ***********************/

    while(1){ // go through entire string
      /*****************
       * GET WHOLE TAG *
       *****************/
      pos1 = str.find ("<", pos1);
      if (pos1 < 0) break;                 //cout << "'<' found at position " << pos1 << endl;
      pos1++; // so it doesn't keep finding the same character
      pos2 = str.find (">", pos1); //cout << "'>' found at position " << pos2 << endl;
      taglength = pos2-pos1;
      rawTag = str.substr( pos1, taglength ); // cout << rawTag << endl;
      // ALWAYS REMEMBER, 2ND ARG IS COUNT OF CHARS, NOT POSITION
      /*********************
       * GOT WHOLE TAG,    *
       * BEGIN PARSING TAG *
       *********************/
      //if doesn't start with'/' then OK, it's a good tag
      clsPos = rawTag.find ("/"); 
      if (clsPos != 0) // make sure it isn't a closing tag
      { 
        
        // detect if whitespace after tag's name
        char charary[] = " \t\n\v\f\r";
        namePos = rawTag.find_first_of(charary, 0);
        if (namePos < 0) // no space, so, no namespace either
        {
          tagName = rawTag; //cout<<"namespace doesn't exist"<<endl;
          tagNamespace = "";
        }else if (namePos > 0) // space, so there could be a namespace
        {
          tagName = rawTag.substr( 0, namePos );// grab tag's name
          // ALWAYS REMEMBER, 2ND ARG IS COUNT OF CHARS, NOT POSITION
        }
        cout << "..............element name is: " << tagName << endl;

/*********
/*********
/*********       still have to validate that tag starts with letter, 
/*********       and is composed of only letters, numbers, underscore
/*********
/*********/

        xPos = rawTag.find ("xmlns:", 0);
        if (xPos < 0) // no namespace 
        {
          tagNamespace = "";
        }else 
        {
          
          do // validate namespace(s)
          {
            if (xPos < 0) // incorrect namespace syntax , so fail
            {
              cout << "namespace syntax failure" <<endl;
              break;
            }
            // store namespace
            nsPos1 = rawTag.find ("\"", xPos);
            nsPos1++;//start after the first quote
            nsPos2 = rawTag.find ("\"", nsPos1+1);
            tagNamespace = rawTag.substr( nsPos1, nsPos2-nsPos1 );
            // ALWAYS REMEMBER, 2ND ARG IS COUNT OF CHARS, NOT POSITION
            cout << ".........element namespace is: " << tagNamespace << endl;
            
            //nextNsps = rawTag.find_first_not_of(" \t\n\v\f\r", nsPos2+1);
            //cout<<"nextNsps is "<<nextNsps<<endl;


            xPos = rawTag.find ("xmlns:", nsPos2);

          }while (xPos > 0 );

        }
      }
      else // it's a CLOSING tag, so handle that.
      {
        tagName = rawTag.substr( 1, rawTag.length()-1 );// grab tag's name
/*********
/*********
/*********       still have to compare with stack;
/*********       --shouldn't have to validate name at all, 
/*********         just compare with stack
/*********/
        cout << "                  closing tag: "<<"/"<< tagName <<endl;
      }
      /************************
       * FINISHED PARSING TAG *
       ************************/  
         
      // could have been last tag & end of string, so check for that
      //cout<<pos2+1<<" (just beyond closing bracket), "<<str.length()<<" (string length)"<<endl;
      if (pos2+1 == str.length()) break;
         
      if (str.at(pos2+1) != '<' ) // means text follows -- even if it's just a space
      {
        afterTxt = str.find ("<", pos2); // find end of text content
        if (afterTxt < 0) break; // never be true in a well formed doc.
        content = str.substr(pos2+1, afterTxt-pos2-1);
        // ALWAYS REMEMBER, 2ND ARG IS COUNT OF CHARS, NOT POSITION
        cout<< "TEXT CONTENT: \""<<content<<"\""<<endl;
      }
    }//end while(1)
    
    return 0;
}