#include <cmath>
#include <cstdlib>
#include <ctime>

#include "State.h"
#include "SDL.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "Game.h"

const int max_time = 5000;
int time_passed;

State::State():  music("./assets/audio/stageState.ogg") {
	quitRequested = false;
	//this->LoadAssets(renderer);
	music.Play(-1);

	std::unique_ptr<GameObject> newGameObject(new GameObject());
	std::unique_ptr<Sprite> newSprite(new Sprite(*newGameObject, "assets/img/ocean.jpg") );
	newGameObject->box = Rect(0,0, newSprite->GetWidth(), newSprite->GetHeight() );
	newGameObject->AddComponent(std::move(newSprite));

	objectArray.emplace_back(std::move( newGameObject) );

	time_passed = 0;
}

State::~State() {
	// is unique_ptr than there is no need to 'delete' each element
	objectArray.clear();

	/*
	for(unsigned i = 0; i < sounds.size(); i++) {
		delete sounds.back();
		sounds.pop_back();
	}
	*/
	soundsArray.clear();
}

void State::LoadAssets() {
	
}

void State::Update(float dt) {

	/*
	if (SDL_QuitRequested()) {
		quitRequested = true;
	}
	*/


	this->Input();

	for(auto it = objectArray.begin(); it != objectArray.end(); ++it) {
		(*it)->Update(1);
	}

	for(unsigned i = 0; i < objectArray.size(); i++) {
		if ((objectArray[i])->IsDead()) {
			
			Component* componentAux = objectArray[i]->ReleaseComponent("Sound");
			std::unique_ptr<Component> component = std::unique_ptr<Component>(componentAux);
			soundsArray.emplace_back(std::move(component));
			objectArray.erase(objectArray.begin()+i);
		}
	}

	int delay = 1000.0/Game::FPS;

	time_passed+= delay;

	if (time_passed > max_time) {
		time_passed = 0;
		soundsArray.erase(soundsArray.end()-1);
	}
}

void State::Render() {

	//bg.SetClip(0, 0, bg.GetWidth(), bg.GetHeight());
	//bg.Render( 0, 0);

	for(auto it = objectArray.begin(); it != objectArray.end(); ++it) {
		(*it)->Render();
	}

}

bool State::QuitRequested() {

	return quitRequested;
}

void State::RequestToQuit() {
	quitRequested = true;
}


void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	Vec2 vec2_cliqued((double)mouseX, (double)mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.ContainVec2( vec2_cliqued) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(int( std::rand() % 10 + 10 ) );
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 100, 0 ).Rotate( -M_PI + M_PI*(rand() % 1001)/500.0 ) + vec2_cliqued;
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY) {
	std::unique_ptr<GameObject> newGameObject(new GameObject());

	std::unique_ptr<Sprite> newSprite = std::make_unique<Sprite>(*newGameObject, "assets/img/penguinface.png");

	newGameObject->box = Rect(mouseX-newSprite->GetWidth()/2, 
		mouseY - newSprite->GetHeight()/2, newSprite->GetWidth(), newSprite->GetHeight() );

	newGameObject->AddComponent(std::move(newSprite));

	std::unique_ptr<Sound> sound = std::make_unique<Sound>(*newGameObject,"assets/audio/boom.wav");

	newGameObject->AddComponent(std::move(sound));

	std::unique_ptr<Face> face = std::make_unique<Face>(*newGameObject);

	newGameObject->AddComponent(std::move(face));

	objectArray.emplace_back(std::move(newGameObject));

}