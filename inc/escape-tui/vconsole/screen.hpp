#ifndef __ESCAPE_TUI_VCONSOLE_SCREEN__
#define __ESCAPE_TUI_VCONSOLE_SCREEN__

#include "area.hpp"

#include <cstdint>
#include <vector>

namespace escape_tui {

	namespace vconsole {
		
		/* Class screen provides user with
		 * a tool to segregate his objects.
		 * */
		class Screen {

			public:

				/* Creates screen of given size.
				 *
				 * The size is passed by vconsole instance.
				 *
				 * @param x, y dimensions of screen.
				 * */
				Screen(std::uint_fast8_t x, std::uint_fast8_t y);

				/* Renders screen instance to the stdout.
				 * */
				void render();

				/* Requests text area on the screen.
				 *
				 * @return area that can be drawn to.
				 *
				 * @param x and y are area starting coordinates and lenx and leny
				 * are it's dimensions.
				 * */
				Area get_area(
						std::uint_fast8_t x,
						std::uint_fast8_t y,
						std::uint_fast8_t lenx,
						std::uint_fast8_t leny);

				/* Clears screen from all areas.
				 */
				void clear();

			private:

				// Dimensions of the screen.
				std::uint_fast8_t _x, _y;

				// Virtual local console representation
				char ** _vconsole;


		};
	
	}

}

#endif
