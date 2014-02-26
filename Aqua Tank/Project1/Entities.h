#pragma once

template<class T>
class GameEntity{
public:
	T health;
	T health_MAX, health_MIN, health_DECAY;


	GameEntity(T _health, T _MAX, T _MIN, T _DECAY){
		health = _health;
		health_MAX = _MAX;
		health_MIN = _MIN;
		health_DECAY = -(_DECAY + 1);
	}

	void Update(){
		health += health_DECAY;
	}

};

typedef GameEntity<int> GameEntity_i;
typedef GameEntity<double> GameEntity_d;
