#include <cmath>
#include <cstdlib>
#include <ctime>

#include "State.h"
#include "SDL.h"
#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "Game.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"

const int max_time = 5000;
int time_passed;

State::State():  music("./assets/audio/stageState.ogg") {
	quitRequested = false;
	//this->LoadAssets(renderer);
	music.Play(-1);

	this->LoadAssets();

	//printf("State initialized!\n");
}

State::~State() {
	// is unique_ptr than there is no need to 'delete' each element
	soundsArray.clear();

	objectArray.clear();

}

void State::LoadAssets() {
		
	std::unique_ptr<GameObject> newGameObject(new GameObject());
	std::unique_ptr<Sprite> newSprite(new Sprite(*newGameObject, "assets/img/ocean.jpg") );
	Rect clip(0, 0, newSprite->GetWidth(), newSprite->GetHeight());
	newSprite->SetClip(clip);
	newGameObject->box = clip;
	newGameObject->AddComponent(std::move(newSprite));
	objectArray.emplace_back(std::move(newGameObject));


	std::unique_ptr<GameObject> gameObjectWithTileMap = std::make_unique<GameObject>();
	TileSet* tileSet = new TileSet(64,64,"assets/img/tileset.png");
	//std::unique_ptr<TileSet> tileSet(new TileSet(64,64, "assets/img/tileset.png"));
	std::unique_ptr<TileMap> tileMap = std::make_unique<TileMap>(*gameObjectWithTileMap,"assets/map/tileMap.txt", tileSet);
	gameObjectWithTileMap->box = Rect(0,0,tileSet->GetTileWidth(), tileSet->GetTileHeight());
	gameObjectWithTileMap->AddComponent(std::move(tileMap));

	objectArray.emplace_back(std::move( gameObjectWithTileMap) );

	time_passed = 0;
}

void State::Update(float dt) {

	/*
	if (SDL_QuitRequested()) {
		quitRequested = true;
	}
	*/

	//this->Input();

	//this->quitRequested = Game::GetInstance("",0,0).GetInput().QuitRequested();
	this->quitRequested = InputManager::GetInstance().QuitRequested();


	if (InputManager::GetInstance().IsKeyDown(ESCAPE_KEY)) {
		this->quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		//mouseX = Game::GetInstance("",0,0).GetInput().GetMouseX();
		//mouseY = Game::GetInstance("",0,0).GetInput().GetMouseY();
		int mouseX = InputManager::GetInstance().GetMouseX();
		int mouseY = InputManager::GetInstance().GetMouseY();

		Vec2 objPos = Vec2(100,0);
		Vec2 vec2_cliqued(mouseX, mouseY);
		objPos = Vec2( 100, 0 );
		objPos = objPos.Rotate( -M_PI + M_PI*(rand() % 1001)/500.0 ) + vec2_cliqued;
		this->AddObject((int)objPos.x, (int)objPos.y);
	}

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

	if (time_passed > max_time && soundsArray.size() != 0) {
		time_passed = 0;
		//soundsArray.era/se(soundsArray.end()-1);
		soundsArray.pop_back();
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

/*
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
*/

void State::AddObject(int mouseX, int mouseY) {
	std::unique_ptr<GameObject> newGameObject(new GameObject());

	std::unique_ptr<Sprite> newSprite = std::make_unique<Sprite>(*newGameObject, "assets/img/penguinface.png");
	Rect clip(0, 0, newSprite->GetWidth(), newSprite->GetHeight());
	newSprite->SetClip(clip);
	newGameObject->box = Rect(mouseX-newSprite->GetWidth()/2, 
		mouseY - newSprite->GetHeight()/2, newSprite->GetWidth(), newSprite->GetHeight() );

	newGameObject->AddComponent(std::move(newSprite));

	std::unique_ptr<Sound> sound = std::make_unique<Sound>(*newGameObject,"assets/audio/boom.wav");

	newGameObject->AddComponent(std::move(sound));

	std::unique_ptr<Face> face = std::make_unique<Face>(*newGameObject);

	newGameObject->AddComponent(std::move(face));

	objectArray.emplace_back(std::move(newGameObject));

}