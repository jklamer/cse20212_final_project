string level::menu(){
	enum KeyPressSurfaces {
		KEY_PRESS_SURFACE_B;
		KEY_PRESS_SURFACE_D;
		KEY_PRESS_SURFACE_S;
		KEY_PRESS_SURFACE_R;
		KEY_PRESS_SURFACE_SPACE;
	}

	string menu_image_path("./Images/menu.jpeg");
	menu =IMG_Load(menu_image_path.c_str());
	while(!quit){
		while( SDL_PollEvent(&e) != 0 ){
			if (e.type == SDL_QUIT) {
				quit = true;
			}	
			else if (keystates[SDL_EVENT_SPACE]){
				string charselect_image_path("./Images/charselect.jpeg");
				charselect=IMG_Load(menu_image_path.c_str());
				if(e.type == SDL_QUIT){
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN){
					switch(e.key.keysym.sym){
						case SDLK_B:
							return "Biz";
							break;
	
						case SDLK_D:
							return "Doz";
							break;
	
						case SDLK_S:
							return "Sledge";
							break;
						
						case SDLK_R:
							return "Ralph";
							break;
						}
					}
				}
			}
		}	
	}
}
