#ifndef __ESCAPE_TUI_CONSOLE_INPUT__
#define __ESCAPE_TUI_CONSOLE_INPUT__

#include <mutex>
#include <thread>


namespace escape_tui {

	/* Records asynchronously input from user.
	 *
	 * Cleans itself after usage and ensures that every
	 * started thread has exited.
	* */
	class InputRecorder {

		public:

			/* Starts recording input.
			 *
			 * Shuld be called only once, additional calls will be
			 * ommited.
			 * */
			void start_recording();

			/* Stops recording input.
			 *
			 * Return after closing input thread.
			 * Calling without running thread will cause nothing.
			 * */
			void stop_recording();

			/* Ensures that efter exiting no created thread is running.
			 * */
			~InputRecorder();

			/* Returns latest input.
			 *
			 * @return latest input or 0 if nothing new has been registered.
			 * */
			char get_input();

		private:

			// Flag is set to true if thread has been dispatched.
			bool _is_thread_on = false;

			// Input function.
			// Runs in background and registers all input.
			void __input_function();

			// Input thread.
			std::thread _input_thread;

			// GUARDED latest input.
			// Do not cleared until used.
			char _g_latest;

			// Changes GUARDED flag to true if new input has been received.
			bool _g_new_input = false;

			// GUARDED flag set to on if input thread should run.
			bool _g_should_record = false;
			
			// Read/write mutex.
			// Must be locked when accessing GUARDED variables.
			std::mutex _rw_mutex;

	};

}

#endif
