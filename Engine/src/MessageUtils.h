bool messageShowed = false;
const SDL_MessageBoxButtonData buttons[] = {
	{ /* .flags, .buttonid, .text */        0, 0, "no" },
	{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
};

const SDL_MessageBoxColorScheme colorScheme = {
	{ /* .colors (.r, .g, .b) */
		/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
		{ 255, 0, 0 },
		/* [SDL_MESSAGEBOX_COLOR_TEXT] */
		{ 0, 255, 0 },
		/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
		{ 255, 255, 0 },
		/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
		{ 0, 0, 255 },
		/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
		{ 255, 0, 255 }
	}
};

const SDL_MessageBoxData messageboxdata = {
	SDL_MESSAGEBOX_INFORMATION, /* .flags */
	NULL, /* .window */
	"Game Over", /* .title */
	"You Lost! Let's play again?", /* .message */
	SDL_arraysize(buttons), /* .numbuttons */
	buttons, /* .buttons */
	&colorScheme /* .colorScheme */
};