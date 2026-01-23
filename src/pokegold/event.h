#ifndef _POKEGOLD_EVENT_H_
#define _POKEGOLD_EVENT_H_

#include "core.h"

namespace pokegold::event {

inline core::event<> rom_changed;
inline core::event<> rom_data_changed;
inline core::event<int> pokemon_names_changed;
inline core::event<int> item_names_changed;
inline core::event<int> move_names_changed;
inline core::event<int> hmtms_changed;
inline core::event<int> type_names_changed;

} // namespace pokegold::event

#endif
