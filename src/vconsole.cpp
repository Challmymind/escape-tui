#include <escape-tui/vconsole.hpp>
#include <escape-tui/conmode.hpp>
#include <cstdio>


namespace escape_tui {

	VConsole::VConsole(std::uint_fast8_t x, std::uint_fast8_t y) {

		// Set size of the window x.
		_x = x;

		// Set size of the window x.
		_y = y;

		// Set console to raw mode.
		console_raw_mode();
		
		// Print new line to create application screen.
		// We need to print one line less than our applicatin will take. 
		for (std::uint_fast8_t i = 0; i < _y - 1; i++) {
			std::fprintf(stdout, "\n");
		}

		// Make cursor invisible.
		std::fprintf(stdout, "\x1B[?25l");

	}

	vconsole::Screen VConsole::get_screen() {
		
		return vconsole::Screen(_x, _y);

	}

	void VConsole::__clear() {
		
		// Go to most top left corner of application.
		std::fprintf(stdout, "\x1B[%dA", _y-1);

		// Clear screen.
		std::fprintf(stdout, "\x1B[0J");

		// Make cursor visible.
		std::fprintf(stdout, "\x1B[?25h");
		
	}

	VConsole::~VConsole() {

		// Clear application.
		__clear();
	}

}

