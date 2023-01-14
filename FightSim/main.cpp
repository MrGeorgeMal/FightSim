#include "main.h"

using namespace std;

void InitialWindow(int width, int height) {
	/*Уставнока шрифта в консоле*/
	CONSOLE_FONT_INFOEX fontStructure = {0};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	lstrcpyW(fontStructure.FaceName, L"Lucida Console");
	fontStructure.cbSize = sizeof(fontStructure);
	fontStructure.dwFontSize.Y = 15;
	fontStructure.FontWeight = 400;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontStructure);

	/*Изменение окна консоли*/
	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);
	HWND hWnd = GetConsoleWindow();
	RECT rect = { screenW / 2 - width / 2, screenH / 2 - height / 2, screenW / 2 + width / 2, screenH / 2 + height / 2 };
	MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	/*Подключение русского языка*/
	SetConsoleCP(1251);			//Задание кодировки для вывода
	SetConsoleOutputCP(1251);	//Задание кодировки для ввода латиницы
}

int main() {
	InitialWindow(600, 800);

	ifstream settingsFile;
	FileManager fileManager;
	string pathForRead = "";
	string pathForWrite = "";
	vector<Fighter> fighters;
	int countFights = 0;


#pragma region Read Settings File
	settingsFile.open("settings.txt");
	if (!settingsFile.is_open()) {
		int key = 0;
		cout << "Файл настроек неудалось открыть!" << endl << endl;
		cout << "1. Заполнить настройки вручную" << endl;
		cout << "2. Выйти из программы" << endl;
		cout << "Введите 1 или 2: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			cout << "Введите путь к файлу чтения: ";
			cin >> pathForRead;
			cout << "Введите количество боев: ";
			cin >> countFights;
			cout << "Введите путь к файлу записи: ";
			cin >> pathForWrite;
			cout << endl;
			break;
		case 2:
			return -1;
			break;
		default:
			return -1;
			break;
		}
	}
	else {
		string line;
		getline(settingsFile, line);
		pathForRead = line;
		getline(settingsFile, line);
		countFights = stoi(line);
		getline(settingsFile, line);
		pathForWrite = line;
		settingsFile.close();

		cout << "****************************************" << endl;
		cout << "* Настройки файла 'settings.txt'" << endl;
		cout << "****************************************" << endl;
		cout << "Путь к файлу чтения: \t" << pathForRead << endl;
		cout << "Количество боев: \t" << countFights << endl;
		cout << "Путь к файлу записи: \t" << pathForWrite << endl << endl;
	}
#pragma endregion


#pragma region Initial Fighers
	if (!fileManager.ReadFromFile(pathForRead)) {
		cout << "Ошибка при открытии фалйа для чтения'" << pathForRead << "'!" << endl << endl << endl;
		cout << "Иди нахуй :)" << endl << endl << endl;
		system("pause");
		return -1;
	}

	for (int i = 0; i < fileManager.GetCountFighters(); i++) {
		fighters.push_back(Fighter(fileManager.GetName(i),
			fileManager.GetHP(i),
			fileManager.GetDMG(i),
			fileManager.GetCC(i),
			fileManager.GetCM(i)));
	}
#pragma endregion


	GameMode::DeathMatch(fighters, countFights);

	cout << "****************************************" << endl;
	cout << "* Результат боев (" << countFights << ")" << endl;
	cout << "****************************************" << endl;
	for (int i = 0; i < GameMode::GetNameVsName().size(); i++)
	{
		cout << "Сражение номер " << i + 1 << endl;
		cout << "Сражались: " << GameMode::GetNameVsName()[i] << endl;
		cout << "Первый победил: " << GameMode::GetWinFighter1()[i] << endl;
		cout << "Второй победил: " << GameMode::GetWinFighter2()[i] << endl;
		cout << "Ничья (количество раз): " << GameMode::GetDraw()[i] << endl;
		cout << "Максимальное количество ходов: " << GameMode::GetNumberLastRoundMax()[i] << endl;
		cout << "Минимальное количество ходов: " << GameMode::GetNumberLastRoundMin()[i] << endl;
		cout << "Среднее количество ходов: " << GameMode::GetNumberLastRoundAvg()[i] << endl;
		cout << "Максимальное здоровье у первого: " << GameMode::GetAfterFightMaxHP1()[i] << endl;
		cout << "Минимальное здоровье у первого: " << GameMode::GetAfterFightMinHP1()[i] << endl;
		cout << "Среднее здоровье у первого: " << GameMode::GetAfterFightAvgHP1()[i] << endl;
		cout << "Максимальное здоровье у второго: " << GameMode::GetAfterFightMaxHP2()[i] << endl;
		cout << "Минимальное здоровье у второго: " << GameMode::GetAfterFightMinHP2()[i] << endl;
		cout << "Среднее здоровье у второго: " << GameMode::GetAfterFightAvgHP2()[i] << endl;
		cout << endl << endl;
	}

	if (!fileManager.WriteToFile(pathForWrite)) {
		cout << "Ошибка при открытии фалйа для записи'" << pathForWrite << "'!" << endl << endl << endl;
		system("pause");
		return -1;
	}	

	system("pause");
	return 0;
}