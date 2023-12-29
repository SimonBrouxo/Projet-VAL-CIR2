



#include <iostream>
#include <mutex>

using namespace std;
#include <list> 

class ligne {

public:
	std::list<Station> stations;
	std::list<Rame> rames;


	void addRame(Rame r) {
		rames.push_front(r);
	}
	Rame removeRame(Rame r) {
		rames.remove(r);
	}


};

class Rame {
public:
	//std::mutex ramMutex;
	Station satationActuelle;
	Station destination;
	

private:
	double  vitesse;
	string id;
	bool demarer=false;
	int nbMaxPassagers;
	int nbPassagersSortant;
	const float vitesseDeFonctionement;
	const float  acceleration;
	const float deceleration;
	const float decelerationUrgence;
	//int x_pos;
	//int y_pos;

	void circuler() {
		if (demarer) {
			auto debutAcc = std::chrono::steady_clock::now();
				while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - debutAcc).count() <( vitesseDeFonctionement/acceleration)*400) {
					accelerer();				
				}

				while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - debutAcc).count() < (vitesseDeFonctionement / acceleration) * 400) {
					decelerer();
				}
		}
	}
	void arreter() {
		demarer = false;
	}

	void accelerer() {
		while (vitesse + acceleration < vitesseDeFonctionement) {
			vitesse += acceleration;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			std::cout << vitesse;
		}
	}

	void decelerer() {
		while (vitesse - deceleration > 0) {
			vitesse -= deceleration;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			std::cout << vitesse;
		}
	}

	void decelererUrgence() {
		while (vitesse - decelerationUrgence > 0) {
			vitesse -= decelerationUrgence;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
				std::cout << vitesse;
		}
	}



	void setSation(Station s) {
		satationActuelle = s;

	}







};



class Station {
public:
	//std::mutex stationMutex;
	string rameSurLeQuai;
	string name;
	int nbPassagersSurQuai;
	bool ramePresente;


	bool operator==(const Station& other) const {
		return (name == other.name);

	}


	bool operator!=(const Station& other) const {
		return !(name == other.name);

	}

};


class Superviseur {
	
};