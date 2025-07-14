
#pragma once
#include "raylib.h"
#include <vector>
#include <iostream>

#define MAX_SOUND  20

namespace Utils {
	enum class Notes {
		C3,
		D3,
		E3,
		F3,
		G3,
		A3,
		B3,
		C4,
		D4,
		E4,
		F4,
		G4,
		A4,
		B4
	};

	class Sounds {
	private:
		std::vector<Sound> sounds;
		std::vector<std::vector<Sound>> aliases;

		inline void loudSingleSound(Notes note, const std::string& fileName)
		{
			{
				std::vector<Sound> alias(MAX_SOUND);

				sounds[static_cast<int>(note)] = LoadSound(fileName.c_str());
				for (int i = 0; i < MAX_SOUND; ++i)
				{
					alias[i] = LoadSoundAlias(sounds[static_cast<int>(note)]);
				}
				aliases[static_cast<int>(note)] = alias;
			}
		}

	public:
		Sounds() : sounds(static_cast<int>(Notes::B4) + 1), aliases(static_cast<int>(Notes::B4) + 1) {
			InitAudioDevice();
			loudSingleSound(Notes::C3, "assets/sounds/C3.wav");
			loudSingleSound(Notes::D3, "assets/sounds/D3.wav");
			loudSingleSound(Notes::E3, "assets/sounds/E3.wav");
			loudSingleSound(Notes::F3, "assets/sounds/F3.wav");
			loudSingleSound(Notes::G3, "assets/sounds/G3.wav");
			loudSingleSound(Notes::A3, "assets/sounds/A3.wav");
			loudSingleSound(Notes::B3, "assets/sounds/B3.wav");
			loudSingleSound(Notes::C4, "assets/sounds/C4.wav");
			loudSingleSound(Notes::D4, "assets/sounds/D4.wav");
			loudSingleSound(Notes::E4, "assets/sounds/E4.wav");
			loudSingleSound(Notes::F4, "assets/sounds/F4.wav");
			loudSingleSound(Notes::G4, "assets/sounds/G4.wav");
			loudSingleSound(Notes::A4, "assets/sounds/A4.wav");
			loudSingleSound(Notes::B4, "assets/sounds/B4.wav");
		};

		~Sounds() {
			//for (auto& alias : aliases)
			//	for (auto& sound : alias)
			//		UnloadSound(sound);
			for (auto& sound : sounds)
				UnloadSound(sound);
			CloseAudioDevice();
		}

		void playSound(Notes note) {
			if (static_cast<int>(note) < 0 || static_cast<int>(note) >= sounds.size()) {
				return; // Invalid note
			}
			if (!IsSoundPlaying(sounds[static_cast<int>(note)]))
			{
				PlaySound(sounds[static_cast<int>(note)]);
				return;
			}

			auto& alias = aliases[static_cast<int>(note)];
			for (auto& sound : alias)
			{
				if (IsSoundPlaying(sound))
					continue;
				PlaySound(sound);
				break;
			}
		}

		static std::string getTextOfNote(Notes note) {
			switch (note)
			{
			case Utils::Notes::C3:
				return "C3";
			case Utils::Notes::D3:
				return "D3";
			case Utils::Notes::E3:
				return "E3";
			case Utils::Notes::F3:
				return "F3";
			case Utils::Notes::G3:
				return "G3";
			case Utils::Notes::A3:
				return "A3";
			case Utils::Notes::B3:
				return "B3";
			case Utils::Notes::C4:
				return "C4";
			case Utils::Notes::D4:
				return "D4";
			case Utils::Notes::E4:
				return "E4";
			case Utils::Notes::F4:
				return "F4";
			case Utils::Notes::G4:
				return "G4";
			case Utils::Notes::A4:
				return "A4";
			case Utils::Notes::B4:
				return "B4";
			}
		}
	};
};