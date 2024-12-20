// pebf.c
//
//      Copyright (c).  2024 pyasmjarjsf90. All rights reserved.
//
                    
       //\\         __________     __________    __________    __________   
      //  \\       |          |   |          |  |          |  |          |  |          |
     // o  \\      |          |   |          |  |          |  |          |  |          |
    // o  o \\     |__________|   |__________|  |__________|  |          |  |          |
   //    o   \\    |          |   |   \         |   \         |          |  |    /\    |
  //  o     o \\   |          |   |    \        |    \        |          |  |   /  \   |
 // o   o  o   \\  |          |   |     \       |     \       |          |  |  /    \  |
//______________\\ |          |   |      \      |      \      |          |  | |      | |
     //____\\      |          |   |       \     |       \     |__________|  |_|      |_|

//                                 Arrow e-book format.

#include"pebf.h"

ebook loadPebf(string literalPebf) {
    ebook preParse;
    preParse.ebookElements.push_back(element());
    for (size_t literalPebfIter = 0; literalPebfIter < literalPebf.size(); ++literalPebfIter) {
        switch (literalPebf[literalPebfIter]) {
            case 1:
                preParse.ebookElements.back().elementTypes.push_back(boldElement);
                break;

            case 2:
                preParse.ebookElements.back().elementTypes.push_back(italicElement);
                break;
            
            case 3:
                preParse.ebookElements.back().elementTypes.push_back(underlinedElement);
                break;

            case 4:
                preParse.ebookElements.back().elementTypes.push_back(hyperLinkElement);
                break;

            case 5:
                preParse.ebookElements.back().elementTypes.push_back(headerElement);
                break;

            case 6:
                preParse.ebookElements.back().elementTypes.push_back(paragraphElement);
                break;

            case 10:
                preParse.ebookElements.push_back(element());
                break;
            
            case 92:
                preParse.ebookElements.back().elementLiteral += literalPebf[literalPebfIter+1];
                ++literalPebfIter;
                break;
            
            default:
                preParse.ebookElements.back().elementLiteral += literalPebf[literalPebfIter];
                break;
        }
    }
    preParse.ebookTitle = preParse.ebookElements[0].elementLiteral;
    preParse.ebookThumbnail = preParse.ebookElements[1].elementLiteral;
    preParse.ebookElements.erase(preParse.ebookElements.begin());
    preParse.ebookElements.erase(preParse.ebookElements.begin());
    return preParse;
}

string pebfHtml(ebook pebfEbook) {
    string htmlFinal;
    vector<preparsehtml> htmlPre;
    htmlPre.push_back({{"<head><title>"}, pebfEbook.ebookTitle, {"</title></head>"}});
    for (auto ebookElement: pebfEbook.ebookElements) {
        htmlPre.push_back(preparsehtml());
        htmlPre.back().literal = ebookElement.elementLiteral;
        for (auto ebookElementC: ebookElement.elementTypes) {
            switch (ebookElementC) {
                case boldElement:
                    htmlPre.back().startTags.push_back("<b>");
                    htmlPre.back().endTags.push_back("</b>");
                    break;

                case italicElement:
                    htmlPre.back().startTags.push_back("<i>");
                    htmlPre.back().endTags.push_back("</i>");
                    break;

                case underlinedElement:
                    htmlPre.back().startTags.push_back("<u>");
                    htmlPre.back().endTags.push_back("</u>");
                    break;

                case hyperLinkElement:
                    htmlPre.back().startTags.push_back("<a href=\""+ebookElement.elementLiteral+"\">");
                    htmlPre.back().endTags.push_back("</a>");
                    break;

                case headerElement:
                    htmlPre.back().startTags.push_back("<h>");
                    htmlPre.back().endTags.push_back("</h>");
                    break;
                
                case paragraphElement:
                    htmlPre.back().startTags.push_back("<p>");
                    htmlPre.back().endTags.push_back("</p>");
                    break;
            }
        }
    }

    for (auto preHtml: htmlPre) {
        for (auto startTag: preHtml.startTags) {
            htmlFinal += startTag.c_str();
        }
        htmlFinal += preHtml.literal;
        for (auto endTag: preHtml.endTags) {
            htmlFinal += endTag.c_str();
        }
    }

    return htmlFinal;
}