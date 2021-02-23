#include <stdio.h>
#include <allegro.h>

BITMAP *koSprite;
int exitState;
int i;

typedef struct {
	int velX, velY;
	int posX, posY;
} KokoIcon;

#define ICON_AMT 12
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
		icons[i].velY = (rand()%5 - 2);
		// 0 velocity is boring, nudge if that happens
		if (icons[i].velX == 0) {
			if (rand()%2) {
				icons[i].velX++;
			} else {
				icons[i].velX--;
			}
		}
		if (icons[i].velY == 0) {
			if (rand()%2) {
				icons[i].velY++;
			} else {
				icons[i].velY--;
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
			if (icons[i].posY <= 0 || icons[i].posY >= 168) {
				icons[i].velY = -icons[i].velY;
			}
		}

		// push foxgirl
		for (i = 0; i < ICON_AMT; i++) {
			icons[i].posX += icons[i].velX;
			icons[i].posY += icons[i].velY;
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
