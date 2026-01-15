#ifndef _POKEGOLD_EVENT_H_
#define _POKEGOLD_EVENT_H_

#include "utils.h"

namespace pokegold::event {

inline utils::event<> rom_changed;
inline utils::event<> rom_data_changed;
inline utils::event<int> pokemon_names_changed;
inline utils::event<int> item_names_changed;
inline utils::event<int> move_names_changed;
inline utils::event<int> hmtms_changed;
inline utils::event<int> type_names_changed;

} // namespace pokegold::event

#endif
