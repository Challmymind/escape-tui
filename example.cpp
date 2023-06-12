#include <escape-tui.hpp>
#include <cstdio>

int main() {

	escape_tui::VConsole console;
	escape_tui::InputRecorder recorder;

	recorder.start_recording();
	char buffer[10];
	std::uint_fast8_t index = 0;

	while (true) {
		
		char symbol = recorder.get_input();

		if (symbol) {

			if (index >= 10) index = 0;

			buffer[index++] = symbol;

			console.write_data(10, 0, buffer, index);

		}


		if(buffer[0] == 'a') break;
		
		console.render();
	}

}
