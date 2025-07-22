#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <sstream>

#include "config.hpp"

double clamp(double x, double min, double max) {
	if (x < min) {return min;}
	if (x > max) {return max;}
	return x;
}

struct Vec2 {
	double x;
	double y;
	Vec2(double x, double y) : x(x), y(y) {}
	std::string x_string() {
		std::stringstream sb;
		sb << x;
		return sb.str();
	}
	std::string y_string() {
		std::stringstream sb;
		sb << y;
		return sb.str();
	}
};
bool operator==(Vec2 l, Vec2 r) {return l.x == r.x && l.y == r.y;}
bool operator!=(Vec2 l, Vec2 r) {return !(l == r);}

struct Viewport {
	int width;
	int height;
	double resolution; // How many pixels wide one unit square is.
	Vec2 center;

	Config config = Config();

	Viewport(int w, int h) : width(w),
							 height(h),
							 resolution(width / 10.0),
							 center(0, 0) {}

	void init() {
		InitWindow(width, height, "GRAPH");
	}

	double left_border() {
		return center.x - width / 2 / resolution;
	}
	double right_border() {
		return center.x + width / 2 / resolution;
	}
	double top_border() {
		return center.y + width / 2 / resolution;
	}
	double bottom_border() {
		return center.y - width / 2 / resolution;
	}

	bool point_is_inside(Vec2 p) {
		if (left_border() > p.x || right_border() < p.x || top_border() < p.y || bottom_border() > p.y) {
			return false;
		}

		return true;
	}

	void draw_grid() {
		for (int x = 0; x <= 10; x++) {
			for (int y = 0; y <= 10; y++) {
				draw_axes(Vec2(-x, y), false);
				draw_axes(Vec2(x, -y), false);
				draw_axes(Vec2(-x, -y), false);
				draw_axes(Vec2(x, y), false);
			}
			//if (!point_is_inside(Vec2(x, 0))) break;
		}
	}

	void draw_axes(Vec2 point, bool force) {
		if (!point_is_inside(point) && !force) return;
		Vec2 point_screen = coord_to_screen(point);

		DrawLineV(Vector2{point_screen.x, 0}, Vector2{point_screen.x, height}, GRAY);
		DrawLineV(Vector2{0, point_screen.y}, Vector2{width, point_screen.y}, GRAY);

		if (point.x == 0 || point.y == 0) {
			if (point.x == 0)
				DrawText(point.y_string().c_str(), point_screen.x + 10, point_screen.y + 10, config.grid_number_size, RAYWHITE);
			else
				DrawText(point.x_string().c_str(), point_screen.x + 10, point_screen.y + 10, config.grid_number_size, RAYWHITE);
		}
	}

	void draw_coordinate_plane() {
		draw_grid();
	}

	Vec2 coord_to_screen(Vec2 p) {
		Vec2 screen_center = Vec2(width / 2, height / 2);
		double diff_x = p.x - center.x;
		double diff_y = p.y - center.y;
		double screen_x = clamp(screen_center.x + diff_x * resolution, 5, width - 5);
		double screen_y = clamp(screen_center.y - diff_y * resolution, 5, height - 5);

		return Vec2(screen_x, screen_y);
	}

	Vec2 screen_to_coord(Vec2 p) {
		Vec2 screen_center = Vec2(width / 2, height / 2);
		double diff_x = p.x - screen_center.x;
		double diff_y = p.y - screen_center.y;
		double screen_x = center.x + diff_x / resolution;
		double screen_y = center.y - diff_y / resolution;

		return Vec2(screen_x, screen_y);
	}

	void draw_point(Vec2 p, float radius, Color color) {
		if (!point_is_inside(p)) {
			return;
		}
		Vec2 p_screen = coord_to_screen(p);
		DrawCircle(p_screen.x, p_screen.y, radius, color);
	}

	void draw_line(Vec2 start, Vec2 end, Color color) {
		Vec2 a = coord_to_screen(start);
		Vec2 b = coord_to_screen(end);

		DrawLineV(Vector2{a.x, a.y}, Vector2{b.x, b.y}, color);
	}
};

#endif
