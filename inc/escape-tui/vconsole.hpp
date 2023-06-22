#ifndef __ESCAPE_TUI_VIRTUAL_CONSOLE__
#define __ESCAPE_TUI_VIRTUAL_CONSOLE__

#include "vconsole/screen.hpp"

#include <cstdint>

namespace escape_tui {

	/* Virtual console is representation of 'real' console.
	 *
	 * It's additional layer when interacting with real console.
	 * Don't use anythink else for writing to console otherwise it
	 * will break bacuse of desynchronization 'real' console from
	 * virtual one.
	 *
	 * Also manages console input.
	 * */
	class VConsole {
		
		public:

			/* Initialize console.
			 *
			 * Creates new space for application and keeps track of it's content.
			 *
			 * @param x and y length of window.
			 * */
			VConsole(std::uint_fast8_t x, std::uint_fast8_t y);

			/* Clears application.
			 * */
			~VConsole();

			/* Get new screen.
			 *
			 * You can render screen to stdout.
			 *
			 * @param x position where to write data (in range 0-23),
			 * y position where to write data (in range 0-79),
			 * and data with is size. If data is longer than avaible space then additional data is lost.
			 *
			 * @return screen instance.
			 * */
			vconsole::Screen get_screen();

		private:

			// Clear screen,
			// Clears all application.
			void __clear();

			// Window sizes.
			std::uint_fast8_t _x, _y;
	};

}

#endif
