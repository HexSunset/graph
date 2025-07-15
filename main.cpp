#include <raylib.h>
#include <string>
#include <sstream>
#include <cstdio>

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

int main() {
	Viewport vp = Viewport(800, 800);

	// Anti-aliasing
	SetConfigFlags(FLAG_MSAA_4X_HINT); 
	vp.init();

	Vec2 p1 = Vec2(1, 1);
	Vec2 p2 = Vec2(1, -1);
	Vec2 p3 = Vec2(-1, 1);
	Vec2 p4 = Vec2(-1, -1);

	std::stringstream coordinates;
	Vec2 mouse_screen_pos = Vec2(0, 0);
	Vec2 mouse_pos = Vec2(0, 0);
	SetTargetFPS(60);


	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_LEFT)) {
			vp.center.x -= 0.1;
		}
		if (IsKeyDown(KEY_RIGHT)) {
			vp.center.x += 0.1;
		}
		if (IsKeyDown(KEY_UP)) {
			vp.center.y += 0.1;
		}
		if (IsKeyDown(KEY_DOWN)) {
			vp.center.y -= 0.1;
		}
		if (IsKeyDown(KEY_PAGE_UP)) {
			vp.resolution += 5;
		}
		if (IsKeyDown(KEY_PAGE_DOWN)) {
			vp.resolution -= 5;
		}

		if (IsKeyPressed(KEY_SPACE)) {
				printf("%f, %f, %f, %f\n", vp.left_border(), vp.right_border(), vp.top_border(), vp.bottom_border());
		}

		mouse_screen_pos.x = GetMouseX();
		mouse_screen_pos.y = GetMouseY();

		mouse_pos = vp.screen_to_coord(mouse_screen_pos);

		coordinates.clear();
		coordinates.str("");
		coordinates << "(" << mouse_pos.x << ", " << mouse_pos.y << ")";

		BeginDrawing();
		
		ClearBackground(BLACK);
		vp.draw_axes();
		DrawFPS(0, 0);
		//DrawCircle(origin_screen.x, origin_screen.y, 10, RAYWHITE);
		vp.draw_point(p1, 5, RED);
		vp.draw_point(p2, 5, GREEN);
		vp.draw_point(p3, 5, BLUE);
		vp.draw_point(p4, 5, YELLOW);

		DrawText(coordinates.str().c_str(), mouse_screen_pos.x, mouse_screen_pos.y - 20, 20, RAYWHITE);
		
		EndDrawing();
	}

	return 0;
}
