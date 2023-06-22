#include <escape-tui.hpp>
#include <cstdio>

char msg[6] = "Hello";

int main() {

	escape_tui::VConsole console(10, 10);
	
	auto sc = console.get_screen();
	auto ar_txt1 = sc.get_area(0, 0, 10, 1);
	auto ar_txt2 = sc.get_area(0, 2, 10, 1);

	ar_txt1.write(msg, 6);
	ar_txt2.write(msg, 6);


	while (true) {

		sc.render();
		
		char symbol;

		std::fscanf(stdin, "%c", &symbol);

		if (symbol == 'q') return 0;
		
	}

}
