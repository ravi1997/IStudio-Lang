
#ifndef _TERMINAL_HPP_
#include <terminal.hpp>
#endif // !_TERMINAL_HPP_

template <typename t>
const Terminal<t> Terminal<t>::EPSILON{"", Terminal<t>::TerminalType::EPSILON};

template <typename t>
const Terminal<t> Terminal<t>::DOLLAR{"", Terminal<t>::TerminalType::END};