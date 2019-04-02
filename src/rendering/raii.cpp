#include "raii.h"

//std::unordered_map<FuncType, std::deque<TupleType>> RAII<stacks;
//
//template <>
//std::unordered_map<WithViewport::FuncType, std::deque<WithViewport::TupleType>> WithViewport::stacks;
//
decltype(make_deques(functions)) stacks = make_deques(functions);
