#include <string.h>

class Token
{
public:
    int tag;
    Token(int t);
    char *toString();
}