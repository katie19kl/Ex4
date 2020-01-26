#ifndef _ISearcher_h_
#define _ISearcher_h_

#include "Searchable.h"

template <typename T , typename Solution>

class ISearcher
{

public:
  virtual Solution search( Searchable <T> * ) = 0;

  virtual int getTotalNumOfNodes() = 0;

  virtual ~ISearcher(){}
};



#endif
