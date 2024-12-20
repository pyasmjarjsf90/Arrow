enum elementTypes {
    boldElement,
    italicElement,
    underlinedElement,
    hyperLinkElement,
    headerElement,
    paragraphElement
};

#if defined(__cplusplus)
#include<string>
#include<vector>

using namespace std;

typedef struct {
    vector<int> elementTypes;
    string elementLiteral;
} element;

typedef struct {
    string ebookThumbnail;
    string ebookTitle;
    vector<element> ebookElements;
} ebook;

typedef struct {
    vector<string> startTags;
    string literal;
    vector<string> endTags;
} preparsehtml;

ebook loadPebf(string);
string pebfHtml(ebook);
#else 
#error C is currently not supported...
#endif