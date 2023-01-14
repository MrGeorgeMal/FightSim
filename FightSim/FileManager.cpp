#include "FileManager.h"

/*Конструктор класса FileManager*/
FileManager::FileManager() {

}


/*Деструктор класса FileManager*/
FileManager::~FileManager() {

}


/*Метод чтения данных из файла*/
bool FileManager::ReadFromFile(std::string pathForRead) {
	this->pathForRead = pathForRead;
	
	this->fileForRead.open(pathForRead);
	if (!this->fileForRead.is_open()) { return false; }

	std::string line;
	int countLines = 0;
	while (!this->fileForRead.eof()) {
		std::getline(fileForRead, line);
		if (countLines != 0) {
			if (!line.empty()) {
				std::string data;	//Переменная для записи временной информации
				std::replace(line.begin(), line.end(), ',', '.');

				/*Чтение имени*/
				this->name.push_back(line.substr(0, line.find_first_of(';')));

				/*Чтение Hit Point*/
				line = line.substr(line.find_first_of(';') + 1, line.size() - 1);
				data = line.substr(0, line.find_first_of(';'));
				this->hp.push_back(std::stof(data));

				/*Чтение Damage*/
				line = line.substr(line.find_first_of(';') + 1, line.size() - 1);
				data = line.substr(0, line.find_first_of(';'));
				this->dmg.push_back(std::stof(data));

				/*Чтение Crit Chance*/
				line = line.substr(line.find_first_of(';') + 1, line.size() - 1);
				data = line.substr(0, line.find_first_of(';'));
				this->cc.push_back(std::stoi(data));

				/*Чтение Crit Multiplay*/
				line = line.substr(line.find_first_of(';') + 1, line.size() - 1);
				data = line.substr(0, line.find_first_of(';'));
				this->cm.push_back(std::stoi(data));
			}
		}
		countLines++;
	}

	this->fileForRead.close();
	return true;
}


/*Метод записи данных в файл*/
bool FileManager::WriteToFile(std::string pathForWrite) {
	this->pathForWrite = pathForWrite;

	this->fileForWrite.open(pathForWrite);
	if (!this->fileForWrite.is_open()) { return false; }

	std::string line;
	line = "Имя 1 VS Имя 2;Победа первого;Победа второго;Ничья;Последний раунд (макс.);Последний раунд (мин.);Последний раунд (сред.);Максимальное здоровье у первого;Минимальное здоровье у первого;Среднее здоровье у первого;Максимальное здоровье у второго;Минимальное здоровье у второго;Среднее здоровье у второго\n";
	this->fileForWrite << line;
	std::string data;

	for (int i = 0; i < GameMode::GetNameVsName().size(); i++)
	{
		this->fileForWrite << GameMode::GetNameVsName()[i] << ";";
		this->fileForWrite << GameMode::GetWinFighter1()[i] << ";";
		this->fileForWrite << GameMode::GetWinFighter2()[i] << ";";
		this->fileForWrite << GameMode::GetDraw()[i] << ";";
		this->fileForWrite << GameMode::GetNumberLastRoundMax()[i] << ";";
		this->fileForWrite << GameMode::GetNumberLastRoundMin()[i] << ";";
		this->fileForWrite << GameMode::GetNumberLastRoundAvg()[i] << ";";

		data = std::to_string(GameMode::GetAfterFightMaxHP1()[i]);
		std::replace(data.begin(), data.end(), '.', ',');
		this->fileForWrite << data << ";";

		data = std::to_string(GameMode::GetAfterFightMinHP1()[i]);
		std::replace(data.begin(), data.end(), '.', ',');
		this->fileForWrite << data << ";";

		data = std::to_string(GameMode::GetAfterFightAvgHP1()[i]);
		std::replace(data.begin(), data.end(), '.', ',');
		this->fileForWrite << data << ";";

		data = std::to_string(GameMode::GetAfterFightMaxHP2()[i]);
		std::replace(data.begin(), data.end(), '.', ',');
		this->fileForWrite << data << ";";

		data = std::to_string(GameMode::GetAfterFightMinHP2()[i]);
		std::replace(data.begin(), data.end(), '.', ',');
		this->fileForWrite << data << ";";

		data = std::to_string(GameMode::GetAfterFightAvgHP2()[i]);
		std::replace(data.begin(), data.end(), '.', ',');
		this->fileForWrite << data << ";";
		this->fileForWrite << "\n";
	}

	fileForWrite.close();
	return true;
}