#ifndef _XDELTA3_WRAPPER_H_
#define _XDELTA3_WRAPPER_H_

#include <string>
#include <vector>

namespace xdelta3 {

/**
 * C++ like command line interface. Parameters are passed with a map, where the key
 * is the parameter flag, e.g., -s and the value is the flag value, .e.g, the path to a file.
 * If the parameter uses only the flat, without value, e.g. compression option -9
 * simply set the value corresponding to the key to the empty string.
 **/

int exec(const std::vector<std::string> &params);
std::string get_messages();

} // namespace xdelta3

#endif
