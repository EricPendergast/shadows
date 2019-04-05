#include "raii.h"

decltype(make_deques(functions)) global::gl_call_stacks = make_deques(functions);
