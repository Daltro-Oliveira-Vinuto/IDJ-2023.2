#include "State.h"
#include "Game.h"
#include "Camera.h"
#include "CameraFollower.h"

const int max_time = 5000;
int time_passed;

State::State():  music("./assets/audio/stageState.ogg") {
	this->quitRequested = false;
	this->started = false;

	music.Play(-1);
	//this->LoadAssets();

	//printf("State initialized!\n");
}

State::~State() {
	// is unique_ptr than there is no need to 'delete' each element
	soundsArray.clear();

	objectArray.clear();

}

void State::Start() {

	this->LoadAssets();

	for(unsigned i = 0; i < this->objectArray.size(); i++) {
		if (! (*(objectArray.begin()+i))->started ) {
			(*(objectArray.begin()+i))->Start();
		}
		
	}

	this->started = true;
}


std::weak_ptr<GameObject> State::AddObject(GameObject* newObject) {
	
	std::shared_ptr<GameObject> newObjectShared(newObject);
	
	this->objectArray.push_back( newObjectShared );

	std::weak_ptr<GameObject> newObjectWeak =  newObjectShared;

	return newObjectWeak;
	
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* desiredObject) {
	std::weak_ptr<GameObject> desiredWeakObject;
	


	for(unsigned i = 0; i < this->objectArray.size(); i++) {
		GameObject* someObject = (*(this->objectArray.begin()+i)).get();
		//std::cout << "someObject: " << someObject << ",  desiredObject: " << desiredObject << std::endl;
		if (someObject == desiredObject) {
			//std::cout << "found address: " << someObject << std::endl;
			std::weak_ptr<GameObject> desiredWeakObjectFound(
										 (*(this->objectArray.begin()+i)) );
			
			return desiredWeakObjectFound;
		}
	}

	return desiredWeakObject;
	
}

void State::LoadAssets() {
		
	std::unique_ptr<GameObject> newGameObject(new GameObject());

	std::unique_ptr<Sprite> newSprite(new Sprite(*newGameObject, "assets/img/ocean.jpg") );
	
	Rect clip(0, 0, newSprite->GetWidth(), newSprite->GetHeight());

	newSprite->SetClip(clip);

	newGameObject->box = clip;

	newGameObject->AddComponent(std::move(newSprite));

	std::unique_ptr<CameraFollower> cameraFollower = 
		std::make_unique<CameraFollower>(*newGameObject);

	newGameObject->AddComponent(std::move(cameraFollower));

	objectArray.emplace_back(std::move(newGameObject));



	std::unique_ptr<GameObject> gameObjectWithTileMap =
		 std::make_unique<GameObject>();

	TileSet* tileSet = new TileSet(64,64,"assets/img/tileset.png");

	std::unique_ptr<TileMap> tileMap = 
		std::make_unique<TileMap>(*gameObjectWithTileMap,"assets/map/tileMap.txt", tileSet);
	
	gameObjectWithTileMap->box = 
		Rect(0,0,tileSet->GetTileWidth(), tileSet->GetTileHeight());

	gameObjectWithTileMap->AddComponent(std::move(tileMap));

	objectArray.emplace_back(std::move( gameObjectWithTileMap) );


	std::shared_ptr<GameObject> alienGameObject = 
										std::make_shared<GameObject>();

	//std::cout << "&alienGO in state: " << alienGameObject.get() << std::endl;

	int numberOfMinions = 4;
	std::unique_ptr<Alien> alienComponent =
			std::make_unique<Alien>(*alienGameObject,numberOfMinions);

	alienGameObject->AddComponent(std::move(alienComponent));

	objectArray.emplace_back(std::move(alienGameObject));

	time_passed = 0;

	/*
	for(auto it = objectArray.begin(); it!= objectArray.end(); it++) {
		 std::cout << "(*it).get(): " << (*it).get() << std::endl;

	}
	*/
}


void State::Update(float dt) {
	Camera::Update(dt);
	//printf("delta time: %.3lf s\n", dt);

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
	
	if (!this->quitRequested) {	

		if (InputManager::GetInstance().KeyPress(KEY_PRESS_a)) {
			printf("Camera::pos: (%.2lf, %.2lf)\n", Camera::pos.x, Camera::pos.y);

		}

		/*
		if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
			//mouseX = Game::GetInstance("",0,0).GetInput().GetMouseX();
			//mouseY = Game::GetInstance("",0,0).GetInput().GetMouseY();
			int mouseX = InputManager::GetInstance().GetMouseX();
			int mouseY = InputManager::GetInstance().GetMouseY();

			Vec2 objPos = Vec2(100,0);
			Vec2 vec2_cliqued(mouseX, mouseY);
			//printf("vec2_cliqued: (%.2lf, %.2lf)\n", vec2_cliqued.x, vec2_cliqued.y);
		
			objPos = objPos.Rotate( -M_PI + M_PI*(rand() % 1001)/500.0 );
			objPos = vec2_cliqued + objPos;
			objPos = objPos - Camera::pos;
			this->AddObject((int)objPos.x, (int)objPos.y);
			//printf("objPos: (%.2lf, %.2lf)\n", objPos.x, objPos.y);
		}
		*/

		for(unsigned i = 0; i < this->objectArray.size(); i++) {
			(*(this->objectArray.begin()+i))->Update(dt);
			
		}

		for(unsigned i = 0; i < objectArray.size(); i++) {
			if ((objectArray[i])->IsDead()) {
				
				Component* componentAux = objectArray[i]->ReleaseComponent("Sound");
				std::unique_ptr<Component> component = std::unique_ptr<Component>(componentAux);
				soundsArray.emplace_back(std::move(component));

				objectArray.erase(objectArray.begin()+i);
			}
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

	for(unsigned i = 0; i < this->objectArray.size(); i++) {
		(*(this->objectArray.begin()+i))->Render();
		
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

/*
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

*/