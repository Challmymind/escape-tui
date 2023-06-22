#ifndef __ESCAPE_TUI_VCONSOLE_AREA__
#define __ESCAPE_TUI_VCONSOLE_AREA__

#include <cstdint>

namespace escape_tui {

	namespace vconsole {

		/* Abstraction over virtual screen area.
		 *
		 * Protects system memory from corruption.
		 * */
		class Area {

			public:

				/* Writes to the area.
				 *
				 * @param pointer the data to be written, and it's length.
				 * */
				void write(char * data, std::uint_fast8_t len);

				/* Passes to area it's array, size and starting point.
				 * */
				Area( 	char ** array, 
						std::uint_fast8_t x, 
						std::uint_fast8_t y, 
						std::uint_fast8_t sx, 
						std::uint_fast8_t sy) 
					: _array(array), _x(x), _y(y), _sx(sx), _sy(sy) {}

			private:

				// Array x,y size and starting points.
				std::uint_fast8_t _x, _y, _sy, _sx;

				// Array itself.
				char ** _array;

		};
	
	}

}

#endif
