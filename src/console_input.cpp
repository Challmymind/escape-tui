#include <escape-tui/console_input.hpp>
#include <cstdio>

namespace escape_tui {

	void InputRecorder::start_recording() {
		
		// Don't run additional thread.
		if (_is_thread_on) return;

		// Change flag. (No thread is runnning so no need to lock mutex)
		_g_should_record = true;

		// Create thread.
		_input_thread = std::thread(&InputRecorder::__input_function, this);

		// Change flag.
		_is_thread_on = true;

	}

	void InputRecorder::__input_function() {

		while (true) {
			
			// Lock mutex.
			std::lock_guard<std::mutex> lock(_rw_mutex);

			// Check if loop should be continued.
			if (!_g_should_record) {

				// End thread.
				return;
			};


			// Check if you can read more.
			if (!_g_new_input) {

				// Read to the buffer and increase.
				std::fscanf(stdin, "%c", &_g_latest);

				_g_new_input = true;

			}

		}
	}

	void InputRecorder::stop_recording() {
			
		// Check if any thread is running.
		if (!_is_thread_on) return;

		// Lock mutex.
		_rw_mutex.lock();

		// Set flag to false, so thread will close.
		_g_should_record = false;

		// Unlock mutex, so thread can run and exit.
		_rw_mutex.unlock();
		
		// Wait for thread to exit.
		_input_thread.join();

		// No thread is running so no need for mutex.
		_g_should_record = false;

		// Set that no thread is running.
		_is_thread_on = false;
	}

	InputRecorder::~InputRecorder() {

		// Make sure before exiting that no thread is running.
		stop_recording();

	}


	char InputRecorder::get_input() {

		// Try lock.
		if (!_rw_mutex.try_lock()) return 0;

		// Reset flag.
		_g_new_input = false;

		// Save latest input.
		char symbol = _g_latest;

		// Unlock mutex.
		_rw_mutex.unlock();
		
		// Return value.
		return symbol;
	}
}
