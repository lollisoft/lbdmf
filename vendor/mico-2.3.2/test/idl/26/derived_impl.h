
#ifndef __DERIVED_IMPL_H__
#define __DERIVED_IMPL_H__

#include "derived.h"
#include "base_impl.h"


class derived_impl : virtual public base_impl,
                     virtual public derived_skel
{
public:
  derived_impl();
};

#endif

