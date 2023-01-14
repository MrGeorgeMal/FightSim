#include "main.h"

using namespace std;

void InitialWindow(int width, int height) {
	/*��������� ������ � �������*/
	CONSOLE_FONT_INFOEX fontStructure = {0};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	lstrcpyW(fontStructure.FaceName, L"Lucida Console");
	fontStructure.cbSize = sizeof(fontStructure);
	fontStructure.dwFontSize.Y = 15;
	fontStructure.FontWeight = 400;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontStructure);

	/*��������� ���� �������*/
	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);
	HWND hWnd = GetConsoleWindow();
	RECT rect = { screenW / 2 - width / 2, screenH / 2 - height / 2, screenW / 2 + width / 2, screenH / 2 + height / 2 };
	MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	/*����������� �������� �����*/
	SetConsoleCP(1251);			//������� ��������� ��� ������
	SetConsoleOutputCP(1251);	//������� ��������� ��� ����� ��������
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
		cout << "���� �������� ��������� �������!" << endl << endl;
		cout << "1. ��������� ��������� �������" << endl;
		cout << "2. ����� �� ���������" << endl;
		cout << "������� 1 ��� 2: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			cout << "������� ���� � ����� ������: ";
			cin >> pathForRead;
			cout << "������� ���������� ����: ";
			cin >> countFights;
			cout << "������� ���� � ����� ������: ";
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
		cout << "* ��������� ����� 'settings.txt'" << endl;
		cout << "****************************************" << endl;
		cout << "���� � ����� ������: \t" << pathForRead << endl;
		cout << "���������� ����: \t" << countFights << endl;
		cout << "���� � ����� ������: \t" << pathForWrite << endl << endl;
	}
#pragma endregion


#pragma region Initial Fighers
	if (!fileManager.ReadFromFile(pathForRead)) {
		cout << "������ ��� �������� ����� ��� ������'" << pathForRead << "'!" << endl << endl << endl;
		cout << "��� ����� :)" << endl << endl << endl;
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
	cout << "* ��������� ���� (" << countFights << ")" << endl;
	cout << "****************************************" << endl;
	for (int i = 0; i < GameMode::GetNameVsName().size(); i++)
	{
		cout << "�������� ����� " << i + 1 << endl;
		cout << "���������: " << GameMode::GetNameVsName()[i] << endl;
		cout << "������ �������: " << GameMode::GetWinFighter1()[i] << endl;
		cout << "������ �������: " << GameMode::GetWinFighter2()[i] << endl;
		cout << "����� (���������� ���): " << GameMode::GetDraw()[i] << endl;
		cout << "������������ ���������� �����: " << GameMode::GetNumberLastRoundMax()[i] << endl;
		cout << "����������� ���������� �����: " << GameMode::GetNumberLastRoundMin()[i] << endl;
		cout << "������� ���������� �����: " << GameMode::GetNumberLastRoundAvg()[i] << endl;
		cout << "������������ �������� � �������: " << GameMode::GetAfterFightMaxHP1()[i] << endl;
		cout << "����������� �������� � �������: " << GameMode::GetAfterFightMinHP1()[i] << endl;
		cout << "������� �������� � �������: " << GameMode::GetAfterFightAvgHP1()[i] << endl;
		cout << "������������ �������� � �������: " << GameMode::GetAfterFightMaxHP2()[i] << endl;
		cout << "����������� �������� � �������: " << GameMode::GetAfterFightMinHP2()[i] << endl;
		cout << "������� �������� � �������: " << GameMode::GetAfterFightAvgHP2()[i] << endl;
		cout << endl << endl;
	}

	if (!fileManager.WriteToFile(pathForWrite)) {
		cout << "������ ��� �������� ����� ��� ������'" << pathForWrite << "'!" << endl << endl << endl;
		system("pause");
		return -1;
	}	

	system("pause");
	return 0;
}