#ifndef CONFIG_HPP
#define CONFIG_HPP

struct Config {
	double grid_spacing = 10.0;
	int grid_number_size = 20;
	Font font = GetFontDefault();
	Config() {}
	void set_font(std::string filename) {
		font = LoadFont(filename.c_str());
	}
};

#endif
