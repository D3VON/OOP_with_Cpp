#include <stdio.h>

#ifndef LISTKLUGE_HPP
#define LISTKLUGE_HPP


#define List_DEFINE(XYZZTOP) \
do{\
#include "List"#XYZZTOP".hpp"\
} while (0)


#endif // List_DEFINE(XYZZTOP)


#endif //LISTKLUGE_HPP
