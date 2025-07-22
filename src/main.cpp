#include <raylib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <vector>

#include "graph.hpp"

int main() {
	Viewport vp = Viewport(1000, 1000);

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
		//vp.draw_axes(Vec2(0, 0));
		vp.draw_grid();
		DrawFPS(0, 0);

		double a = -10.0;
		double b = 10.0;
		int point_count = 10000;
		std::vector<Vec2> points;
		for (int i = 0; i < point_count; i++) {
			double x = a + (b - a) / point_count * i;
			double y = 1/x;
			points.push_back(Vec2(x, y));
		}

		for (int i = 0; i < point_count - 1; i++) {
			if (!vp.point_is_inside(points[i])) continue;
			vp.draw_line(points[i], points[i+1], GREEN);
		}

		DrawText(coordinates.str().c_str(), mouse_screen_pos.x, mouse_screen_pos.y - 20, 20, RAYWHITE);
		
		EndDrawing();
	}

	return 0;
}
