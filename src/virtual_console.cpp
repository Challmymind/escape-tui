#include <escape-tui/virtual_console.hpp>
#include <escape-tui/console_mode.hpp>
#include <cstdio>


namespace escape_tui {

	VConsole::VConsole() {

		// Set console to raw mode.
		console_raw_mode();
		
		// Print new line to create application screen.
		// We need to print one line less than our applicatin will take. 
		for (std::uint_fast8_t i = 0; i < CONSOLE_HEIGHT - 1; i++) {
			std::fprintf(stdout, "\n");
		}

		// Clear buffer.
		// Note: please initialize value, without initialization to 0
		// causes some weird bugs.
		for (std::uint_fast8_t i = 0; i < CONSOLE_HEIGHT; i++) {
			for (std::uint_fast8_t j = 0; j <= CONSOLE_WIDTH; j++) {

				_vconsole[j][i] = ' ';
			}
		}

		// Set to max value because there is currently pointer.
		// It's index so we need to 
		_heigth = CONSOLE_HEIGHT - 1;

		// Make cursor invisible.
		std::fprintf(stdout, "\x1B[?25l");

	}

	bool VConsole::write_data(std::uint_fast8_t x, std::uint_fast8_t y, char *data, std::uint_fast8_t size)	{

		// Return false if x is out of ragne.
		if (x >= CONSOLE_WIDTH)	return false;

		// Return false if y is out of range.
		if (y >= CONSOLE_HEIGHT) return false;

		// Set x to current position.
		std::uint_fast8_t position = x;	

		// Set iteration counter.
	 	std::uint_fast8_t iteration = 0;

		// Check for out of range in _vconsole and data.
		while (position < CONSOLE_WIDTH && iteration < size) {

			// Copy data to _vconsole.
			_vconsole[position][y] = data[iteration];

			// Increase iteration.
			iteration++;

			// Increase position.
			position++;

		}

		// Change "change flag" to 1.
		_vconsole[CONSOLE_WIDTH][y] = 1;

		// Return success.
		return true;
	}

	bool VConsole::__jump_to_line(std::uint_fast8_t x, std::uint_fast8_t y) {

		// Return false if x is out of ragne.
		if (x >= CONSOLE_WIDTH)	return false;

		// Return false if y is out of range.
		if (y >= CONSOLE_HEIGHT) return false;

		std::int_fast8_t relative = _heigth - y;	

		// You can use else because for 0 it will move it anyway.
		if (relative < 0) {

			// Move cursor down 'relative' lines.
			std::fprintf(stdout, "\x1B[%dB", -relative);
			
		}
		if (relative > 0) {

			// Move cursor up 'relative' lines.
			std::fprintf(stdout, "\x1B[%dA", relative);
		}

		// Use same variable for new test.
		relative = _width - x;

		if (relative < 0) {

			// Move cursor right 'relative' lines.
			std::fprintf(stdout, "\x1B[%dC", -relative);
			
		}

		// You can use else because for 0 it will move it anyway.
		if (relative > 0) {

			// Move cursor left 'relative' lines.
			std::fprintf(stdout, "\x1B[%dD", relative);
		}
		

		// Set new height.
		_heigth = y;

		// Set new width
		_width = x;

		return true;
	}

	void VConsole::__clear() {
		
		// Go to most top left corner of application.
		__jump_to_line(0, 0);

		// Clear screen.
		std::fprintf(stdout, "\x1B[0J");

		// Make cursor visible.
		std::fprintf(stdout, "\x1B[?25h");
		
	}

	void VConsole::render() { 

		// Check for modified lines.
		for (std::uint_fast8_t i = 0; i < CONSOLE_HEIGHT; i++) {
			
			// Check "changed" index.
			if (_vconsole[CONSOLE_WIDTH][i] != 0) {
			
				// Jump to modified line.
				__jump_to_line(0, i);

				// Print whole changed line.
				for (std::uint_fast8_t j = 0; j < CONSOLE_WIDTH; j++) {

					// Print each character.
					std::fprintf(stdout, "%c", _vconsole[j][i]);

					// Increase _width every write.
					_width++;
				}

				// Reset flag after print.
				_vconsole[CONSOLE_WIDTH][i] = 0;
				
			}
		}

	}

	VConsole::~VConsole() {

		// Clear application.
		__clear();
	}

}

