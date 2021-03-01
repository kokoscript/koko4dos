#include <stdio.h>
#include <math.h>
#include <allegro.h>

BEGIN_GFX_DRIVER_LIST
	GFX_DRIVER_VGA
END_GFX_DRIVER_LIST

BEGIN_COLOR_DEPTH_LIST
	COLOR_DEPTH_8
END_COLOR_DEPTH_LIST

BEGIN_DIGI_DRIVER_LIST
END_DIGI_DRIVER_LIST

BEGIN_MIDI_DRIVER_LIST
END_MIDI_DRIVER_LIST

BEGIN_JOYSTICK_DRIVER_LIST
END_JOYSTICK_DRIVER_LIST

BITMAP *koSprite;
int exitState;
int i;

typedef struct {
	int velX;
	int posX, posY;
	int height;
	double arcProgress;
} KokoIcon;

#define ICON_AMT 8
KokoIcon icons[ICON_AMT];

int main(void) {
	allegro_init();
	install_keyboard();
	if (set_gfx_mode(GFX_VGA, 320, 200, 0, 0) < 0) {
		printf("Video error! You need VGA 13h for this :<");
		return 1;
	}

	srand(time(NULL));
	exitState = 0;

	// load bitmap
	koSprite = load_bitmap("koko.bmp", NULL);
	if (!koSprite) {
		printf("Error loading koko.bmp! :<");
		return 1;
	}
	// setup bouncing icons
	for (i = 0; i < ICON_AMT; i++) {
		icons[i].posX = 50 + (rand()%220);
		icons[i].posY = 50 + (rand()%100);
		icons[i].velX = (rand()%5 - 2);
		icons[i].height = 200 - icons[i].posY;
		icons[i].arcProgress = 1.57;
		// 0 velocity is boring, nudge if that happens
		if (icons[i].velX == 0) {
			if (rand()%2) {
				icons[i].velX++;
			} else {
				icons[i].velX--;
			}
		}
	}
	
	do {
		vsync();
		// collision check
		for (i = 0; i < ICON_AMT; i++) {
			if (icons[i].posX <= 0 || icons[i].posX >= 288) {
				icons[i].velX = -icons[i].velX;
			}
		}

		// push foxgirl
		for (i = 0; i < ICON_AMT; i++) {
			icons[i].posX += icons[i].velX;
			icons[i].posY = 168 - (sin(icons[i].arcProgress) * icons[i].height);
			icons[i].arcProgress += 0.01;
			if (icons[i].arcProgress >= 3.14) {
				icons[i].arcProgress = 0;    
			}
		}

		// screen redraw
		clear_to_color(screen, 0);
		for (i = 0; i < ICON_AMT; i++) {
			draw_sprite(screen, koSprite, icons[i].posX, icons[i].posY);
		}

		if (key[KEY_ESC]) {
			exitState = 1;
		}
	} while (exitState == 0);

	destroy_bitmap(koSprite);
	return 0;
}
END_OF_MAIN()
