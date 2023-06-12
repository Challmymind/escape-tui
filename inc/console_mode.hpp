#ifndef __ESCAPE_TUI_CONSOLE_MODE__
#define __ESCAPE_TUI_CONSOLE_MODE__

namespace escape_tui {

	/* Switch console mode to raw from cooked/canonical.
	 *
	 * Back ups original state automatically and restores it after exit.
	 * Should be called only once, additional calls do nothing.
	 * */
	void console_raw_mode();

}

#endif
