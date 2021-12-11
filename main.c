#include <stdbool.h>
#include <stdio.h>

#include "spaceship.h"

int main()
{
	int sw = 420;//1280; // screen width
	int sh = 210;//720; // screen height
	Spaceship *ship = new_ship(sw, sh);

	printf("Ship: direction: %f, speed: %f, alive: %d (r: %f | g: %f | b: %f) ship ...\n",
		ship->direction, ship->speed, ship->alive,
		ship->color.r, ship->color.g, ship->color.b);

	al_init();
	al_install_keyboard();
	if (!al_init_primitives_addon()) {
		printf("al_init_primitives_addon failed: %d", al_get_errno());
		exit(1);
	}

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_DISPLAY* display = al_create_display(sw, sh);
	ALLEGRO_FONT* font = al_create_builtin_font();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool redraw = true;
	ALLEGRO_EVENT event;

	al_start_timer(timer);
	while(1) {
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN ||
			event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}


		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_text(font, al_map_rgb(255, 255, 255),
				0, 0, 0, "Hello world from Allegro!");
			draw_ship(ship);
			al_flip_display();

			redraw = false;
		}
	}

	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	destroy_ship(ship);

	return 0;
}
