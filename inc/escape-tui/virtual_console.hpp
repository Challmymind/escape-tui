#ifndef __ESCAPE_TUI_VIRTUAL_CONSOLE__
#define __ESCAPE_TUI_VIRTUAL_CONSOLE__

#include <cstdint>


// Hard coded console heigth.
// Value based on linux console.
#define CONSOLE_HEIGHT 24

// Hard coded console width.
// Value based on linux console.
#define CONSOLE_WIDTH 80

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
			 * */
			VConsole();

			/* Clears application.
			 * */
			~VConsole();

			/* Write data to the virutal console.
			 *
			 * After writing to this buffer screen will be updated after
			 * render command.
			 *
			 * @param x position where to write data (in range 0-23),
			 * y position where to write data (in range 0-79),
			 * and data with is size. If data is longer than avaible space then additional data is lost.
			 *
			 * @return true if whole data has been written.
			 * */
			bool write_data(std::uint_fast8_t x, std::uint_fast8_t y, char * data, std::uint_fast8_t size);

			/* Render changes on screen.
			 * Every change that has been buffered via write methods is written to
			 * the 'real' console.
			 * */
			void render();

		private:

			// Jumps to the position in the terminal.
			// Return true if no error occured.
			bool __jump_to_line(std::uint_fast8_t x, std::uint_fast8_t y);

			// Clear screen,
			// Clears all application.
			void __clear();

			// Current cursor y position.
			// It won't start with zero but will be updated accordingly.
			std::uint_fast8_t _heigth = 0;

			// Current cursor x position.
			std::uint_fast8_t _width = 0;
			
			// Virtual console representation
			// Last column of each row is set to one if line
			// has been changed.
			char _vconsole[CONSOLE_WIDTH+1][CONSOLE_HEIGHT];
	};

}

#endif
