#ifndef GRAPH_HPP
#define GRAPH_HPP

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
};

struct Viewport {
	int width;
	int height;
	double resolution; // How many pixels wide one unit square is.
	Vec2 center;

	Config config = Config();

	Viewport(int w, int h) : width(w), height(h), resolution(width / 10.0), center(0, 0) {}

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

	void draw_axes() {
		Vec2 origin = coord_to_screen(Vec2(0, 0));
		DrawLine(origin.x, 0, origin.x, height, RAYWHITE);
		DrawLine(0, origin.y, width, origin.y, RAYWHITE);
	}

	Vec2 coord_to_screen(Vec2 p) {
		Vec2 screen_center = Vec2(width / 2, height / 2);
		double diff_x = p.x - center.x;
		double diff_y = p.y - center.y;
		double screen_x = clamp(screen_center.x + diff_x * resolution, 1, width);
		double screen_y = clamp(screen_center.y - diff_y * resolution, 1, height - 1);

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
};

#endif
