#include <console_mode.hpp>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

namespace escape_tui {
	
	// Hidden control variable.
	// Ensures that multiple console_raw_mode() won't
	// do harm to the system.
	bool _is_raw_mode_on = false;

	// Stores original console state.
	struct termios __orignal_console;


	// Restores console to orignal state.
	// Hidden function from user.
	void __restore_console() {
		
		// Set to the original console.
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &__orignal_console);

	}

	void console_raw_mode() {
		
		// Make sure that it's first time.
		if (_is_raw_mode_on) return;

		// Get terminal current state.
		tcgetattr(STDIN_FILENO, &__orignal_console);

		// Copy setting to new console.
		struct termios new_console = __orignal_console;

		// Swap ECHO and ICANON flags.
		// ECHO flags makes that input isn't echoed to
		// the output.
		new_console.c_lflag &= ~(ECHO | ICANON);

		// Send new settings.
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_console);

		// Make sure that original console will be restored.
		std::atexit(__restore_console);

		// Change control flag.
		_is_raw_mode_on = true;
	}

}
