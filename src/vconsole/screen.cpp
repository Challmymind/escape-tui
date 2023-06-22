#include <escape-tui/vconsole/screen.hpp>
#include <cstdio>

namespace escape_tui {

	namespace vconsole {

		Screen::Screen(std::uint_fast8_t x, std::uint_fast8_t y) {

			// Pass x to the screen.
			_x = x;

			// Pass y to the screen.
			_y = y;

			// Create new array.
			_vconsole = new char*[_x];

			for (std::uint_fast8_t i = 0; i < _x; i++) {
				_vconsole[i] = new char[_y];
			}

			// Clear the screen on start.
			clear();

		}

		Area Screen::get_area(std::uint_fast8_t x, std::uint_fast8_t y, std::uint_fast8_t lenx, std::uint_fast8_t leny) {

			return Area(_vconsole, lenx, leny, x, y);
		}

		void Screen::clear() {

			// Clear screen.
			for (std::uint_fast8_t i = 0; i < _x; i++) {
				for (std::uint_fast8_t j = 0; j < _y; j++) {
					_vconsole[i][j] = ' ';
				}
			}
		}

		void Screen::render() {
			
			// Go to most top left corner of application.
			std::fprintf(stdout, "\x1B[%dA", _y-1);

			// Iterate on whole vconsole.
			for (std::uint_fast8_t i = 0; i < _y; i++) {

				for (std::uint_fast8_t j = 0; j < _x; j++) {

					// Print vconsole to the screen.
					std::fprintf(stdout, "%c", _vconsole[j][i]);

				}

				// Print new line. (one less than there is rows)
				// and go to first column if it's last row.
				if (i < _y - 1) std::fprintf(stdout, "\n\r");
				else std::fprintf(stdout, "\r");
			}

		}
	
	}

}
