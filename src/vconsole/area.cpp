#include <escape-tui/vconsole/area.hpp>

namespace escape_tui {

	namespace vconsole {

		void Area::write(char *data, std::uint_fast8_t len) {

			// Clear the area.
			for (std::uint_fast8_t y = _sy; y < _sy + _y; y++) {

				for (std::uint_fast8_t x = _sx; x < _sx + _x; x++) {
					
					// Switch every symbol to the space.
					_array[x][y] = ' ';

				}

			}

			std::uint_fast8_t counter = 0;

			for (std::uint_fast8_t y = _sy; y < _sy + _y; y++) {

				for (std::uint_fast8_t x = _sx; x < _sx + _x; x++) {

					if (counter >= len) return;
					_array[x][y] = data[counter++];

				}

			}



		}
	
	}

}
