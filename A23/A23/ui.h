#pragma once

struct UI {
	struct Controller* contr;
};

struct UI* ui_init();
void ui_destr(struct UI* ui);
void run(struct UI* ui);
